/**
 * @file        ppc/backtrace.h
 * @brief       Return addresses of the guest functions on the calling thread
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#pragma once

#include <cstddef>
#include <cstdint>

namespace rex::ppc {

// The deepest guest backtrace anything in the SDK asks for. Long enough to get
// past a graphics library's own layers and reach the engine code that called
// into it, short enough to store one per sample without thinking about it.
inline constexpr size_t kMaxGuestBacktrace = 16;

// Writes the return addresses of the guest frames below the calling thread,
// innermost first, and returns how many were written. Zero when the thread is
// not a guest thread or its stack does not look like a chain of frames.
//
// It reads the guest stack, which the guest can have left in any state, so it
// stops at the first frame that does not make sense rather than trusting what
// it finds. The addresses are return addresses, so each one is inside the
// function that made the call, a few instructions past the call itself.
size_t CaptureGuestBacktrace(uint32_t* frames, size_t max_frames);

}  // namespace rex::ppc
