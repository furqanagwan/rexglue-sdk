/**
 * @file        kernel/xam/system_ui.h
 * @brief       Routing the XamShow*UI exports to the host's system shell
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#pragma once

#include <cstdint>
#include <functional>
#include <optional>
#include <string>

namespace rex::kernel::xam {

// On a console these open the dashboard's Guide and its screens. A recompiled
// title has no dashboard, so the host application (a compatibility shell such
// as recomp-framework's XboxGuide) registers a handler and shows its own.
//
// The handler is called from the guest thread that made the call. It must only
// request the screen and return: the export completes asynchronously, because a
// title that waits for the user inside the call would otherwise stall for as
// long as the screen is open (xenia-project/xenia#1296).
enum class SystemUi : uint32_t {
  kGuide,
  kSignIn,
  kAchievements,
  kFriends,
  kMessages,
  kGamerCard,
  kPlayerReview,
  kMarketplace,
};

const char* SystemUiName(SystemUi ui);

// Returns whether the host showed the screen; when it did not, the export
// reports success without doing anything, as the screens are optional.
using SystemUiHandler = std::function<bool(SystemUi ui, uint32_t user_index)>;

void SetSystemUiHandler(SystemUiHandler handler);

// Tells the title that system UI is up or gone (the XN_SYS_UI notification a
// console sends while the Guide is open). Titles pause themselves on it, so the
// host shell raises it while its screens are showing.
void SetSystemUiActive(bool active);
bool HasSystemUiHandler();
bool ShowSystemUi(SystemUi ui, uint32_t user_index);

// XamShowKeyboardUI: the console's on-screen keyboard (vk.xex), which titles open
// to name a save, a player or a team.
struct KeyboardUiRequest {
  uint32_t user_index = 0;
  // The title's VKBD_* flags, passed through unread.
  uint32_t flags = 0;
  std::u16string title;
  std::u16string description;
  std::u16string default_text;
  // Characters the title's buffer holds, not counting its terminator.
  uint32_t max_length = 0;
};

// Called exactly once with what the player entered, or nullopt when they backed
// out. Safe to call from any thread.
using KeyboardUiResult = std::function<void(std::optional<std::u16string> text)>;

// Called on a kernel worker thread while the title's overlapped call is pending.
// Returns whether the host will show a keyboard; when it does not, the call
// completes as cancelled and `done` is never called.
using KeyboardUiHandler = std::function<bool(const KeyboardUiRequest& request,
                                             KeyboardUiResult done)>;

void SetKeyboardUiHandler(KeyboardUiHandler handler);
bool HasKeyboardUiHandler();
// Shows the host keyboard and waits for the player. nullopt when they cancel or
// no host keyboard could be shown.
std::optional<std::u16string> RunKeyboardUi(const KeyboardUiRequest& request);

}  // namespace rex::kernel::xam
