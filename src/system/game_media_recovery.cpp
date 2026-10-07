// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <rex/system/game_media_recovery.h>

namespace rex::system {
GameMediaRecovery::GameMediaRecovery(std::function<bool()> reopen,
                                     std::function<void(std::string)> prompt)
    : reopen_(std::move(reopen)), prompt_(std::move(prompt)) {}
bool GameMediaRecovery::Recover() {
  std::string error;
  for (;;) {
    {
      std::lock_guard lock(mutex_);
      if (stopped_)
        return false;
      choice_ = 0;
    }
    prompt_(error);
    std::unique_lock lock(mutex_);
    condition_.wait(lock, [this] { return stopped_ || choice_; });
    if (stopped_ || choice_ < 0)
      return false;
    lock.unlock();
    try {
      if (reopen_()) {
        std::lock_guard resumed_lock(mutex_);
        return !stopped_;
      }
      error =
          "The source is unavailable or does not match the original disc. Reinsert the same disc "
          "and retry.";
    } catch (const std::exception& exception) {
      error = exception.what();
    }
  }
}
void GameMediaRecovery::Choose(bool retry) {
  {
    std::lock_guard lock(mutex_);
    choice_ = retry ? 1 : -1;
    if (!retry)
      stopped_ = true;
  }
  condition_.notify_all();
}
void GameMediaRecovery::Cancel() {
  {
    std::lock_guard lock(mutex_);
    stopped_ = true;
  }
  condition_.notify_all();
}
}  // namespace rex::system
