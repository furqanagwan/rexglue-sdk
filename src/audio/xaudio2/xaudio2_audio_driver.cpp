/**
 * @file        audio/xaudio2/xaudio2_audio_driver.cpp
 * @brief       XAudio2 output driver for Universal Windows Platform builds
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include <rex/audio/xaudio2/xaudio2_audio_driver.h>

#include <cstring>

#include <windows.h>
#include <mmreg.h>
#include <xaudio2.h>

#include <rex/assert.h>
#include <rex/audio/conversion.h>
#include <rex/audio/downmix.h>
#include <rex/audio/flags.h>
#include <rex/logging.h>

namespace rex::audio::xaudio2 {

namespace {

constexpr DWORD kStereoChannelMask = 0x3;
constexpr DWORD kSurround51ChannelMask = 0x3F;

}  // namespace

class XAudio2AudioDriver::VoiceCallback final : public IXAudio2VoiceCallback {
 public:
  explicit VoiceCallback(XAudio2AudioDriver& driver) : driver_(driver) {}

  void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32) override {}
  void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() override {}
  void STDMETHODCALLTYPE OnStreamEnd() override {}
  void STDMETHODCALLTYPE OnBufferStart(void*) override {}
  void STDMETHODCALLTYPE OnBufferEnd(void* context) override {
    driver_.OnBufferPlayed(static_cast<float*>(context));
  }
  void STDMETHODCALLTYPE OnLoopEnd(void*) override {}
  void STDMETHODCALLTYPE OnVoiceError(void*, HRESULT error) override {
    REXAPU_ERROR("XAudio2 voice error 0x{:08X}", static_cast<uint32_t>(error));
  }

 private:
  XAudio2AudioDriver& driver_;
};

XAudio2AudioDriver::XAudio2AudioDriver(memory::Memory* memory, rex::thread::Semaphore* semaphore)
    : AudioDriver(memory), semaphore_(semaphore) {}

XAudio2AudioDriver::~XAudio2AudioDriver() {
  assert_true(unused_buffers_.empty());
}

bool XAudio2AudioDriver::Initialize() {
  HRESULT result = XAudio2Create(&xaudio2_, 0, XAUDIO2_DEFAULT_PROCESSOR);
  if (FAILED(result)) {
    REXAPU_ERROR("XAudio2Create failed: 0x{:08X}", static_cast<uint32_t>(result));
    return false;
  }

  result = xaudio2_->CreateMasteringVoice(&mastering_voice_);
  if (FAILED(result)) {
    REXAPU_ERROR("CreateMasteringVoice failed: 0x{:08X}", static_cast<uint32_t>(result));
    return false;
  }

  XAUDIO2_VOICE_DETAILS mastering_details = {};
  mastering_voice_->GetVoiceDetails(&mastering_details);
  output_channels_ = mastering_details.InputChannels >= kGuestChannels ? kGuestChannels : 2;

  WAVEFORMATEXTENSIBLE format = {};
  format.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
  format.Format.nChannels = static_cast<WORD>(output_channels_);
  format.Format.nSamplesPerSec = kFrameFrequency;
  format.Format.wBitsPerSample = 32;
  format.Format.nBlockAlign = static_cast<WORD>(output_channels_ * sizeof(float));
  format.Format.nAvgBytesPerSec = kFrameFrequency * format.Format.nBlockAlign;
  format.Format.cbSize = sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX);
  format.Samples.wValidBitsPerSample = 32;
  format.dwChannelMask =
      output_channels_ == kGuestChannels ? kSurround51ChannelMask : kStereoChannelMask;
  format.SubFormat = KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;

  voice_callback_ = std::make_unique<VoiceCallback>(*this);
  result = xaudio2_->CreateSourceVoice(&source_voice_, &format.Format, 0,
                                       XAUDIO2_DEFAULT_FREQ_RATIO, voice_callback_.get());
  if (FAILED(result)) {
    REXAPU_ERROR("CreateSourceVoice failed: 0x{:08X}", static_cast<uint32_t>(result));
    return false;
  }

  result = source_voice_->Start();
  if (FAILED(result)) {
    REXAPU_ERROR("Starting the XAudio2 source voice failed: 0x{:08X}",
                 static_cast<uint32_t>(result));
    return false;
  }

  REXAPU_INFO("XAudio2 endpoint: {} ch, {} Hz; submitting {} ch", mastering_details.InputChannels,
              mastering_details.InputSampleRate, output_channels_);
  return true;
}

float* XAudio2AudioDriver::AcquireBuffer() {
  std::lock_guard<std::mutex> lock(buffers_mutex_);
  if (unused_buffers_.empty()) {
    return new float[kChannelSamples * kGuestChannels];
  }
  float* buffer = unused_buffers_.back();
  unused_buffers_.pop_back();
  return buffer;
}

void XAudio2AudioDriver::ReleaseBuffer(float* buffer) {
  std::lock_guard<std::mutex> lock(buffers_mutex_);
  unused_buffers_.push_back(buffer);
}

void XAudio2AudioDriver::SubmitFrame(uint32_t frame_ptr) {
  if (!source_voice_) {
    return;
  }
  const auto input_frame = memory_->TranslateVirtual<float*>(frame_ptr);
  float* output_frame = AcquireBuffer();

  if (REXCVAR_GET(audio_mute)) {
    std::memset(output_frame, 0, sizeof(float) * kChannelSamples * output_channels_);
  } else if (output_channels_ == kGuestChannels) {
    conversion::sequential_6_BE_to_interleaved_6_LE(output_frame, input_frame, kChannelSamples,
                                                    GetSurroundMix(), GetOutputGain());
  } else {
    conversion::sequential_6_BE_to_interleaved_2_LE(output_frame, input_frame, kChannelSamples,
                                                    GetStereoFold(), GetOutputGain());
  }

  XAUDIO2_BUFFER buffer = {};
  buffer.AudioBytes = sizeof(float) * kChannelSamples * output_channels_;
  buffer.pAudioData = reinterpret_cast<const BYTE*>(output_frame);
  buffer.pContext = output_frame;
  HRESULT result = source_voice_->SubmitSourceBuffer(&buffer);
  if (FAILED(result)) {
    REXAPU_ERROR("SubmitSourceBuffer failed: 0x{:08X}", static_cast<uint32_t>(result));
    ReleaseBuffer(output_frame);
    semaphore_->Release(1, nullptr);
  }
}

void XAudio2AudioDriver::OnBufferPlayed(float* buffer) {
  ReleaseBuffer(buffer);
  semaphore_->Release(1, nullptr);
}

void XAudio2AudioDriver::Shutdown() {
  if (source_voice_) {
    source_voice_->Stop();
    source_voice_->FlushSourceBuffers();
    source_voice_->DestroyVoice();
    source_voice_ = nullptr;
  }
  if (mastering_voice_) {
    mastering_voice_->DestroyVoice();
    mastering_voice_ = nullptr;
  }
  if (xaudio2_) {
    xaudio2_->StopEngine();
    xaudio2_->Release();
    xaudio2_ = nullptr;
  }
  voice_callback_.reset();
  std::lock_guard<std::mutex> lock(buffers_mutex_);
  for (float* buffer : unused_buffers_) {
    delete[] buffer;
  }
  unused_buffers_.clear();
}

}  // namespace rex::audio::xaudio2
