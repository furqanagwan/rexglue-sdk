/**
 * @file        main.cpp
 * @brief       External consumer of an installed GDK build of the SDK (RG-GDK-002)
 *
 * Checks, with only the install tree and the consumer's own GDK: the pinned
 * edition, Gaming Runtime initialization, C++ exceptions unwinding through
 * rexruntime, and the GPU plugin ABI handshake plus its cvars landing in the
 * runtime's registry (one CRT and heap shared by the executable, rexruntime
 * and the plugin). Exits nonzero on the first failure.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/cvar.h>
#include <rex/system/gpu_plugin.h>

// The GDK headers need the Windows headers first; the SDK headers above do
// not include them.
#include <windows.h>

#include <XGameRuntime.h>

#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <string>

static_assert(_GRDK_EDITION == REXGLUE_GDK_EDITION,
              "GDK headers differ from the edition the SDK was built with");

REXCVAR_DEFINE_COMMAND_ARGS(
    gdk_consumer_throw, [](std::string_view args) { throw std::runtime_error(std::string(args)); },
    "Testing", "Throws its argument");

namespace {

int failures = 0;

void Check(bool condition, const char* what) {
  std::printf("%s: %s\n", condition ? "PASS" : "FAIL", what);
  if (!condition) {
    ++failures;
  }
}

}  // namespace

int main() {
  std::printf("GDK edition %d\n", _GRDK_EDITION);

  HRESULT hr = XGameRuntimeInitialize();
  std::printf("XGameRuntimeInitialize: 0x%08X\n", uint32_t(hr));
  Check(SUCCEEDED(hr), "Gaming Runtime initializes unpackaged");
  if (SUCCEEDED(hr)) {
    XGameRuntimeUninitialize();
  }

  bool caught = false;
  try {
    rex::cvar::InvokeCommand("gdk_consumer_throw", "crossed rexruntime");
  } catch (const std::runtime_error& e) {
    caught = std::string(e.what()) == "crossed rexruntime";
  }
  Check(caught, "exception thrown in a callback unwinds through rexruntime");

  auto graphics = rex::system::LoadGpuPlugin("xenos", "d3d12");
  Check(graphics != nullptr, "GPU plugin loads and passes the ABI handshake");
  Check(rex::cvar::GetFlagInfo("readback_memexport") != nullptr,
        "plugin cvars register in the runtime registry");
  Check(rex::cvar::SetFlagByName("readback_memexport", "false") &&
            rex::cvar::GetFlagByName("readback_memexport") == "false",
        "plugin cvar round-trips through the runtime");
  graphics.reset();

  std::printf("%s\n", failures ? "FAILED" : "OK");
  return failures ? 1 : 0;
}
