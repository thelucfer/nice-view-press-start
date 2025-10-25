#pragma once
/*
 * Minimal zephyr/sys/printk.h stub for static analysis and framebuffer-only builds.
 *
 * Provides a lightweight, POSIX-backed implementation of `printk` using
 * standard I/O. This is intended only for editing, static analysis and
 * local development where Zephyr is not available. On real Zephyr builds,
 * the platform's printk implementation and header should be used instead.
 */

#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * printk: basic printf-like logging helper.
 *
 * Signature mirrors the common Zephyr `printk` usage:
 *   int printk(const char *fmt, ...);
 *
 * This stub forwards to vprintf and returns the result of vprintf.
 */
static inline int printk(const char *fmt, ...)
{
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = vprintf(fmt, ap);
    va_end(ap);
    return ret;
}

/*
 * hexdump-like helper (optional convenience).
 * Many Zephyr examples use sys_printk or printk-only; include a tiny helper
 * to print a hex buffer if code expects it. This is not part of Zephyr's
 * official API but can be handy during porting.
 */
static inline void printk_hexdump(const void *buf, size_t len)
{
    const unsigned char *b = (const unsigned char *)buf;
    for (size_t i = 0; i < len; ++i) {
        printf("%02X ", b[i]);
        if ((i & 0x0F) == 0x0F) {
            printf("\n");
        }
    }
    if (len && (len & 0x0F)) {
        printf("\n");
    }
}

/* Fallback for older code that expects SYS_LOG or similar macro */
#ifndef LOG_ERR
#define LOG_ERR(...) printk(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif