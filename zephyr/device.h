/*
 * zephyr/device.h
 *
 * Minimal Zephyr device header stub for static analysis within the
 * nice-view-press-start project. This is NOT a replacement for the real
 * Zephyr headers — it only provides a small set of types and helper
 * declarations so the codebase can be parsed / compiled by tools while
 * porting. Remove or guard these stubs before performing a real Zephyr build.
 */

#ifndef NICE_VIEW_PRESS_START_ZEPHYR_DEVICE_H
#define NICE_VIEW_PRESS_START_ZEPHYR_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

/* Opaque device structure.
 *
 * Real Zephyr exposes a much richer `struct device` (or `struct device *`)
 * type. For our purposes a minimal, lightweight representation that can be
 * used as a pointer is sufficient.
 */
struct device {
    const char *name;
    int _stub;
};

/* device_get_binding
 *
 * In Zephyr this returns a pointer to the device object for the requested
 * device label, or NULL if the device is not found. Provide a header-level
 * inline stub so callers compile. The real implementation is provided by the
 * Zephyr runtime / board support code and will replace this stub in real
 * builds.
 */
static inline const struct device *device_get_binding(const char *name)
{
    (void)name;
    return NULL;
}

/* Helper often used in Zephyr code to check if a device pointer is valid. */
static inline int device_is_ready(const struct device *dev)
{
    /* In the stub we consider NULL as not ready; any non-NULL may be treated
     * as ready by higher-level static analysis. */
    return dev != NULL;
}

#ifdef __cplusplus
}
#endif

#endif /* NICE_VIEW_PRESS_START_ZEPHYR_DEVICE_H */