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
MessageBoxUiHandler g_message_box_handler;

// Hands a request to the host and waits on this (kernel worker) thread until the
// host reports what the player did, for as long as that takes. The host calls
// back from its own thread; a second call is ignored.
template <typename Value, typename Request, typename Handler>
std::optional<Value> RunHostUi(const Handler& handler, const Request& request, const char* what) {
  if (!handler) {
    return std::nullopt;
  }
  struct Completion {
    std::mutex mutex;
    std::condition_variable done;
    bool finished = false;
    std::optional<Value> value;
  };
  auto completion = std::make_shared<Completion>();
  const bool shown = handler(request, [completion](std::optional<Value> value) {
    std::lock_guard lock(completion->mutex);
    if (completion->finished) {
      return;
    }
    completion->value = std::move(value);
    completion->finished = true;
    completion->done.notify_all();
  });
  if (!shown) {
    REXKRNL_INFO("System UI: title asked for the {}; the host did not show one", what);
    return std::nullopt;
  }
  REXKRNL_INFO("System UI: title asked for the {} for user {}", what, request.user_index);

  std::unique_lock lock(completion->mutex);
  completion->done.wait(lock, [&] { return completion->finished; });
  REXKRNL_INFO("System UI: {} {}", what, completion->value ? "answered" : "cancelled");
  return std::move(completion->value);
}

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
  return RunHostUi<std::u16string>(handler, request, "keyboard");
}

void SetMessageBoxUiHandler(MessageBoxUiHandler handler) {
  std::lock_guard lock(g_mutex);
  g_message_box_handler = std::move(handler);
}

bool HasMessageBoxUiHandler() {
  std::lock_guard lock(g_mutex);
  return static_cast<bool>(g_message_box_handler);
}

std::optional<uint32_t> RunMessageBoxUi(const MessageBoxUiRequest& request) {
  MessageBoxUiHandler handler;
  {
    std::lock_guard lock(g_mutex);
    handler = g_message_box_handler;
  }
  return RunHostUi<uint32_t>(handler, request, "message box");
}

}  // namespace rex::kernel::xam
