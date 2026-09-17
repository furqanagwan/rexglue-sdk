/**
 * @file        kernel/xam/system_ui.cpp
 * @brief       Routing the XamShow*UI exports to the host's system shell
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#include <rex/kernel/xam/system_ui.h>

#include <condition_variable>
#include <memory>
#include <mutex>

#include <rex/logging.h>
#include <rex/system/kernel_state.h>

namespace rex::kernel::xam {
namespace {

std::mutex g_mutex;
SystemUiHandler g_handler;
KeyboardUiHandler g_keyboard_handler;

}  // namespace

const char* SystemUiName(SystemUi ui) {
  switch (ui) {
    case SystemUi::kGuide:
      return "guide";
    case SystemUi::kSignIn:
      return "sign-in";
    case SystemUi::kAchievements:
      return "achievements";
    case SystemUi::kFriends:
      return "friends";
    case SystemUi::kMessages:
      return "messages";
    case SystemUi::kGamerCard:
      return "gamer card";
    case SystemUi::kPlayerReview:
      return "player review";
    case SystemUi::kMarketplace:
      return "marketplace";
  }
  return "unknown";
}

void SetSystemUiHandler(SystemUiHandler handler) {
  std::lock_guard lock(g_mutex);
  g_handler = std::move(handler);
}

void SetSystemUiActive(bool active) {
  // XN_SYS_UI.
  REX_KERNEL_STATE()->BroadcastNotification(0x9, active);
  REXKRNL_DEBUG("System UI: {}", active ? "shown" : "hidden");
}

bool HasSystemUiHandler() {
  std::lock_guard lock(g_mutex);
  return static_cast<bool>(g_handler);
}

bool ShowSystemUi(SystemUi ui, uint32_t user_index) {
  SystemUiHandler handler;
  {
    std::lock_guard lock(g_mutex);
    handler = g_handler;
  }
  if (!handler) {
    REXKRNL_INFO("System UI: title asked for the {} screen; no host shell is registered",
                 SystemUiName(ui));
    return false;
  }
  const bool shown = handler(ui, user_index);
  REXKRNL_INFO("System UI: title asked for the {} screen for user {} ({})", SystemUiName(ui),
               user_index, shown ? "shown" : "not shown");
  return shown;
}

void SetKeyboardUiHandler(KeyboardUiHandler handler) {
  std::lock_guard lock(g_mutex);
  g_keyboard_handler = std::move(handler);
}

bool HasKeyboardUiHandler() {
  std::lock_guard lock(g_mutex);
  return static_cast<bool>(g_keyboard_handler);
}

std::optional<std::u16string> RunKeyboardUi(const KeyboardUiRequest& request) {
  KeyboardUiHandler handler;
  {
    std::lock_guard lock(g_mutex);
    handler = g_keyboard_handler;
  }
  if (!handler) {
    return std::nullopt;
  }

  // Shared with the callback, which the host calls from its own thread whenever
  // the player finishes; this thread waits for as long as they type.
  struct Completion {
    std::mutex mutex;
    std::condition_variable done;
    bool finished = false;
    std::optional<std::u16string> text;
  };
  auto completion = std::make_shared<Completion>();
  const bool shown = handler(request, [completion](std::optional<std::u16string> text) {
    std::lock_guard lock(completion->mutex);
    if (completion->finished) {
      return;
    }
    completion->text = std::move(text);
    completion->finished = true;
    completion->done.notify_all();
  });
  if (!shown) {
    REXKRNL_INFO("System UI: title asked for the keyboard; the host did not show one");
    return std::nullopt;
  }
  REXKRNL_INFO("System UI: title asked for the keyboard for user {}", request.user_index);

  std::unique_lock lock(completion->mutex);
  completion->done.wait(lock, [&] { return completion->finished; });
  REXKRNL_INFO("System UI: keyboard {}", completion->text ? "entered text" : "cancelled");
  return std::move(completion->text);
}

}  // namespace rex::kernel::xam
