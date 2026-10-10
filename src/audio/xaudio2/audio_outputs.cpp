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
#include <audioclient.h>
#include <mmdeviceapi.h>
#include <mmreg.h>
#include <objbase.h>
#include <propidl.h>
#include <spatialaudioclient.h>

#include <rex/string/utf8.h>

namespace rex::audio {
namespace {

constexpr PROPERTYKEY kDeviceFriendlyName = {
    {0xa45c254e, 0xdf1c, 0x4efd, {0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0}}, 14};
constexpr PROPERTYKEY kAudioEngineDeviceFormat = {
    {0xf19f064d, 0x082c, 0x4e27, {0xbc, 0x73, 0x68, 0x82, 0xa1, 0xbb, 0x8e, 0x4c}}, 0};

constexpr GUID kIec61937DolbyDigital = {
    0x00000092, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}};
constexpr GUID kIec61937Dts = {
    0x00000008, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}};
constexpr GUID kIec61937DolbyDigitalPlus = {
    0x0000000a, 0x0cea, 0x0010, {0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}};
constexpr GUID kIec61937DolbyMlp = {
    0x0000000c, 0x0cea, 0x0010, {0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}};
constexpr GUID kIec61937DtsHd = {
    0x0000000b, 0x0cea, 0x0010, {0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}};

constexpr DWORD kMaskStereo = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT;
constexpr DWORD kMask71 = kMaskStereo | SPEAKER_FRONT_CENTER | SPEAKER_LOW_FREQUENCY |
                          SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT | SPEAKER_SIDE_LEFT |
                          SPEAKER_SIDE_RIGHT;

Support Iec61937Support(IAudioClient* client, const GUID& subformat, WORD channels,
                        DWORD sample_rate, DWORD encoded_rate, DWORD encoded_channels) {
  WAVEFORMATEXTENSIBLE_IEC61937 format = {};
  WAVEFORMATEXTENSIBLE& ext = format.FormatExt;
  ext.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
  ext.Format.nChannels = channels;
  ext.Format.nSamplesPerSec = sample_rate;
  ext.Format.wBitsPerSample = 16;
  ext.Format.nBlockAlign = WORD(channels * 2);
  ext.Format.nAvgBytesPerSec = sample_rate * ext.Format.nBlockAlign;
  ext.Format.cbSize = sizeof(format) - sizeof(WAVEFORMATEX);
  ext.Samples.wValidBitsPerSample = 16;
  ext.dwChannelMask = channels == 2 ? kMaskStereo : kMask71;
  ext.SubFormat = subformat;
  format.dwEncodedSamplesPerSec = encoded_rate;
  format.dwEncodedChannelCount = encoded_channels;
  format.dwAverageBytesPerSec = 0;
  const HRESULT hr = client->IsFormatSupported(AUDCLNT_SHAREMODE_EXCLUSIVE, &ext.Format, nullptr);
  if (hr == S_OK) {
    return Support::kYes;
  }
  return hr == AUDCLNT_E_UNSUPPORTED_FORMAT ? Support::kNo : Support::kUnknown;
}

void ReadDeviceFormat(const WAVEFORMATEX& format, AudioOutput& output) {
  output.channels = format.nChannels;
  output.sample_rate = format.nSamplesPerSec;
  output.bits_per_sample = format.wBitsPerSample;
  if (format.wFormatTag == WAVE_FORMAT_EXTENSIBLE && format.cbSize >= 22) {
    const auto& ext = reinterpret_cast<const WAVEFORMATEXTENSIBLE&>(format);
    output.channel_mask = ext.dwChannelMask;
    if (ext.Samples.wValidBitsPerSample) {
      output.bits_per_sample = ext.Samples.wValidBitsPerSample;
    }
  }
}

bool ReadEngineFormat(IMMDevice* device, AudioOutput& output) {
  IPropertyStore* properties = nullptr;
  if (FAILED(device->OpenPropertyStore(STGM_READ, &properties))) {
    return false;
  }
  PROPVARIANT value;
  PropVariantInit(&value);
  bool read = false;
  if (SUCCEEDED(properties->GetValue(kAudioEngineDeviceFormat, &value)) && value.vt == VT_BLOB &&
      value.blob.cbSize >= sizeof(WAVEFORMATEX)) {
    ReadDeviceFormat(*reinterpret_cast<const WAVEFORMATEX*>(value.blob.pBlobData), output);
    read = true;
  }
  PropVariantClear(&value);
  properties->Release();
  return read;
}

void ReadCapabilities(IMMDevice* device, AudioOutput& output) {
  IAudioClient* client = nullptr;
  if (SUCCEEDED(device->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr,
                                 reinterpret_cast<void**>(&client)))) {
    if (!ReadEngineFormat(device, output)) {
      WAVEFORMATEX* mix = nullptr;
      if (SUCCEEDED(client->GetMixFormat(&mix)) && mix) {
        ReadDeviceFormat(*mix, output);
        CoTaskMemFree(mix);
      }
    }
    output.formats.dolby_digital =
        Iec61937Support(client, kIec61937DolbyDigital, 2, 48000, 48000, 6);
    output.formats.dts = Iec61937Support(client, kIec61937Dts, 2, 48000, 48000, 6);
    output.formats.dolby_digital_plus =
        Iec61937Support(client, kIec61937DolbyDigitalPlus, 2, 192000, 48000, 6);
    output.formats.dolby_truehd = Iec61937Support(client, kIec61937DolbyMlp, 8, 192000, 48000, 8);
    output.formats.dts_hd = Iec61937Support(client, kIec61937DtsHd, 8, 192000, 48000, 8);
    client->Release();
  }
  ISpatialAudioClient* spatial = nullptr;
  if (SUCCEEDED(device->Activate(__uuidof(ISpatialAudioClient), CLSCTX_INPROC_SERVER, nullptr,
                                 reinterpret_cast<void**>(&spatial)))) {
    UINT32 objects = 0;
    output.spatial_sound = SUCCEEDED(spatial->GetMaxDynamicObjectCount(&objects)) && objects > 0;
    spatial->Release();
  }
}

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

}

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
        ReadCapabilities(device, output);
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

std::string SpeakerLayoutName(uint32_t channels, uint32_t channel_mask) {
  constexpr DWORD kQuad = kMaskStereo | SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT;
  constexpr DWORD k51 = kQuad | SPEAKER_FRONT_CENTER | SPEAKER_LOW_FREQUENCY;
  constexpr DWORD k51Side = kMaskStereo | SPEAKER_FRONT_CENTER | SPEAKER_LOW_FREQUENCY |
                            SPEAKER_SIDE_LEFT | SPEAKER_SIDE_RIGHT;
  switch (channel_mask) {
    case SPEAKER_FRONT_CENTER:
      return "Mono";
    case kMaskStereo:
      return "Stereo";
    case kQuad:
      return "Quadraphonic";
    case k51:
    case k51Side:
      return "5.1 surround";
    case kMask71:
      return "7.1 surround";
    default:
      break;
  }
  switch (channels) {
    case 0:
      return {};
    case 1:
      return "Mono";
    case 2:
      return "Stereo";
    case 6:
      return "5.1 surround";
    case 8:
      return "7.1 surround";
    default:
      return std::to_string(channels) + " channels";
  }
}

}
