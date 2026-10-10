/**
 * @file        audio/xaudio2/audio_outputs.cpp
 * @brief       The Windows audio outputs a player can choose to play the game through
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/audio/audio_outputs.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <mmdeviceapi.h>
#include <objbase.h>
#include <propidl.h>

#include <rex/string/utf8.h>

namespace rex::audio {
namespace {

constexpr PROPERTYKEY kDeviceFriendlyName = {
    {0xa45c254e, 0xdf1c, 0x4efd, {0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0}}, 14};

std::string Utf8(const wchar_t* text) {
  return text ? string::to_utf8(reinterpret_cast<const char16_t*>(text)) : std::string();
}

std::string EndpointId(IMMDevice* device) {
  LPWSTR id = nullptr;
  if (!device || FAILED(device->GetId(&id))) {
    return {};
  }
  std::string utf8 = Utf8(id);
  CoTaskMemFree(id);
  return utf8;
}

std::string FriendlyName(IMMDevice* device) {
  IPropertyStore* properties = nullptr;
  if (FAILED(device->OpenPropertyStore(STGM_READ, &properties))) {
    return {};
  }
  PROPVARIANT value;
  PropVariantInit(&value);
  std::string name;
  if (SUCCEEDED(properties->GetValue(kDeviceFriendlyName, &value)) && value.vt == VT_LPWSTR) {
    name = Utf8(value.pwszVal);
  }
  PropVariantClear(&value);
  properties->Release();
  return name;
}

}  // namespace

std::vector<AudioOutput> ListAudioOutputs() {
  const HRESULT com = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
  std::vector<AudioOutput> outputs;
  IMMDeviceEnumerator* enumerator = nullptr;
  if (SUCCEEDED(CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL,
                                 IID_PPV_ARGS(&enumerator)))) {
    IMMDevice* default_device = nullptr;
    enumerator->GetDefaultAudioEndpoint(eRender, eConsole, &default_device);
    const std::string default_id = EndpointId(default_device);
    if (default_device) {
      default_device->Release();
    }
    IMMDeviceCollection* devices = nullptr;
    UINT count = 0;
    if (SUCCEEDED(enumerator->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, &devices)) &&
        SUCCEEDED(devices->GetCount(&count))) {
      for (UINT i = 0; i < count; ++i) {
        IMMDevice* device = nullptr;
        if (FAILED(devices->Item(i, &device))) {
          continue;
        }
        AudioOutput output;
        output.id = EndpointId(device);
        output.name = FriendlyName(device);
        output.is_default = !output.id.empty() && output.id == default_id;
        device->Release();
        if (!output.id.empty()) {
          outputs.push_back(std::move(output));
        }
      }
    }
    if (devices) {
      devices->Release();
    }
    enumerator->Release();
  }
  if (SUCCEEDED(com)) {
    CoUninitialize();
  }
  return outputs;
}

}  // namespace rex::audio
