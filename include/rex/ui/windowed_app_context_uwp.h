/**
 * @file        ui/windowed_app_context_uwp.h
 * @brief       CoreWindow implementation of the windowed app UI loop context
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <atomic>
#include <functional>
#include <memory>

#include <winrt/Windows.UI.Core.h>

#include <rex/ui/windowed_app_context.h>

namespace rex::ui {

class UWPWindowedAppContext final : public WindowedAppContext {
 public:
  explicit UWPWindowedAppContext(winrt::Windows::UI::Core::CoreWindow core_window);
  ~UWPWindowedAppContext() override;

  const winrt::Windows::UI::Core::CoreWindow& core_window() const { return core_window_; }

  void NotifyUILoopOfPendingFunctions() override;
  void PlatformQuitFromUIThread() override;

  int RunMainMessageLoop();

  void RunOnDispatcher(std::function<void()> function);

 private:
  winrt::Windows::UI::Core::CoreWindow core_window_;
  winrt::Windows::UI::Core::CoreDispatcher dispatcher_;
  std::shared_ptr<std::atomic<bool>> accepting_dispatch_;
  std::atomic<bool> wakeup_pending_{false};
};

}  // namespace rex::ui
