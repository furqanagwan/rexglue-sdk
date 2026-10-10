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

  kUnavailable,

  kMissing,

  kVersionMismatch,

  kConfigError,
  kTimedOut,
  kFailed,
};

std::string_view GamingRuntimeStateName(GamingRuntimeState state);

struct GamingRuntimeResult {
  GamingRuntimeState state = GamingRuntimeState::kNotInitialized;

  int32_t hresult = 0;

  std::string message;

  bool ok() const { return state == GamingRuntimeState::kReady; }
};

GamingRuntimeState ClassifyGamingRuntimeResult(int32_t hresult);

std::string DescribeGamingRuntimeResult(int32_t hresult);

enum class GamingRuntimePolicy : uint8_t {
  kOff,
  kAuto,
  kRequired,
};

std::optional<GamingRuntimePolicy> ParseGamingRuntimePolicy(std::string_view text);

bool GamingRuntimeAllowsLaunch(GamingRuntimePolicy policy, const GamingRuntimeResult& result);

struct GamingRuntimeHooks {
  std::function<int32_t(const std::string& config_path)> initialize;
  std::function<void()> uninitialize;
};

GamingRuntimeHooks SystemGamingRuntimeHooks();

class GamingRuntime {
 public:
  static constexpr std::chrono::milliseconds kDefaultTimeout{10000};

  explicit GamingRuntime(GamingRuntimeHooks hooks = SystemGamingRuntimeHooks());
  ~GamingRuntime();

  GamingRuntime(const GamingRuntime&) = delete;
  GamingRuntime& operator=(const GamingRuntime&) = delete;

  static bool built_with_gdk();

  GamingRuntimeResult Initialize(std::chrono::milliseconds timeout = kDefaultTimeout,
                                 std::string config_path = {});

  void Uninitialize();

  const GamingRuntimeResult& result() const { return result_; }
  GamingRuntimeState state() const { return result_.state; }

 private:
  struct Attempt;

  GamingRuntimeHooks hooks_;
  std::shared_ptr<Attempt> pending_;
  GamingRuntimeResult result_;
};

}
