#include "../../include/central/initialize_listeners.h"

#include <limits.h>
#include <stdint.h>
#include <zephyr/sys/util.h>

/* Detect presence of ZMK headers and provide lightweight fallbacks if ZMK is
 * not available in the static analysis / non-ZMK build environment. This
 * allows the shield source to be compiled/checked without forcing ZMK to be
 * present during the refactor work. When ZMK is available we include the real
 * headers; otherwise we provide minimal stubs and set NICEVIEW_ZMK_AVAILABLE=0.
 */
#if defined(__has_include)
#  if __has_include(<zmk/battery.h>)
#    include <zmk/battery.h>
#    include <zmk/ble.h>
#    include <zmk/display.h>
#    include <zmk/endpoints.h>
#    include <zmk/event_manager.h>
#    include <zmk/events/activity_state_changed.h>
#    include <zmk/events/battery_state_changed.h>
#    include <zmk/events/ble_active_profile_changed.h>
#    include <zmk/events/endpoint_changed.h>
#    include <zmk/events/layer_state_changed.h>
#    include <zmk/events/usb_conn_state_changed.h>
#    include <zmk/keymap.h>
#    include <zmk/usb.h>
#    define NICEVIEW_ZMK_AVAILABLE 1
#  else
#    define NICEVIEW_ZMK_AVAILABLE 0
#  endif
#else
/* Fallback: assume ZMK not available */
#  define NICEVIEW_ZMK_AVAILABLE 0
#endif

#if NICEVIEW_ZMK_AVAILABLE == 0
/* Minimal stub definitions so this file can still be compiled/checked
 * without the full ZMK include tree. These stubs are intentionally small and
 * are only used when ZMK headers are not present.
 */
typedef int zmk_event_t;
static inline int zmk_battery_state_of_charge(void) { return 100; }
static inline bool zmk_usb_is_powered(void) { return false; }
static inline int zmk_ble_active_profile_index(void) { return 0; }
static inline bool zmk_ble_active_profile_is_connected(void) { return false; }
static inline bool zmk_ble_active_profile_is_open(void) { return true; }
static inline int zmk_keymap_highest_layer_active(void) { return 0; }
static inline const char *zmk_keymap_layer_name(int id) { (void)id; return NULL; }

/* Provide no-op macros for the ZMK listener/subscription helpers so the
 * source remains parseable. When ZMK is present, the real macros are used.
 */
#ifndef ZMK_LISTENER
#define ZMK_LISTENER(...)
#endif
#ifndef ZMK_SUBSCRIPTION
#define ZMK_SUBSCRIPTION(...)
#endif
#ifndef ZMK_DISPLAY_WIDGET_LISTENER
#define ZMK_DISPLAY_WIDGET_LISTENER(...)
#endif
#endif /* NICEVIEW_ZMK_AVAILABLE == 0 */

#include "../../include/central/render.h"

struct states states;

/*
 * Replace LVGL timers with a Zephyr k_timer for the background animation.
 *
 * Behavior:
 *  - When CONFIG_NICE_VIEW_PRESS_START_ANIMATION is enabled we start a periodic
 *    k_timer that calls `render_main()` at the configured interval.
 *  - When activity changes to idle/sleep we stop the timer. When active we
 *    (re)start the timer.
 *
 * This keeps the behavior minimal and avoids pulling LVGL into the framebuffer
 * port.
 */
#if IS_ENABLED(CONFIG_NICE_VIEW_PRESS_START_ANIMATION)

static struct k_timer background_k_timer;

/* Handler invoked when the k_timer expires (runs in system workqueue context). */
static void background_k_timer_handler(struct k_timer *kt) {
    ARG_UNUSED(kt);
    states.background_index = (states.background_index + 1) % UINT_MAX;
    render_main();
}

/* Initialize and start the periodic timer (called from initialize_listeners). */
static void start_timer(void) {
    /* Initialize the timer with a no-op expiry function first, then set it. */
    k_timer_init(&background_k_timer, background_k_timer_handler, NULL);

    /* Start periodic timer with the configured frame interval */
    k_timer_start(&background_k_timer, K_MSEC(CONFIG_NICE_VIEW_PRESS_START_ANIMATION_FRAME_MS), K_MSEC(CONFIG_NICE_VIEW_PRESS_START_ANIMATION_FRAME_MS));
}

/* Stop the timer (used when the device is idle/sleeping). */
static void stop_timer(void) {
    k_timer_stop(&background_k_timer);
}

/* We want to pause the animation when the keyboard is idling. */
int activity_update_callback(const zmk_event_t* eh) {
    struct zmk_activity_state_changed* ev = as_zmk_activity_state_changed(eh);
    if (ev == NULL) {
        return -ENOTSUP;
    }

    switch (ev->state) {
        case ZMK_ACTIVITY_ACTIVE: {
            /* (Re)start the periodic timer */
            k_timer_start(&background_k_timer, K_MSEC(CONFIG_NICE_VIEW_PRESS_START_ANIMATION_FRAME_MS), K_MSEC(CONFIG_NICE_VIEW_PRESS_START_ANIMATION_FRAME_MS));
            break;
        }
        case ZMK_ACTIVITY_IDLE:
        case ZMK_ACTIVITY_SLEEP: {
            /* Stop the timer to pause animation */
            stop_timer();
            break;
        }
        default: {
            return -EINVAL;
        }
    }

    return 0;
}

/* Create a listener named `activity_update`. This name is then used to create a
 * subscription. When subscribed, `activity_update_callback` will be called.
 */
ZMK_LISTENER(
    activity_update,
    activity_update_callback
);

/* Subscribe the `activity_update` listener to the `zmk_activity_state_changed`
 * event dispatched by ZMK.
 */
ZMK_SUBSCRIPTION(
    activity_update,
    zmk_activity_state_changed
);
#endif /* CONFIG_NICE_VIEW_PRESS_START_ANIMATION */

static void battery_state_update_callback(struct battery_state state) {
    states.battery = state;

    render_battery();
}

static struct battery_state get_battery_state(const zmk_event_t* event) {
    // `as_zmk_battery_state_changed(event)->state_of_charge` seems to be
    // usually used but the same value can be retrieved from the following.
    const uint8_t level = zmk_battery_state_of_charge();
    const bool is_charging = zmk_usb_is_powered();

    struct battery_state state = {
        .level = level,
        .is_charging = is_charging,
    };

    return state;
}

// Create a listener named `widget_battery_state_update`. This name is then
// used to create a subscription.
ZMK_DISPLAY_WIDGET_LISTENER(
    widget_battery_state_update,
    struct battery_state,
    // Called after `get_battery_state` with the value it returned.
    battery_state_update_callback,
    get_battery_state
)

// Subscribe the `widget_battery_state_update` listener to the
// `zmk_battery_state_changed` event dispatched by ZMK.
ZMK_SUBSCRIPTION(
    widget_battery_state_update,
    // Triggered when the computed battery percentage has changed.
    zmk_battery_state_changed
);

// Subscribe the `widget_battery_state_update` listener to the
// `zmk_usb_conn_state_changed` event dispatched by ZMK.
ZMK_SUBSCRIPTION(
    widget_battery_state_update,
    // Triggered when connected or disconnected from USB.
    zmk_usb_conn_state_changed
);

static void connectivity_state_update_callback(struct connectivity_state state) {
    states.connectivity = state;

    render_connectivity();
}

static struct connectivity_state get_connectivity_state(const zmk_event_t* event) {
    const struct zmk_endpoint_instance selected_endpoint = zmk_endpoints_selected();
    const int active_profile_index = zmk_ble_active_profile_index();
    const bool active_profile_connected = zmk_ble_active_profile_is_connected();
    const bool active_profile_bonded = !zmk_ble_active_profile_is_open();

    struct connectivity_state state = {
        .selected_endpoint = selected_endpoint,
        .active_profile_index = active_profile_index,
        .active_profile_connected = active_profile_connected,
        .active_profile_bonded = active_profile_bonded,
    };

    return state;
}

// Create a listener named `widget_connectivity_state_update`. This
// name is then used to create a subscription.
ZMK_DISPLAY_WIDGET_LISTENER(
    widget_connectivity_state_update,
    struct connectivity_state,
    // Called after `get_connectivity_state` with the value it returned.
    connectivity_state_update_callback,
    get_connectivity_state
)

// Subscribe the `widget_connectivity_state_update` listener to the
// `zmk_endpoint_changed` event dispatched by ZMK.
ZMK_SUBSCRIPTION(
    widget_connectivity_state_update,
    zmk_endpoint_changed
);

// Subscribe the `widget_connectivity_state_update` listener to the
// `zmk_usb_conn_state_changed` event dispatched by ZMK.
ZMK_SUBSCRIPTION(
    widget_connectivity_state_update,
    // Triggered when connected or disconnected from USB.
    zmk_usb_conn_state_changed
);

// Subscribe the `widget_connectivity_state_update` listener to the
// `zmk_ble_active_profile_changed` event dispatched by ZMK.
ZMK_SUBSCRIPTION(
    widget_connectivity_state_update,
    // Triggered when the selected profile has changed.
    zmk_ble_active_profile_changed
);

static void layer_state_update_callback(struct layer_state state) {
    states.layer = state;

    render_main2();
}

// Retrieve the data we want from the event
static struct layer_state get_layer_state(const zmk_event_t* event) {
    const zmk_keymap_layer_index_t index = zmk_keymap_highest_layer_active();
    const char* name = zmk_keymap_layer_name(zmk_keymap_layer_index_to_id(index));

    struct layer_state state = {
        .index = index,
        .name = name
    };

    return state;
}

// Create a listener named `widget_layer_state_update`. This name is then used
// to create a subscription.
ZMK_DISPLAY_WIDGET_LISTENER(
    widget_layer_state_update,
    struct layer_state,
    // Called after `get_layer_state` with the value it returned.
    layer_state_update_callback,
    get_layer_state
)

// Subscribe the `widget_layer_state_update` listener to the
// `zmk_battery_state_changed` event dispatched by ZMK.
ZMK_SUBSCRIPTION(
    widget_layer_state_update,
    // Triggered when the selected layer has changed.
    zmk_layer_state_changed
);

void initialize_listeners() {
    widget_layer_state_update_init();
    widget_connectivity_state_update_init();
    widget_battery_state_update_init();

#if IS_ENABLED(CONFIG_NICE_VIEW_PRESS_START_ANIMATION)
    start_timer();
#endif
}
