/**
 * @file        result.h
 * @brief       Error handling using std::expected
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <expected>
#include <string>
#include <utility>

namespace rex {

enum class ErrorCategory {
  NoError,
  IO,
  Memory,
  Format,
  Crypto,
  Compression,
  Runtime,
  Platform,
  Config,
  Validation,
  NotFound,
  NotImplemented,
  UserAbort,
};

struct Error {
  ErrorCategory category = ErrorCategory::NoError;
  std::string message;
  int code = 0;

  Error() = default;

  Error(ErrorCategory cat, std::string msg, int err_code = 0)
      : category(cat), message(std::move(msg)), code(err_code) {}

  static Error from_errno(ErrorCategory cat, std::string msg, int errno_value) {
    return Error(cat, std::move(msg), errno_value);
  }

  [[nodiscard]] bool is_success() const noexcept { return category == ErrorCategory::NoError; }

  [[nodiscard]] std::string what() const {
    if (is_success()) {
      return "Success";
    }
    std::string result = message;
    if (code != 0) {
      result += " (code: " + std::to_string(code) + ")";
    }
    return result;
  }
};

template <typename T>
using Result = std::expected<T, Error>;

using VoidResult = std::expected<void, Error>;

template <typename T>
inline Result<T> Ok(T&& value) {
  return Result<T>(std::forward<T>(value));
}

inline VoidResult Ok() {
  return VoidResult();
}

template <typename T = void>
inline auto Err(Error error) {
  if constexpr (std::is_void_v<T>) {
    return VoidResult(std::unexpected(std::move(error)));
  } else {
    return Result<T>(std::unexpected(std::move(error)));
  }
}

template <typename T = void>
inline auto Err(ErrorCategory category, std::string message, int code = 0) {
  return Err<T>(Error(category, std::move(message), code));
}

}

#define REX_TRY_CONCAT_IMPL(x, y) x##y
#define REX_TRY_CONCAT(x, y) REX_TRY_CONCAT_IMPL(x, y)

#define TRY(expr)                                                                 \
  ({                                                                              \
    auto REX_TRY_CONCAT(_rex_try_result_, __LINE__) = (expr);                     \
    if (!REX_TRY_CONCAT(_rex_try_result_, __LINE__)) {                            \
      return std::unexpected(REX_TRY_CONCAT(_rex_try_result_, __LINE__).error()); \
    }                                                                             \
    std::move(REX_TRY_CONCAT(_rex_try_result_, __LINE__)).value();                \
  })
