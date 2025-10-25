/*
 * zephyr/kernel.h
 *
 * Minimal Zephyr kernel header stub for static analysis within the
 * nice-view-press-start project. This is NOT a replacement for the real
 * Zephyr headers — it only provides a small set of types, macros and
 * no-op helper functions so the codebase can be parsed / compiled by
 * tools that expect the presence of <zephyr/kernel.h>.
 *
 * Keep the definitions intentionally small and conservative.
 */

#ifndef NICE_VIEW_PRESS_START_ZEPHYR_KERNEL_H
#define NICE_VIEW_PRESS_START_ZEPHYR_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* Time-related helpers
 *
 * In Zephyr K_* macros expand to timeout objects; for static analysis
 * we keep them as integer millisecond values.
 */
typedef int64_t k_timeout_t;

#define K_NO_WAIT 0
#define K_FOREVER (-1)

/* Convenience macros used in many places */
#define K_MSEC(x) ((int)(x))
#define K_SECONDS(x) ((int)((x) * 1000))

/* Sleep / delay helpers (no-op implementations) */
static inline int k_msleep(int ms)
{
    (void)ms;
    return 0;
}

static inline void k_sleep(int ms)
{
    (void)ms;
}

/* Uptime (returns 0 in stub) */
static inline uint64_t k_uptime_get(void)
{
    return 0ULL;
}

/* Basic kernel synchronization primitives (stubs) */

/* Mutex */
typedef struct {
    int _opaque;
} k_mutex_t;

static inline void k_mutex_init(k_mutex_t *m)
{
    (void)m;
}

static inline int k_mutex_lock(k_mutex_t *m, int timeout_ms)
{
    (void)m; (void)timeout_ms;
    return 0;
}

static inline int k_mutex_unlock(k_mutex_t *m)
{
    (void)m;
    return 0;
}

/* Semaphore */
typedef struct {
    int _opaque;
} k_sem;

static inline void k_sem_init(k_sem *s, unsigned int initial_count, unsigned int limit)
{
    (void)s; (void)initial_count; (void)limit;
}

static inline int k_sem_take(k_sem *s, int timeout_ms)
{
    (void)s; (void)timeout_ms;
    return 0;
}

static inline void k_sem_give(k_sem *s)
{
    (void)s;
}

/* Timer (very small shim) */
typedef struct {
    void (*_handler)(struct _k_timer *); /* not used in stub */
    int _opaque;
} k_timer;

static inline void k_timer_init(k_timer *t, void (*handler)(k_timer *), void (*stop_handler)(k_timer *))
{
    (void)t; (void)handler; (void)stop_handler;
}

static inline void k_timer_start(k_timer *t, int32_t duration_ms, int32_t period_ms)
{
    (void)t; (void)duration_ms; (void)period_ms;
}

static inline void k_timer_stop(k_timer *t)
{
    (void)t;
}

/* Thread / stack helper stubs */
typedef struct {
    int _opaque;
} k_thread;

#define K_THREAD_STACK_DEFINE(name, size) \
    static uint8_t name[(size)]

/* Workqueue / work item minimal stubs */
typedef struct {
    int _opaque;
} k_work;

static inline void k_work_init(k_work *work, void (*handler)(k_work *))
{
    (void)work; (void)handler;
}

static inline int k_work_submit(k_work *work)
{
    (void)work;
    return 0;
}

/* Simple helper used by some codebases */
#define ARG_UNUSED(x) ((void)(x))

#ifdef __cplusplus
}
#endif

#endif /* NICE_VIEW_PRESS_START_ZEPHYR_KERNEL_H */