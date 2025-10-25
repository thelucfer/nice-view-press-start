#pragma once
/*
 * Minimal zephyr/kernel.h stub for static analysis and framebuffer-only builds.
 *
 * This header provides a tiny, no-op subset of the Zephyr kernel API used by
 * the shield code (timers, basic macros). It intentionally does not implement
 * any real RTOS behavior; it only supplies symbols so the code compiles/analyses
 * cleanly in environments that do not have Zephyr available.
 *
 * WARNING: This is a stub for static-analysis and local development only.
 * Do NOT rely on this for real device behavior. Use the real Zephyr headers
 * and runtime when building firmware for hardware.
 */

#include <stdint.h>
#include <stddef.h>

/* Basic unused-parameter helper */
#ifndef ARG_UNUSED
#define ARG_UNUSED(x) (void)(x)
#endif

/* Millisecond helper macro (keeps numeric value for stubs) */
#ifndef K_MSEC
#define K_MSEC(ms) (ms)
#endif

/* Minimal k_timer type and helpers (no real timing functionality) */
typedef struct k_timer {
    /* opaque in this stub */
    void *priv;
} k_timer_t;

/* Function pointer type for timer handlers */
typedef void (*k_timer_handler_t)(struct k_timer *);

/* Initialize a k_timer; no-op in stub implementation */
static inline void k_timer_init(struct k_timer *timer, void (*expiry_fn)(struct k_timer *), void *user_data)
{
    ARG_UNUSED(timer);
    ARG_UNUSED(expiry_fn);
    ARG_UNUSED(user_data);
}

/* Start a k_timer with given initial and period intervals (ms) -- no-op */
static inline void k_timer_start(struct k_timer *timer, uint32_t delay_ms, uint32_t period_ms)
{
    ARG_UNUSED(timer);
    ARG_UNUSED(delay_ms);
    ARG_UNUSED(period_ms);
}

/* Stop a k_timer -- no-op */
static inline void k_timer_stop(struct k_timer *timer)
{
    ARG_UNUSED(timer);
}

/* Convenience typedef for compatibility */
typedef struct k_timer k_timer;

/* Minimal sleep/yield helpers (no-op) */
static inline void k_msleep(uint32_t ms) { ARG_UNUSED(ms); }
static inline void k_yield(void) {}

/* Minimal printk fallback for environments without printk */
#ifndef printk
#include <stdio.h>
#define printk(fmt, ...) ((void)printf((fmt), ##__VA_ARGS__))
#endif