// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#pragma once
#include <condition_variable>
#include <functional>
#include <mutex>
#include <string>

namespace rex::system {
// DiscImageDevice serializes Recover calls. Only the failing guest I/O waits;
// validation/reopening runs on that worker, never on the UI thread.
class GameMediaRecovery {
 public:
  GameMediaRecovery(std::function<bool()> reopen, std::function<void(std::string)> prompt);
  bool Recover();
  void Choose(bool retry);
  void Cancel();

 private:
  std::function<bool()> reopen_;
  std::function<void(std::string)> prompt_;
  std::mutex mutex_;
  std::condition_variable condition_;
  bool stopped_ = false;
  int choice_ = 0;
};
}  // namespace rex::system
