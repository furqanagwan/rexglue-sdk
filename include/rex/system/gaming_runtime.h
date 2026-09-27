/**
 * @file        rex/system/gaming_runtime.h
 * @brief       Application-owned Microsoft Gaming Runtime lifecycle (RG-GDK-022)
 *
 * The title, not the guest, owns the host Gaming Runtime: it is initialized
 * once before the guest runtime starts and uninitialized after the guest's
 * audio, input and GPU services are gone. Guest XAM profiles never map to
 * host Xbox services identities.
 *
 * XGameRuntimeInitialize has been seen to stall for over 60 s on a working
 * machine (docs/gdk-toolchain.md), so Initialize runs it on a worker thread
 * and gives up after a timeout. A call that completes after the caller gave
 * up is balanced with an uninitialize by the worker.
 *
 * This header does not include the GDK or Windows headers; HRESULTs are
 * carried as int32_t. In a build without REXGLUE_USE_GDK every attempt
 * reports kUnavailable.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

namespace rex::system {

enum class GamingRuntimeState : uint8_t {
  kNotInitialized,
  kReady,
  // The SDK was built without the GDK.
  kUnavailable,
  // xgameruntime.dll (Gaming Services) is not installed or is incomplete.
  kMissing,
  // The installed runtime does not support the GDK edition the title uses.
  kVersionMismatch,
  // MicrosoftGame.config is malformed or disagrees with the package or with an
  // earlier initialization in this process.
  kConfigError,
  kTimedOut,
  kFailed,
};

std::string_view GamingRuntimeStateName(GamingRuntimeState state);

struct GamingRuntimeResult {
  GamingRuntimeState state = GamingRuntimeState::kNotInitialized;
  // The initialize HRESULT; 0 when the call did not return (timeout) or was
  // never made (unavailable).
  int32_t hresult = 0;
  // A diagnostic for logs and error dialogs: what failed and what to do.
  std::string message;

  bool ok() const { return state == GamingRuntimeState::kReady; }
};

// Maps an XGameRuntimeInitialize* HRESULT to a state (kReady on success).
GamingRuntimeState ClassifyGamingRuntimeResult(int32_t hresult);

// The diagnostic for a failed (or successful) initialize HRESULT.
std::string DescribeGamingRuntimeResult(int32_t hresult);

// What a title does with the runtime at startup (cvar gaming_runtime).
enum class GamingRuntimePolicy : uint8_t {
  kOff,       // never initialize it
  kAuto,      // initialize it when the SDK has the GDK; launch whatever happens
  kRequired,  // launch only when it is ready
};

std::optional<GamingRuntimePolicy> ParseGamingRuntimePolicy(std::string_view text);

// Whether the title may start after `result` under `policy`.
bool GamingRuntimeAllowsLaunch(GamingRuntimePolicy policy, const GamingRuntimeResult& result);

// The calls GamingRuntime makes. Tests substitute fakes; titles use
// SystemGamingRuntimeHooks().
struct GamingRuntimeHooks {
  // Initializes the runtime. An empty config_path means XGameRuntimeInitialize;
  // otherwise XGameRuntimeInitializeWithOptions with that MicrosoftGame.config.
  std::function<int32_t(const std::string& config_path)> initialize;
  std::function<void()> uninitialize;
};

// The real XGameRuntime calls, or empty hooks in a build without the GDK.
GamingRuntimeHooks SystemGamingRuntimeHooks();

class GamingRuntime {
 public:
  static constexpr std::chrono::milliseconds kDefaultTimeout{10000};

  explicit GamingRuntime(GamingRuntimeHooks hooks = SystemGamingRuntimeHooks());
  ~GamingRuntime();

  GamingRuntime(const GamingRuntime&) = delete;
  GamingRuntime& operator=(const GamingRuntime&) = delete;

  static bool built_with_gdk();

  // Initializes the runtime, waiting at most `timeout`. Returns the current
  // result without calling again when already ready. A new attempt is refused
  // (kTimedOut) while an earlier timed-out call is still inside the runtime.
  GamingRuntimeResult Initialize(std::chrono::milliseconds timeout = kDefaultTimeout,
                                 std::string config_path = {});

  // Balances a successful Initialize; otherwise does nothing. Call it after
  // everything that uses the runtime has shut down.
  void Uninitialize();

  const GamingRuntimeResult& result() const { return result_; }
  GamingRuntimeState state() const { return result_.state; }

 private:
  struct Attempt;

  GamingRuntimeHooks hooks_;
  std::shared_ptr<Attempt> pending_;
  GamingRuntimeResult result_;
};

}  // namespace rex::system
