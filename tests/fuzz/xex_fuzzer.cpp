// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <windows.h>

#include <cstdint>
#include <filesystem>
#include <memory>
#include <span>
#include <string>

#include <rex/runtime.h>
#include <rex/system/game_source.h>
#include <rex/system/xex_module.h>

namespace {

using rex::X_STATUS;

rex::Runtime* ToolRuntime() {
  static rex::Runtime* runtime = [] {
    auto root = std::filesystem::temp_directory_path() /
                ("rex_xex_fuzz_" + std::to_string(GetCurrentProcessId()));
    std::filesystem::create_directories(root / "game");
    auto* created = new rex::Runtime(root / "game", root / "users", {}, root / "cache");
    if (created->Setup(rex::RuntimeConfig{.tool_mode = true}) != X_STATUS_SUCCESS) {
      std::abort();
    }
    return created;
  }();
  return runtime;
}

}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const std::span<const uint8_t> bytes(data, size);
  rex::system::XexSourceTitleId(bytes);
  rex::system::XexTitleName(bytes);

  auto* runtime = ToolRuntime();
  auto module = std::make_unique<rex::runtime::XexModule>(runtime->function_dispatcher(),
                                                          runtime->kernel_state());
  if (module->Load("fuzz.xex", "game:\\fuzz.xex", data, size)) {
    module->Unload();
  }
  return 0;
}
