/**
 * @file        ui/windowed_app_context_uwp.cpp
 * @brief       CoreWindow implementation of the windowed app UI loop context
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include <rex/ui/windowed_app_context_uwp.h>

#include <cstdlib>
#include <utility>

#include <winrt/Windows.Foundation.h>

namespace rex::ui {

using winrt::Windows::UI::Core::CoreDispatcherPriority;
using winrt::Windows::UI::Core::CoreProcessEventsOption;

UWPWindowedAppContext::UWPWindowedAppContext(winrt::Windows::UI::Core::CoreWindow core_window)
    : core_window_(std::move(core_window)),
      dispatcher_(core_window_.Dispatcher()),
      accepting_dispatch_(std::make_shared<std::atomic<bool>>(true)) {}

UWPWindowedAppContext::~UWPWindowedAppContext() {
  accepting_dispatch_->store(false);
  ExecutePendingFunctionsFromUIThread();
}

void UWPWindowedAppContext::RunOnDispatcher(std::function<void()> function) {
  auto accepting = accepting_dispatch_;
  dispatcher_.RunAsync(CoreDispatcherPriority::Normal,
                       [accepting, function = std::move(function)]() {
                         if (accepting->load()) {
                           function();
                         }
                       });
}

void UWPWindowedAppContext::NotifyUILoopOfPendingFunctions() {
  if (wakeup_pending_.exchange(true)) {
    return;
  }
  RunOnDispatcher([this]() {
    wakeup_pending_.store(false);
    ExecutePendingFunctionsFromUIThread();
  });
}

void UWPWindowedAppContext::PlatformQuitFromUIThread() {
  wakeup_pending_.store(false);
  NotifyUILoopOfPendingFunctions();
}

int UWPWindowedAppContext::RunMainMessageLoop() {
  while (!HasQuitFromUIThread()) {
    dispatcher_.ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);
  }
  accepting_dispatch_->store(false);
  return EXIT_SUCCESS;
}

}  // namespace rex::ui
