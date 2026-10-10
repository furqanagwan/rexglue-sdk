/**
 * @file        rexglue/commands/http_client.cpp
 * @brief       HTTP GET for the build-time catalogue and update commands (RG-GDK-050)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include "http_client.h"

#include <fmt/format.h>

#include <rex/string/utf8.h>

// clang-format off
#include <windows.h>
#include <winhttp.h>
// clang-format on

namespace rexglue::cli {
namespace {

struct Handle {
  HINTERNET h = nullptr;
  ~Handle() {
    if (h) {
      WinHttpCloseHandle(h);
    }
  }
};

}

std::optional<std::vector<uint8_t>> HttpGet(const std::string& url, std::string* error,
                                            int timeout_ms) {
  auto fail = [&](std::string why) -> std::optional<std::vector<uint8_t>> {
    if (error) {
      *error = fmt::format("{}: {}", url, why);
    }
    return std::nullopt;
  };
  const std::u16string utf16 = rex::string::to_utf16(url);
  const std::wstring wide(utf16.begin(), utf16.end());
  URL_COMPONENTS parts = {sizeof(parts)};
  wchar_t host[256] = {};
  wchar_t path[2048] = {};
  parts.lpszHostName = host;
  parts.dwHostNameLength = DWORD(std::size(host));
  parts.lpszUrlPath = path;
  parts.dwUrlPathLength = DWORD(std::size(path));
  wchar_t extra[2048] = {};
  parts.lpszExtraInfo = extra;
  parts.dwExtraInfoLength = DWORD(std::size(extra));
  if (!WinHttpCrackUrl(wide.c_str(), 0, 0, &parts)) {
    return fail(fmt::format("not a URL (error {})", GetLastError()));
  }
  Handle session{WinHttpOpen(L"rexglue", WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY, WINHTTP_NO_PROXY_NAME,
                             WINHTTP_NO_PROXY_BYPASS, 0)};
  if (!session.h) {
    return fail(fmt::format("WinHttpOpen failed (error {})", GetLastError()));
  }
  WinHttpSetTimeouts(session.h, timeout_ms, timeout_ms, timeout_ms, timeout_ms);
  Handle connection{WinHttpConnect(session.h, host, parts.nPort, 0)};
  if (!connection.h) {
    return fail(fmt::format("could not connect (error {})", GetLastError()));
  }
  const std::wstring object = std::wstring(path) + extra;
  Handle request{
      WinHttpOpenRequest(connection.h, L"GET", object.c_str(), nullptr, WINHTTP_NO_REFERER,
                         WINHTTP_DEFAULT_ACCEPT_TYPES,
                         parts.nScheme == INTERNET_SCHEME_HTTPS ? WINHTTP_FLAG_SECURE : 0)};
  if (!request.h ||
      !WinHttpSendRequest(request.h, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0,
                          0, 0) ||
      !WinHttpReceiveResponse(request.h, nullptr)) {
    return fail(fmt::format("request failed (error {})", GetLastError()));
  }
  DWORD status = 0;
  DWORD size = sizeof(status);
  WinHttpQueryHeaders(request.h, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
                      WINHTTP_HEADER_NAME_BY_INDEX, &status, &size, WINHTTP_NO_HEADER_INDEX);
  if (status != 200) {
    return fail(fmt::format("HTTP {}", status));
  }
  std::vector<uint8_t> body;
  for (;;) {
    DWORD available = 0;
    if (!WinHttpQueryDataAvailable(request.h, &available)) {
      return fail(fmt::format("read failed (error {})", GetLastError()));
    }
    if (!available) {
      break;
    }
    const size_t at = body.size();
    body.resize(at + available);
    DWORD read = 0;
    if (!WinHttpReadData(request.h, body.data() + at, available, &read)) {
      return fail(fmt::format("read failed (error {})", GetLastError()));
    }
    body.resize(at + read);
  }
  return body;
}

}
