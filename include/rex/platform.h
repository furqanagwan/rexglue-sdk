/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2020 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#if !defined(_WIN32)
#error ReXGlue supports Windows only (RG-GDK-024).
#endif

#if defined(__clang__)
#define REX_COMPILER_CLANG 1
#elif defined(__GNUC__)
#define REX_COMPILER_GNUC 1
#elif defined(_MSC_VER)
#define REX_COMPILER_MSVC 1
#elif defined(__MINGW32)
#define REX_COMPILER_MINGW32 1
#elif defined(__INTEL_COMPILER)
#define REX_COMPILER_INTEL 1
#else
#define REX_COMPILER_UNKNOWN 1
#endif

#if defined(_M_AMD64) || defined(__amd64__)
#define REX_ARCH_AMD64 1
#elif defined(_M_ARM64) || defined(__aarch64__)
#define REX_ARCH_ARM64 1
#elif defined(_M_IX86) || defined(__i386__) || defined(_M_ARM) || defined(__arm__)
#error Rex is not supported on 32-bit platforms.
#elif defined(_M_PPC) || defined(__powerpc__)
#define REX_ARCH_PPC 1
#endif

#include <intrin.h>

#include <bit>
#include <cstdint>

#if defined(__clang__)

#elif defined(__GNUC__)
#ifndef __builtin_rotateleft32
#define __builtin_rotateleft32(x, n) std::rotl(static_cast<uint32_t>(x), static_cast<int>(n))
#endif
#ifndef __builtin_rotateleft64
#define __builtin_rotateleft64(x, n) std::rotl(static_cast<uint64_t>(x), static_cast<int>(n))
#endif
#ifndef __builtin_debugtrap
#if defined(__x86_64__) || defined(__i386__)
#define __builtin_debugtrap() __asm__ __volatile__("int3")
#else
#define __builtin_debugtrap() __builtin_trap()
#endif
#endif
#endif

#if REX_COMPILER_MSVC
#define _REXPACKEDSCOPE(body) __pragma(pack(push, 1)) body __pragma(pack(pop));
#else
#define _REXPACKEDSCOPE(body)    \
  _Pragma("pack(push, 1)") body; \
  _Pragma("pack(pop)");
#endif

#define REXPACKEDSTRUCT(name, value) _REXPACKEDSCOPE(struct name value)
#define REXPACKEDSTRUCTANONYMOUS(value) _REXPACKEDSCOPE(struct value)
#define REXPACKEDUNION(name, value) _REXPACKEDSCOPE(union name value)

#if REX_COMPILER_CLANG || REX_COMPILER_GNUC
#define REX_HAS_BUILTIN_STRLEN 1
#else
#define REX_HAS_BUILTIN_STRLEN 0
#endif

namespace rex::platform {

inline constexpr char kPathSeparator = '\\';

}
