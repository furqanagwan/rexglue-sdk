/**
 * @file        ui/display_info_win.cpp
 * @brief       The displays a player can choose to play on, and what each supports
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/ui/display_info.h>

#include <algorithm>
#include <map>
#include <utility>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <dxgi1_6.h>

#include <fmt/format.h>

#include <rex/string/utf8.h>

namespace rex::ui {
namespace {

constexpr size_t kMaxResolutions = 4;

constexpr DisplayResolution kStandardResolutions[] = {
    {3840, 2160, 0}, {2560, 1440, 0}, {1920, 1080, 0}, {1280, 720, 0}};

struct TargetFacts {
  std::string name;
  uint32_t native_width = 0;
  uint32_t native_height = 0;
  bool hdr_supported = false;
  bool hdr_on = false;
  uint32_t bits_per_color = 0;
};

struct OutputFacts {
  float peak_nits = 0.0f;
  uint32_t bits_per_color = 0;
};

std::string Utf8(const wchar_t* text) {
  std::string utf8 = string::to_utf8(reinterpret_cast<const char16_t*>(text));
  utf8.erase(utf8.find_last_not_of(' ') + 1);
  return utf8;
}

std::map<std::wstring, TargetFacts> QueryTargets() {
  std::map<std::wstring, TargetFacts> targets;
  UINT32 path_count = 0;
  UINT32 mode_count = 0;
  if (GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &path_count, &mode_count) !=
      ERROR_SUCCESS) {
    return targets;
  }
  std::vector<DISPLAYCONFIG_PATH_INFO> paths(path_count);
  std::vector<DISPLAYCONFIG_MODE_INFO> modes(mode_count);
  if (QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &path_count, paths.data(), &mode_count,
                         modes.data(), nullptr) != ERROR_SUCCESS) {
    return targets;
  }
  paths.resize(path_count);
  for (const DISPLAYCONFIG_PATH_INFO& path : paths) {
    DISPLAYCONFIG_SOURCE_DEVICE_NAME source = {};
    source.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
    source.header.size = sizeof(source);
    source.header.adapterId = path.sourceInfo.adapterId;
    source.header.id = path.sourceInfo.id;
    if (DisplayConfigGetDeviceInfo(&source.header) != ERROR_SUCCESS) {
      continue;
    }
    TargetFacts facts;
    DISPLAYCONFIG_TARGET_DEVICE_NAME target = {};
    target.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
    target.header.size = sizeof(target);
    target.header.adapterId = path.targetInfo.adapterId;
    target.header.id = path.targetInfo.id;
    if (DisplayConfigGetDeviceInfo(&target.header) == ERROR_SUCCESS) {
      facts.name = Utf8(target.monitorFriendlyDeviceName);
    }
    DISPLAYCONFIG_TARGET_PREFERRED_MODE preferred = {};
    preferred.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_PREFERRED_MODE;
    preferred.header.size = sizeof(preferred);
    preferred.header.adapterId = path.targetInfo.adapterId;
    preferred.header.id = path.targetInfo.id;
    if (DisplayConfigGetDeviceInfo(&preferred.header) == ERROR_SUCCESS) {
      facts.native_width = preferred.width;
      facts.native_height = preferred.height;
    }
    DISPLAYCONFIG_GET_ADVANCED_COLOR_INFO color = {};
    color.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_ADVANCED_COLOR_INFO;
    color.header.size = sizeof(color);
    color.header.adapterId = path.targetInfo.adapterId;
    color.header.id = path.targetInfo.id;
    if (DisplayConfigGetDeviceInfo(&color.header) == ERROR_SUCCESS) {
      facts.hdr_supported = color.advancedColorSupported;
      facts.hdr_on = color.advancedColorEnabled;
      facts.bits_per_color = color.bitsPerColorChannel;
    }
    targets[source.viewGdiDeviceName] = std::move(facts);
  }
  return targets;
}

std::map<std::wstring, OutputFacts> QueryOutputs() {
  std::map<std::wstring, OutputFacts> outputs;
  IDXGIFactory1* factory = nullptr;
  if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory)))) {
    return outputs;
  }
  IDXGIAdapter1* adapter = nullptr;
  for (UINT a = 0; factory->EnumAdapters1(a, &adapter) != DXGI_ERROR_NOT_FOUND; ++a) {
    IDXGIOutput* output = nullptr;
    for (UINT o = 0; adapter->EnumOutputs(o, &output) != DXGI_ERROR_NOT_FOUND; ++o) {
      IDXGIOutput6* output6 = nullptr;
      DXGI_OUTPUT_DESC1 desc = {};
      if (SUCCEEDED(output->QueryInterface(IID_PPV_ARGS(&output6))) &&
          SUCCEEDED(output6->GetDesc1(&desc))) {
        outputs[desc.DeviceName] = {desc.MaxLuminance, desc.BitsPerColor};
      }
      if (output6) {
        output6->Release();
      }
      output->Release();
    }
    adapter->Release();
  }
  factory->Release();
  return outputs;
}

std::vector<HMONITOR> MonitorsInSettingOrder() {
  std::vector<HMONITOR> monitors;
  EnumDisplayMonitors(
      nullptr, nullptr,
      [](HMONITOR monitor, HDC, LPRECT, LPARAM data) -> BOOL {
        reinterpret_cast<std::vector<HMONITOR>*>(data)->push_back(monitor);
        return TRUE;
      },
      reinterpret_cast<LPARAM>(&monitors));
  std::stable_partition(monitors.begin(), monitors.end(), [](HMONITOR monitor) {
    MONITORINFO info = {};
    info.cbSize = sizeof(info);
    return GetMonitorInfoW(monitor, &info) && (info.dwFlags & MONITORINFOF_PRIMARY);
  });
  return monitors;
}

}

std::vector<DisplayResolution> NotableResolutions(const std::vector<DisplayResolution>& modes,
                                                  uint32_t native_width, uint32_t native_height) {
  std::map<std::pair<uint32_t, uint32_t>, uint32_t> fastest;
  for (const DisplayResolution& mode : modes) {
    uint32_t& hz = fastest[{mode.width, mode.height}];
    hz = std::max(hz, mode.max_refresh_hz);
  }
  std::vector<DisplayResolution> notable;
  auto add = [&](uint32_t width, uint32_t height) {
    const auto found = fastest.find({width, height});
    if (found == fastest.end() || notable.size() >= kMaxResolutions ||
        std::find_if(notable.begin(), notable.end(), [&](const DisplayResolution& r) {
          return r.width == width && r.height == height;
        }) != notable.end()) {
      return;
    }
    notable.push_back({width, height, found->second});
  };
  add(native_width, native_height);
  for (const DisplayResolution& standard : kStandardResolutions) {
    add(standard.width, standard.height);
  }
  return notable;
}

std::string ResolutionName(uint32_t width, uint32_t height) {
  if (width == 7680 && height == 4320) {
    return "8K UHD";
  }
  if (width == 3840 && height == 2160) {
    return "4K UHD";
  }
  if (width == 2560 && height == 1440) {
    return "1440p QHD";
  }
  if (width == 3440 && height == 1440) {
    return "Ultrawide QHD";
  }
  if (width == 1920 && height == 1080) {
    return "1080p Full HD";
  }
  if (width == 1280 && height == 720) {
    return "720p HD";
  }
  return {};
}

std::vector<DisplayInfo> ListDisplays(void* game_window) {
  const std::map<std::wstring, TargetFacts> targets = QueryTargets();
  const std::map<std::wstring, OutputFacts> outputs = QueryOutputs();
  const HMONITOR game_monitor =
      game_window ? MonitorFromWindow(static_cast<HWND>(game_window), MONITOR_DEFAULTTONULL)
                  : nullptr;
  std::vector<DisplayInfo> displays;
  const std::vector<HMONITOR> monitors = MonitorsInSettingOrder();
  for (size_t i = 0; i < monitors.size(); ++i) {
    MONITORINFOEXW info = {};
    info.cbSize = sizeof(info);
    if (!GetMonitorInfoW(monitors[i], &info)) {
      continue;
    }
    DisplayInfo display;
    display.monitor_index = int32_t(i + 1);
    display.primary = (info.dwFlags & MONITORINFOF_PRIMARY) != 0;
    display.shows_game = monitors[i] == game_monitor;
    DEVMODEW current = {};
    current.dmSize = sizeof(current);
    if (EnumDisplaySettingsExW(info.szDevice, ENUM_CURRENT_SETTINGS, &current, 0)) {
      display.width = current.dmPelsWidth;
      display.height = current.dmPelsHeight;
      display.refresh_hz = current.dmDisplayFrequency;
    }
    std::vector<DisplayResolution> modes;
    for (DWORD m = 0;; ++m) {
      DEVMODEW mode = {};
      mode.dmSize = sizeof(mode);
      if (!EnumDisplaySettingsExW(info.szDevice, m, &mode, 0)) {
        break;
      }
      modes.push_back({mode.dmPelsWidth, mode.dmPelsHeight, mode.dmDisplayFrequency});
    }
    if (const auto target = targets.find(info.szDevice); target != targets.end()) {
      display.name = target->second.name;
      display.native_width = target->second.native_width;
      display.native_height = target->second.native_height;
      display.hdr_supported = target->second.hdr_supported;
      display.hdr_on = target->second.hdr_on;
      display.bits_per_color = target->second.bits_per_color;
    }
    if (const auto output = outputs.find(info.szDevice); output != outputs.end()) {
      display.peak_nits = output->second.peak_nits;
      if (!display.bits_per_color) {
        display.bits_per_color = output->second.bits_per_color;
      }
    }
    if (display.name.empty()) {
      display.name = fmt::format("Display {}", i + 1);
    }
    if (!display.native_width || !display.native_height) {
      display.native_width = display.width;
      display.native_height = display.height;
    }
    display.resolutions = NotableResolutions(modes, display.native_width, display.native_height);
    displays.push_back(std::move(display));
  }
  return displays;
}

}
