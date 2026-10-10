/**
 * @file        system/gaming_runtime.cpp
 * @brief       Application-owned Microsoft Gaming Runtime lifecycle (RG-GDK-022)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/system/gaming_runtime.h>

#include <condition_variable>
#include <mutex>
#include <thread>
#include <utility>

#include <fmt/format.h>

#if defined(REXGLUE_GDK_EDITION)
#include <windows.h>

#include <XGameRuntimeInit.h>
#endif

namespace rex::system {

namespace {

constexpr uint32_t kDllNotFound = 0x89240101;
constexpr uint32_t kVersionMismatch = 0x89240102;
constexpr uint32_t kMissingDependency = 0x89240107;
constexpr uint32_t kOptionsMismatch = 0x89240109;
constexpr uint32_t kOptionsNotSupported = 0x8924010A;
constexpr uint32_t kGameConfigBadFormat = 0x8924010B;
constexpr uint32_t kServiceNotAvailable = 0x8924010D;

constexpr uint32_t kPackageConfigFirst = 0x89245209;
constexpr uint32_t kPackageConfigLast = 0x89245212;
constexpr uint32_t kModNotFound = 0x8007007E;
constexpr uint32_t kFileNotFound = 0x80070002;
constexpr uint32_t kPathNotFound = 0x80070003;

#if defined(REXGLUE_GDK_EDITION)
constexpr int kEdition = REXGLUE_GDK_EDITION;
#else
constexpr int kEdition = 0;
#endif

}

struct GamingRuntime::Attempt {
  std::mutex mutex;
  std::condition_variable done_cv;
  bool done = false;
  bool abandoned = false;
  int32_t hresult = 0;
};

std::string_view GamingRuntimeStateName(GamingRuntimeState state) {
  switch (state) {
    case GamingRuntimeState::kNotInitialized:
      return "not initialized";
    case GamingRuntimeState::kReady:
      return "ready";
    case GamingRuntimeState::kUnavailable:
      return "unavailable";
    case GamingRuntimeState::kMissing:
      return "missing";
    case GamingRuntimeState::kVersionMismatch:
      return "version mismatch";
    case GamingRuntimeState::kConfigError:
      return "config error";
    case GamingRuntimeState::kTimedOut:
      return "timed out";
    case GamingRuntimeState::kFailed:
      return "failed";
  }
  return "unknown";
}

GamingRuntimeState ClassifyGamingRuntimeResult(int32_t hresult) {
  if (hresult >= 0) {
    return GamingRuntimeState::kReady;
  }
  const uint32_t code = uint32_t(hresult);
  switch (code) {
    case kDllNotFound:
    case kMissingDependency:
    case kModNotFound:
      return GamingRuntimeState::kMissing;
    case kVersionMismatch:
      return GamingRuntimeState::kVersionMismatch;
    case kOptionsMismatch:
    case kOptionsNotSupported:
    case kGameConfigBadFormat:
      return GamingRuntimeState::kConfigError;
    default:
      break;
  }
  if (code >= kPackageConfigFirst && code <= kPackageConfigLast) {
    return GamingRuntimeState::kConfigError;
  }
  return GamingRuntimeState::kFailed;
}

std::string DescribeGamingRuntimeResult(int32_t hresult) {
  const uint32_t code = uint32_t(hresult);
  switch (ClassifyGamingRuntimeResult(hresult)) {
    case GamingRuntimeState::kReady:
      return "The Microsoft Gaming Runtime is ready.";
    case GamingRuntimeState::kMissing:
      return fmt::format(
          "The Microsoft Gaming Runtime (Gaming Services) is not installed or is incomplete "
          "(0x{:08X}). Install or update Gaming Services from the Microsoft Store, then start "
          "the game again.",
          code);
    case GamingRuntimeState::kVersionMismatch:
      return fmt::format(
          "The installed Gaming Services does not support GDK {} that this game was built with "
          "(0x{:08X}). Update Gaming Services from the Microsoft Store.",
          kEdition, code);
    case GamingRuntimeState::kConfigError:
      if (code == kOptionsMismatch) {
        return fmt::format(
            "The Gaming Runtime was already initialized in this process with a different "
            "MicrosoftGame.config (0x{:08X}).",
            code);
      }
      if (code == kOptionsNotSupported) {
        return fmt::format(
            "A packaged game cannot override its MicrosoftGame.config at initialization "
            "(0x{:08X}).",
            code);
      }
      return fmt::format(
          "MicrosoftGame.config is invalid or does not match this game (0x{:08X}). Regenerate it "
          "with `rexglue init gameconfig` and check the identity against the installed package.",
          code);
    default:
      if (code == kServiceNotAvailable) {
        return fmt::format("The Gaming Runtime service is not available (0x{:08X}).", code);
      }
      return fmt::format("XGameRuntimeInitialize failed (0x{:08X}).", code);
  }
}

std::optional<GamingRuntimePolicy> ParseGamingRuntimePolicy(std::string_view text) {
  if (text == "off") {
    return GamingRuntimePolicy::kOff;
  }
  if (text == "auto") {
    return GamingRuntimePolicy::kAuto;
  }
  if (text == "required") {
    return GamingRuntimePolicy::kRequired;
  }
  return std::nullopt;
}

bool GamingRuntimeAllowsLaunch(GamingRuntimePolicy policy, const GamingRuntimeResult& result) {
  return policy != GamingRuntimePolicy::kRequired || result.ok();
}

GamingRuntimeHooks SystemGamingRuntimeHooks() {
#if defined(REXGLUE_GDK_EDITION)
  return {
      [](const std::string& config_path) -> int32_t {
        if (config_path.empty()) {
          return XGameRuntimeInitialize();
        }
        XGameRuntimeOptions options = {};
        options.gameConfigSource = XGameRuntimeGameConfigSource::File;
        options.gameConfig = config_path.c_str();
        return XGameRuntimeInitializeWithOptions(&options);
      },
      [] { XGameRuntimeUninitialize(); },
  };
#else
  return {};
#endif
}

GamingRuntime::GamingRuntime(GamingRuntimeHooks hooks) : hooks_(std::move(hooks)) {}

GamingRuntime::~GamingRuntime() {
  Uninitialize();
}

bool GamingRuntime::built_with_gdk() {
#if defined(REXGLUE_GDK_EDITION)
  return true;
#else
  return false;
#endif
}

GamingRuntimeResult GamingRuntime::Initialize(std::chrono::milliseconds timeout,
                                              std::string config_path) {
  if (result_.state == GamingRuntimeState::kReady) {
    return result_;
  }
  if (!hooks_.initialize) {
    result_ = {GamingRuntimeState::kUnavailable, 0,
               "This SDK build has no Gaming Runtime (it was built without REXGLUE_USE_GDK)."};
    return result_;
  }
  if (pending_) {
    std::lock_guard lock(pending_->mutex);
    if (!pending_->done) {
      result_ = {GamingRuntimeState::kTimedOut, 0,
                 "An earlier Gaming Runtime initialization has not returned yet."};
      return result_;
    }
  }
  pending_.reset();

  auto attempt = std::make_shared<Attempt>();
  std::thread([attempt, initialize = hooks_.initialize, uninitialize = hooks_.uninitialize,
               config_path] {
    const int32_t hresult = initialize(config_path);
    bool balance = false;
    {
      std::lock_guard lock(attempt->mutex);
      attempt->hresult = hresult;
      attempt->done = true;

      balance = attempt->abandoned && hresult >= 0;
    }
    attempt->done_cv.notify_all();
    if (balance && uninitialize) {
      uninitialize();
    }
  }).detach();

  std::unique_lock lock(attempt->mutex);
  if (!attempt->done_cv.wait_for(lock, timeout, [&] { return attempt->done; })) {
    attempt->abandoned = true;
    pending_ = attempt;
    result_ = {GamingRuntimeState::kTimedOut, 0,
               fmt::format("The Microsoft Gaming Runtime did not respond within {} ms. Gaming "
                           "Services may still be starting or may be stuck; restarting the "
                           "Gaming Services service or the PC usually clears it.",
                           timeout.count())};
    return result_;
  }

  const int32_t hresult = attempt->hresult;
  GamingRuntimeState state = ClassifyGamingRuntimeResult(hresult);
  std::string message = DescribeGamingRuntimeResult(hresult);

  if (!config_path.empty() &&
      (uint32_t(hresult) == kFileNotFound || uint32_t(hresult) == kPathNotFound)) {
    state = GamingRuntimeState::kConfigError;
    message = fmt::format("MicrosoftGame.config was not found at {} (0x{:08X}).", config_path,
                          uint32_t(hresult));
  }
  result_ = {state, hresult, std::move(message)};
  return result_;
}

void GamingRuntime::Uninitialize() {
  if (result_.state != GamingRuntimeState::kReady) {
    return;
  }
  if (hooks_.uninitialize) {
    hooks_.uninitialize();
  }
  result_ = {};
}

}
