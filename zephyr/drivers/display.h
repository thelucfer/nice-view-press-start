/*
 * zephyr/drivers/display.h
 *
 * Minimal Zephyr display driver header stub used for static analysis and
 * framebuffer-only builds in the nice-view-press-start project.
 *
 * This header provides a tiny subset of the real Zephyr display API so the
 * shield code (oled_fb.c and friends) can be parsed and analyzed outside of a
 * full Zephyr SDK. It is NOT a replacement for the real Zephyr headers and
 * should be removed or guarded when performing an actual Zephyr build.
 */

#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Display capability flags (very small subset).
 *
 * The real Zephyr headers define many more bits and fields. Provide the ones
 * referenced by the shield code so static analysis can reason about them.
 */
#define SCREEN_INFO_MONO_VTILED (1u << 0) /* monochrome, vertical tiled framebuffer */

/* Minimal device type forward declaration (see zephyr/device.h stub). */
struct device;

/* Display capabilities reported by drivers (trimmed to fields we use). */
struct display_capabilities {
    uint16_t x_resolution;
    uint16_t y_resolution;
    uint32_t screen_info; /* driver-specific flags such as SCREEN_INFO_* */
};

/* Descriptor describing a buffer being written to the display.
 *
 * Fields mirror the real Zephyr structure sufficiently for the shield code:
 * - buf_size: total number of bytes pointed to by buf
 * - width/height: pixel dimensions described by the buffer
 * - pitch: number of pixels between successive rows in the buffer (in pixels)
 */
struct display_buffer_descriptor {
    size_t buf_size;
    uint16_t width;
    uint16_t height;
    uint16_t pitch;
};

/* Get display capabilities.
 *
 * In the real Zephyr API this fills `caps` with the device's capabilities and
 * returns 0 on success. Provide a simple inline stub that returns -1 to
 * indicate capabilities are not available in this analysis stub.
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

/* Write a buffer to the display at the given (x,y) origin.
 *
 * Real API returns 0 on success. The stub returns -1 to indicate the operation
 * is not performed in the analysis environment.
 */
static inline int display_write(const struct device *dev, uint16_t x, uint16_t y,
                                const struct display_buffer_descriptor *desc, const void *buf)
{
    (void)dev;
    (void)x;
    (void)y;
    (void)desc;
    (void)buf;
    return -1;
}

/* Convenience: some code checks for presence of the driver by testing return
 * equality with zero. Provide a macro for success code used in the stubs. */
#define DISPLAY_SUCCESS 0

#ifdef __cplusplus
}
#endif