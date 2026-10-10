/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2021 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#include <cstddef>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <rex/assert.h>
#include <rex/platform.h>
#include <rex/ui/windowed_app_context.h>

namespace rex {
namespace ui {

class WindowedApp {
 public:
  using Creator =
      std::unique_ptr<rex::ui::WindowedApp> (*)(rex::ui::WindowedAppContext& app_context);

  WindowedApp(const WindowedApp& app) = delete;
  WindowedApp& operator=(const WindowedApp& app) = delete;
  virtual ~WindowedApp() = default;

  WindowedAppContext& app_context() const { return app_context_; }

  const std::string& GetName() const { return name_; }
  const std::string& GetPositionalOptionsUsage() const { return positional_options_usage_; }
  const std::vector<std::string>& GetPositionalOptions() const { return positional_options_; }

  void SetParsedArguments(std::map<std::string, std::string> args) {
    parsed_args_ = std::move(args);
  }

  std::optional<std::string> GetArgument(const std::string& name) const {
    auto it = parsed_args_.find(name);
    if (it != parsed_args_.end()) {
      return it->second;
    }
    return std::nullopt;
  }

  virtual bool OnInitialize() = 0;

  void InvokeOnDestroy() {
    app_context().ExecutePendingFunctionsFromUIThread();
    OnDestroy();
  }

 protected:
  explicit WindowedApp(WindowedAppContext& app_context, const std::string_view name,
                       const std::string_view positional_options_usage = std::string_view())
      : app_context_(app_context),
        name_(name),
        positional_options_usage_(positional_options_usage) {}

  void AddPositionalOption(const std::string_view option) {
    positional_options_.emplace_back(option);
  }

  virtual void OnDestroy() {}

 private:
  WindowedAppContext& app_context_;

  std::string name_;
  std::string positional_options_usage_;
  std::vector<std::string> positional_options_;

  std::map<std::string, std::string> parsed_args_;

#if XE_UI_WINDOWED_APPS_IN_LIBRARY
 public:
  class CreatorRegistration {
   public:
    CreatorRegistration(const std::string_view identifier, Creator creator) {
      if (!creators_) {
        creators_ = new std::unordered_map<std::string, WindowedApp::Creator>;
      }
      iterator_inserted_ = creators_->emplace(identifier, creator);
      assert_true(iterator_inserted_.second);
    }

    ~CreatorRegistration() {
      if (iterator_inserted_.second) {
        creators_->erase(iterator_inserted_.first);
        if (creators_->empty()) {
          delete creators_;
        }
      }
    }

   private:
    std::pair<std::unordered_map<std::string, Creator>::iterator, bool> iterator_inserted_;
  };

  static Creator GetCreator(const std::string& identifier) {
    if (!creators_) {
      return nullptr;
    }
    auto it = creators_->find(identifier);
    return it != creators_->end() ? it->second : nullptr;
  }

 private:
  static std::unordered_map<std::string, Creator>* creators_;
#endif
};

#if XE_UI_WINDOWED_APPS_IN_LIBRARY

#define REX_DEFINE_APP(identifier, creator)                                   \
  namespace rex {                                                             \
  namespace ui {                                                              \
  namespace windowed_app_creator_registrations {                              \
  rex::ui::WindowedApp::CreatorRegistration identifier(#identifier, creator); \
  }                                                                           \
  }                                                                           \
  }
#else

std::unique_ptr<WindowedApp> (*GetWindowedAppCreator())(WindowedAppContext& app_context);
#define REX_DEFINE_APP(identifier, creator)                        \
  rex::ui::WindowedApp::Creator rex::ui::GetWindowedAppCreator() { \
    return creator;                                                \
  }
#endif

#define XE_DEFINE_WINDOWED_APP(identifier, creator) REX_DEFINE_APP(identifier, creator)

}
}
