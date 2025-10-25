#pragma once
/*
 * nice-view-press-start/zephyr/devicetree.h
 *
 * Minimal devicetree/stub header for static analysis in the framebuffer-only
 * port of the nice!view Press Start shield. This file provides a tiny subset
 * of the Zephyr devicetree macro surface so source files that use the usual
 * DT_* macros can be parsed without a full Zephyr SDK.
 *
 * Notes:
 *  - This is only a header-level stub for editing, static analysis and local
 *    development. It is NOT a replacement for the real Zephyr devicetree
 *    headers and should not be used for actual firmware builds.
 *  - The macros intentionally produce safe, neutral values (usually 0 or an
 *    empty string) so downstream conditional checks evaluate predictably.
 */

#ifndef NICE_VIEW_PRESS_START_ZEPHYR_DEVICETREE_H
#define NICE_VIEW_PRESS_START_ZEPHYR_DEVICETREE_H

#include <stddef.h>

/* ----------------------
 * Generic helpers
 * ---------------------- */

/* Token concatenation helpers used to build symbol names from macro args. */
#define __NICEV_CAT(a, b) a##b
#define _NICEV_CAT(a, b) __NICEV_CAT(a, b)

/* Convert an argument into a token suitable for use in #ifdef/#if tests.
 * Real Zephyr uses complex macros that map names to generated symbols; the
 * pattern below mimics that behaviour enough for static analysis purposes.
 */
#define DT_ALIAS(x) _NICEV_CAT(DT_ALIAS_, x)
#define DT_NODELABEL(x) _NICEV_CAT(DT_NODELABEL_, x)
#define DT_CHOSEN(x) _NICEV_CAT(DT_CHOSEN_, x)
#define DT_INST(inst, compat) _NICEV_CAT(_NICEV_CAT(DT_INST_, inst), _##compat)

/* Evaluate existence of a node. Return 0 (not present) by default. */
#define DT_NODE_EXISTS(node) 0

/* Return a label string for a node. Provide empty string fallback. */
#define DT_LABEL(node) ""

/* DT alias/compat/status helpers used in some source files. Return safe 0. */
#define DT_HAS_COMPAT_STATUS_OKAY(compat) 0
#define DT_DRV_COMPAT_whatever 0  /* innocuous if referenced in #ifdef */

#define DT_ALIAS_ssd1306 0
#define DT_NODELABEL_ssd1306 0
#define DT_CHOSEN_zmk_display 0
#define DT_INST_0_solomon_ssd1306fb 0

/* DT_ALIAS macro may be used in an `#ifdef DT_ALIAS(name)` form in code.
 * The pattern above (DT_ALIAS(x) => DT_ALIAS_x) together with the concrete
 * DT_ALIAS_ssd1306 symbol defined above makes that usage valid for the
 * common `ssd1306` alias used in our shield code.
 */

/* A convenience macro used by some Zephyr-based projects. Keep it defined. */
#ifndef DT_PROP
#define DT_PROP(node, prop) 0
#endif

/* Some code checks DT_NODE_EXISTS(DT_ALIAS(name)) using our function-like
 * macros; since DT_NODE_EXISTS returns 0 we safely indicate absent nodes.
 */

/* ----------------------
 * Specific stub symbols
 * ---------------------- */

/* Provide explicit stub symbols used by the OLED helper so the preprocessor
 * conditionals in the shield code can be evaluated without errors. These
 * expand to neutral values indicating the relevant devicetree nodes are not
 * present in the analysis environment.
 */
#define DT_ALIAS_ssd1306 0
#define DT_NODELABEL_ssd1306 0
#define DT_CHOSEN_zmk_display 0
#define DT_INST_0_solomon_ssd1306fb 0

/* ----------------------
 * Safety / compatibility
 * ---------------------- */

/* In some translation units the code may test for DT_ALIAS(x) using
 * `#ifdef DT_ALIAS(x)`. To ensure the preprocessor sees a defined macro name
 * when that pattern is used, we also define the plain `DT_ALIAS` macro name
 * (function-like) above. The existence of this macro allows constructs like
 * `#ifdef DT_ALIAS(ssd1306)` to be processed in the same way as Zephyr's
 * headers do (they expand to a generated identifier).
 *
 * Reminder: this header is for static-analysis only. Remove it or guard it
 * out when compiling with a real Zephyr SDK / devicetree.
 */

#endif /* NICE_VIEW_PRESS_START_ZEPHYR_DEVICETREE_H */