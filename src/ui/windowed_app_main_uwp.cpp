/**
 * @file        ui/windowed_app_main_uwp.cpp
 * @brief       Entry point for windowed applications (Universal Windows Platform)
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include <cstdlib>
#include <map>
#include <memory>
#include <string>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <unknwn.h>

#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Core.h>

#include <rex/cvar.h>
#include <rex/logging.h>
#include <rex/ui/windowed_app.h>
#include <rex/ui/windowed_app_context_uwp.h>

namespace {

using winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs;
using winrt::Windows::ApplicationModel::Core::CoreApplication;
using winrt::Windows::ApplicationModel::Core::CoreApplicationView;
using winrt::Windows::ApplicationModel::Core::IFrameworkView;
using winrt::Windows::ApplicationModel::Core::IFrameworkViewSource;
using winrt::Windows::UI::Core::CoreWindow;

int exit_code = EXIT_SUCCESS;

int RunWindowedApp(const CoreWindow& core_window) {
  std::string program_name = "rexglue";
  char* argv[] = {program_name.data(), nullptr};
  rex::cvar::Init(1, argv);
  rex::InitLoggingEarly();

  int result;
  {
    rex::ui::UWPWindowedAppContext app_context(core_window);
    std::unique_ptr<rex::ui::WindowedApp> app = rex::ui::GetWindowedAppCreator()(app_context);
    app->SetParsedArguments({});
    result = app->OnInitialize() ? app_context.RunMainMessageLoop() : EXIT_FAILURE;
    app->InvokeOnDestroy();
  }
  return result;
}

struct RexFrameworkView : winrt::implements<RexFrameworkView, IFrameworkView> {
  void Initialize(const CoreApplicationView& application_view) {
    application_view.Activated([](const CoreApplicationView&, const IActivatedEventArgs&) {
      CoreWindow::GetForCurrentThread().Activate();
    });
  }

  void SetWindow(const CoreWindow& window) { window_ = window; }

  void Load(const winrt::hstring&) {}

  void Run() { exit_code = RunWindowedApp(window_); }

  void Uninitialize() {}

 private:
  CoreWindow window_{nullptr};
};

struct RexFrameworkViewSource : winrt::implements<RexFrameworkViewSource, IFrameworkViewSource> {
  IFrameworkView CreateView() { return winrt::make<RexFrameworkView>(); }
};

}  // namespace

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int) {
  winrt::init_apartment();
  CoreApplication::Run(winrt::make<RexFrameworkViewSource>());
  return exit_code;
}
