#pragma once
/*
 * Minimal display driver stubs for static analysis / framebuffer-only builds.
 *
 * This header provides lightweight type definitions and no-op function
 * implementations for a tiny subset of the Zephyr display driver API that
 * the shield code expects:
 *
 *  - struct display_buffer_descriptor
 *  - struct display_capabilities
 *  - display_get_capabilities()
 *  - display_write()
 *
 * These are intentional stubs to allow the repository to be edited and
 * analyzed without a full Zephyr SDK or display driver available. On a real
 * device build with Zephyr, the real display driver headers and functions
 * should be provided by the SDK and will override these inline stubs.
 */

#include <stdint.h>
#include <stddef.h>

#ifdef __has_include
#  if __has_include(<zephyr/device.h>)
#    include <zephyr/device.h>
#  else
/* Minimal fallback for struct device when Zephyr device header isn't present */
typedef struct device {
    void *priv;
} device;
#  endif
#else
typedef struct device {
    void *priv;
} device;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Descriptor describing a buffer to write to the display.
 *
 * - buf_size: size in bytes of the buffer pointed to by `buf` passed to
 *             display_write.
 * - width:    width in pixels of the buffer region described.
 * - height:   height in pixels of the buffer region described.
 * - pitch:    pitch in pixels (distance between starts of consecutive rows).
 *
 * This mirrors the basic descriptor shape used by many display drivers.
 */
struct display_buffer_descriptor {
    size_t buf_size;
    uint16_t width;
    uint16_t height;
    uint16_t pitch; /* pitch in pixels */
};

/* Display capability flags (minimal subset). */
#define SCREEN_INFO_MONO_VTILED (1u << 0) /* display is mono and uses vertical tiling/pages */

/* Basic capabilities returned by drivers */
struct display_capabilities {
    uint32_t x_resolution;
    uint32_t y_resolution;
    uint32_t screen_info;
};

/*
 * display_get_capabilities
 *
 * Query the display device for its capabilities.
 *
 * Returns:
 *  0 on success and fills `caps`,
 * -1 if the device is not present or capabilities cannot be determined.
 *
 * This header provides a conservative inline stub that returns -1 and leaves
 * `caps` zeroed. On a Zephyr build the real driver implementation will be used.
 */
static inline int display_get_capabilities(const struct device *dev, struct display_capabilities *caps)
{
    (void)dev;
    if (caps) {
        caps->x_resolution = 0;
        caps->y_resolution = 0;
        caps->screen_info = 0;
    }
    return -1;
}

/*
 * display_write
 *
 * Write a buffer to the display.
 *
 * Some codebases call a variant that accepts x,y coordinates followed by a
 * descriptor pointer and buffer pointer. Provide a compatible stub here:
 *
 * Parameters:
 *  - dev: display device pointer
 *  - x, y: pixel offset within the device framebuffer where the provided
 *          buffer should be written (drivers may ignore these)
 *  - desc: pointer to a display_buffer_descriptor describing the buffer
 *  - buf:  pointer to the packed framebuffer data
 *
 * Returns:
 *  0 on success, negative error on failure.
 *
 * The inline stub simply returns -1 (no-op). On real hardware builds the
 * platform's display_write implementation will be used instead.
 */
static inline int display_write(const struct device *dev, int x, int y,
                                const struct display_buffer_descriptor *desc, const void *buf)
{
    (void)dev;
    (void)x;
    (void)y;
    (void)desc;
    (void)buf;
    return -1;
}

#ifdef __cplusplus
}
#endif