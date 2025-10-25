/*
 * animation1_frames_mono.c
 *
 * Small compilation unit that includes the generated packed 1bpp frames header
 * so CMake can compile the animation data into the build. The heavy data lives
 * in the included header; this TU provides a tiny symbol referencing the
 * generated arrays to ensure the translation unit is not optimized away.
 *
 * This file intentionally does not re-declare the frame arrays; it relies on
 * the generated header:
 *   boards/shields/nice_view_press_start/include/images/animation1_frames_mono.h
 *
 * The header defines the packed frames (static const uint8_t animation1_frames[][])
 * and the frame count (static const unsigned animation1_frame_count).
 *
 * Including the header here will allocate the frame data into this object file
 * (static linkage) — the draw code in other translation units also includes
 * the header and will reference the same frame definitions compiled into their
 * translation units. This approach avoids linking issues while keeping the
 * generated binary in the build.
 */

#include "../../include/images/animation1_frames_mono.h"

/* Small helper function that touches the generated symbols so the TU is not
 * considered empty by some toolchains/linters. This function is not intended
 * to be called by runtime code; it's provided as a harmless symbol.
 */
void animation1_frames_mono_compile_unit_reference(void) {
    /* Use the frame count and first byte of the first frame to create a side
     * effect-free reference to the generated data.
     */
    (void)animation1_frame_count;
    if (animation1_frame_count > 0) {
        /* Access first byte of first frame (this is safe because header
         * generation guarantees frames have the expected size).
         */
        volatile uint8_t probe = animation1_frames[0][0];
        (void)probe;
    }
}