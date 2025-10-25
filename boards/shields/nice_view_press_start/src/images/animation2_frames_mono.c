/*
 * animation2_frames_mono.c
 *
 * Small compilation unit that includes the generated packed 1bpp frames header
 * so CMake can compile the animation data into the build. The heavy data lives
 * in the included header; this TU provides a tiny symbol referencing the
 * generated arrays to ensure the translation unit is not considered empty.
 *
 * The generated header path:
 *   boards/shields/nice_view_press_start/include/images/animation2_frames_mono.h
 *
 * The header defines:
 *   - static const uint8_t animation2_frames[][BYTES_PER_FRAME] = { ... };
 *   - static const unsigned animation2_frame_count = N;
 *
 * Including the header here causes the frame data to be part of this object
 * file. The draw code in other translation units includes the header as well
 * and will reference the same definitions.
 */

#include "../../include/images/animation2_frames_mono.h"
#include <stdint.h>

/* Provide a small non-inlined symbol that references the generated data so the
 * compiler/linker keeps the translation unit. This function is safe to exist
 * even if not called at runtime.
 */
void animation2_frames_mono_compile_unit_reference(void) {
    /* Use the frame count to create a harmless reference to the generated symbol. */
    (void)animation2_frame_count;

    /* If frames exist, touch the first byte of the first frame to ensure the
     * frame data is actually referenced by this TU. Use volatile to prevent
     * the compiler from optimizing away the load.
     */
    if (animation2_frame_count > 0) {
        volatile uint8_t probe = animation2_frames[0][0];
        (void)probe;
    }
}