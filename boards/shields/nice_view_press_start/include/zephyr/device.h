#pragma once
/*
 * Minimal zephyr/device.h stub for static analysis and framebuffer-only builds.
 *
 * Provides a tiny subset of the Zephyr device API needed by the shield code:
 *  - an opaque `struct device`
 *  - device_get_binding() helper (no-op stub)
 *
 * This header is intentionally small and safe: it does not attempt to replicate
 * Zephyr's runtime or driver model. It only supplies symbols so source files
 * that include <zephyr/device.h> can be parsed/compiled in environments where
 * Zephyr is not available.
 *
 * WARNING: This is a stub for local development/static analysis only. Do NOT
 * rely on it for real firmware behavior. Use the real Zephyr SDK headers and
 * runtime on device builds.
 */

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Opaque device structure.
 *
 * Real Zephyr exposes a rich `struct device` with driver APIs and state. Here
 * we provide an opaque struct so pointers to devices have a type but no
 * concrete layout.
 */
typedef struct device {
    void *priv; /* opaque pointer for compatibility */
} device;

/* Return type used in many Zephyr APIs */
typedef const device *const_device_ptr_t;

/* device_get_binding()
 *
 * In Zephyr this looks up a device by its DT label and returns a pointer to
 * the device struct if the driver instance is present and initialized.
 *
 * In this stub, the function is implemented as an inline no-op returning NULL.
 * Callers receiving NULL should behave as if the device is not bound/available.
 */
static inline const struct device *device_get_binding(const char *name)
{
    (void)name;
    return NULL;
}

/* device_is_ready()
 *
 * Real Zephyr provides a macro/function to query whether a device is ready.
 * Provide a safe inline that returns false (device not ready) in the stub.
 */
static inline int device_is_ready(const struct device *dev)
{
    (void)dev;
    return 0;
}

/* Helper macro typically used to declare device instances by label.
 * Provide a minimal placeholder so code using DT_LABEL(...) continues to parse.
 * If your build environment defines DT_LABEL(...) differently, the real header
 * will supersede this stub.
 */
#ifndef DT_LABEL
#define DT_LABEL(node_id) ("" /* empty label placeholder */)
#endif

#ifdef __cplusplus
}
#endif