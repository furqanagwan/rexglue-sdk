/**
 * @file        kernel/xam/system_ui.cpp
 * @brief       Routing the XamShow*UI exports to the host's system shell
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#include <rex/kernel/xam/system_ui.h>

#include <mutex>

#include <rex/logging.h>
#include <rex/system/kernel_state.h>

namespace rex::kernel::xam {
namespace {

std::mutex g_mutex;
SystemUiHandler g_handler;

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

}  // namespace rex::kernel::xam
