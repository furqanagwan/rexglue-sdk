/**
 * @file        runtime.h
 * @brief       Runtime subsystem entry point
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 * @remarks     Based on Xenia emulator.h/cc
 */

#pragma once

#include <filesystem>
#include <functional>
#include <memory>
#include <optional>
#include <span>
#include <string>

#include <rex/cvar.h>
#include <rex/embedded_metadata.h>
#include <rex/filesystem/vfs.h>
#include <rex/memory.h>
#include <rex/system/export_resolver.h>
#include <rex/system/interfaces/audio.h>
#include <rex/system/interfaces/graphics.h>
#include <rex/system/interfaces/input.h>
#include <rex/system/kernel_state.h>
#include <rex/system/kernel_object.h>

struct PPCFuncMapping;

#include <rex/image_info.h>

REXCVAR_DECLARE(std::string, game_data_root);
REXCVAR_DECLARE(std::string, user_data_root);
REXCVAR_DECLARE(std::string, update_data_root);
REXCVAR_DECLARE(std::string, cache_root);
REXCVAR_DECLARE(std::string, metadata_root);

namespace rex {

namespace runtime {
class FunctionDispatcher;
class ExportResolver;
}
namespace system {
class KernelState;
class XThread;
}
namespace ui {
class WindowedAppContext;
class Window;
class ImGuiDrawer;
}

struct RuntimeConfig {
  std::unique_ptr<system::IGraphicsSystem> graphics;

  std::string gpu_plugin;
  std::function<std::unique_ptr<system::IAudioSystem>(runtime::FunctionDispatcher*)> audio_factory;
  std::function<std::unique_ptr<system::IInputSystem>(bool tool_mode)> input_factory;
  std::function<void(Runtime*, system::KernelState*)> kernel_init;
  bool tool_mode = false;
};

#define REX_GRAPHICS_BACKEND(Type) std::make_unique<Type>()
#define REX_AUDIO_BACKEND(Type)                                                                 \
  [](::rex::runtime::FunctionDispatcher* _fd) -> std::unique_ptr<::rex::system::IAudioSystem> { \
    return Type::Create(_fd);                                                                   \
  }
#define REX_INPUT_BACKEND(SetupFunc)                                    \
  [](bool _tool_mode) -> std::unique_ptr<::rex::system::IInputSystem> { \
    return SetupFunc(_tool_mode);                                       \
  }

class Runtime {
 public:
  explicit Runtime(const std::filesystem::path& game_data_root,
                   const std::filesystem::path& user_data_root = {},
                   const std::filesystem::path& update_data_root = {},
                   const std::filesystem::path& cache_root = {},
                   const std::filesystem::path& metadata_root = {});
  ~Runtime();

  Runtime(const Runtime&) = delete;
  Runtime& operator=(const Runtime&) = delete;

  static Runtime* instance();

  memory::Memory* memory() const { return memory_.get(); }
  rex::filesystem::VirtualFileSystem* file_system() const { return file_system_.get(); }
  system::KernelState* kernel_state() const { return kernel_state_.get(); }
  system::IGraphicsSystem* graphics_system() const { return graphics_system_.get(); }
  system::IAudioSystem* audio_system() const { return audio_system_.get(); }
  system::IInputSystem* input_system() const { return input_system_.get(); }

  runtime::FunctionDispatcher* function_dispatcher() const { return function_dispatcher_.get(); }

  runtime::ExportResolver* export_resolver() const { return export_resolver_.get(); }

  const std::filesystem::path& game_data_root() const { return game_data_root_; }
  const std::filesystem::path& user_data_root() const { return user_data_root_; }
  const std::filesystem::path& update_data_root() const { return update_data_root_; }
  const std::filesystem::path& cache_root() const { return cache_root_; }
  const std::filesystem::path& metadata_root() const { return metadata_root_; }

  std::optional<std::filesystem::path> FindMetadataPath(
      const std::filesystem::path& relative_path) const;
  std::optional<EmbeddedMetadataAsset> FindEmbeddedMetadata(
      const std::filesystem::path& relative_path) const;

  void set_app_context(ui::WindowedAppContext* context) { app_context_ = context; }
  ui::WindowedAppContext* app_context() const { return app_context_; }

  void set_display_window(ui::Window* window) { display_window_ = window; }
  ui::Window* display_window() const { return display_window_; }
  void set_imgui_drawer(ui::ImGuiDrawer* drawer) { imgui_drawer_ = drawer; }
  ui::ImGuiDrawer* imgui_drawer() const { return imgui_drawer_; }

  X_STATUS Setup(RuntimeConfig config = {});

  X_STATUS Setup(const PPCImageInfo& image_info, RuntimeConfig config = {});

  const PPCCodegenFlags& codegen_flags() const { return codegen_flags_; }

  bool is_tool_mode() const { return tool_mode_; }

  void Shutdown();

  X_STATUS LoadXexImage(const std::string_view module_path);

  system::object_ref<system::XThread> LaunchModule();

  system::object_ref<system::XThread> PrepareModuleLaunch();

  uint8_t* virtual_membase() const;

 private:
  bool SetupVfs();

  std::filesystem::path game_data_root_;
  std::filesystem::path user_data_root_;
  std::filesystem::path update_data_root_;
  std::filesystem::path cache_root_;
  std::filesystem::path metadata_root_;

  ui::WindowedAppContext* app_context_ = nullptr;
  ui::Window* display_window_ = nullptr;
  ui::ImGuiDrawer* imgui_drawer_ = nullptr;
  bool tool_mode_ = false;
  PPCCodegenFlags codegen_flags_{};
  bool setup_complete_ = false;

  std::unique_ptr<memory::Memory> memory_;
  std::unique_ptr<runtime::FunctionDispatcher> function_dispatcher_;
  std::unique_ptr<rex::filesystem::VirtualFileSystem> file_system_;
  std::unique_ptr<system::KernelState> kernel_state_;
  std::unique_ptr<system::IGraphicsSystem> graphics_system_;
  std::unique_ptr<system::IAudioSystem> audio_system_;
  std::unique_ptr<system::IInputSystem> input_system_;
  std::unique_ptr<runtime::ExportResolver> export_resolver_;

  static Runtime* instance_;
};

}
