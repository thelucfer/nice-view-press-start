#pragma once

#include "../initialize_listeners.h"

#include <stdbool.h>
#include "../utils/draw_battery.h"

/* Forward declarations to avoid pulling ZMK headers into this public header.
 *
 * The implementation files (C sources) should include the real ZMK headers
 * where the types are actually used. These lightweight forward declarations
 * allow other shield headers to reference these types without forcing a
 * dependency on the full ZMK include tree at the point of inclusion.
 */

/* Use a void* for the selected_endpoint to avoid incomplete-type issues.
 * The concrete ZMK endpoint type is only required in the implementation C
 * files that include the real ZMK headers.
 */
typedef void* zmk_endpoint_instance_t;

/* Layer index type used by ZMK keymap APIs. Use a signed integer as a safe
 * minimal representation; the real ZMK header defines this typedef precisely.
 */
typedef int zmk_keymap_layer_index_t;

struct connectivity_state {
    zmk_endpoint_instance_t selected_endpoint;
    int active_profile_index;
    bool active_profile_connected;
    bool active_profile_bonded;
};

struct layer_state {
    zmk_keymap_layer_index_t index;
    const char* name;
};

struct states {
    unsigned background_index;
    struct battery_state battery;
    struct connectivity_state connectivity;
    struct layer_state layer;
};

extern struct states states;

void initialize_listeners();
