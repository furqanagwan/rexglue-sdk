// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <catch2/catch_test_macros.hpp>
#include <future>
#include <rex/system/game_media_recovery.h>

TEST_CASE("Media recovery retries on the worker and keeps mismatched media pending",
          "[game_source][media_recovery]") {
  int prompts = 0, attempts = 0;
  rex::system::GameMediaRecovery* current = nullptr;
  rex::system::GameMediaRecovery recovery([&] { return ++attempts == 2; },
                                          [&](std::string error) {
                                            ++prompts;
                                            if (prompts == 1)
                                              CHECK(error.empty());
                                            else
                                              CHECK_FALSE(error.empty());
                                            current->Choose(true);
                                          });
  current = &recovery;
  CHECK(recovery.Recover());
  CHECK(prompts == 2);
  CHECK(attempts == 2);
}

TEST_CASE("Leaving media recovery performs no retry", "[game_source][media_recovery]") {
  int attempts = 0;
  rex::system::GameMediaRecovery* current = nullptr;
  rex::system::GameMediaRecovery recovery(
      [&] {
        ++attempts;
        return true;
      },
      [&](std::string) { current->Choose(false); });
  current = &recovery;
  CHECK_FALSE(recovery.Recover());
  CHECK(attempts == 0);
  CHECK_FALSE(recovery.Recover());
}

TEST_CASE("Shutdown cancels a guest I/O worker waiting for media",
          "[game_source][media_recovery]") {
  std::promise<void> shown;
  auto ready = shown.get_future();
  rex::system::GameMediaRecovery recovery([] { return true; },
                                          [&](std::string) { shown.set_value(); });
  auto worker = std::async(std::launch::async, [&] { return recovery.Recover(); });
  struct CancelOnExit {
    rex::system::GameMediaRecovery& recovery;
    ~CancelOnExit() { recovery.Cancel(); }
  } guard{recovery};
  REQUIRE(ready.wait_for(std::chrono::seconds(1)) == std::future_status::ready);
  recovery.Cancel();
  REQUIRE(worker.wait_for(std::chrono::seconds(1)) == std::future_status::ready);
  CHECK_FALSE(worker.get());
}

TEST_CASE("Shutdown during successful media validation does not resume guest I/O",
          "[game_source][media_recovery]") {
  rex::system::GameMediaRecovery* current = nullptr;
  rex::system::GameMediaRecovery recovery(
      [&] {
        current->Cancel();
        return true;
      },
      [&](std::string) { current->Choose(true); });
  current = &recovery;
  CHECK_FALSE(recovery.Recover());
}
