/**
 * @file        audio/xaudio2/xaudio2_audio_driver.cpp
 * @brief       XAudio2 2.9 output for one guest audio client (RG-GDK-019)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/audio/xaudio2/xaudio2_audio_driver.h>

#include <algorithm>
#include <cstring>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <mmreg.h>
#include <objbase.h>
#include <xaudio2.h>

#include <rex/audio/conversion.h>
#include <rex/audio/downmix.h>
#include <rex/audio/flags.h>
#include <rex/cvar.h>
#include <rex/logging.h>

namespace rex::audio::xaudio2 {

namespace {

// KSDATAFORMAT_SUBTYPE_IEEE_FLOAT, spelled out so no GUID library is needed.
constexpr GUID kSubtypeIeeeFloat = {
    0x00000003, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}};

// Guest channel order fl fr fc lf bl br is the 5.1 speaker mask's bit order.
constexpr DWORD kMask51 = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT | SPEAKER_FRONT_CENTER |
                          SPEAKER_LOW_FREQUENCY | SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT;
constexpr DWORD kMaskStereo = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT;

void* EncodeContext(uint32_t slot, uint32_t generation) {
  return reinterpret_cast<void*>((uintptr_t(generation) << 8) | slot);
}

}  // namespace

class XAudio2AudioDriver::EngineCallback final : public IXAudio2EngineCallback {
 public:
  explicit EngineCallback(XAudio2AudioDriver* driver) : driver_(driver) {}
  void STDMETHODCALLTYPE OnProcessingPassStart() noexcept override {}
  void STDMETHODCALLTYPE OnProcessingPassEnd() noexcept override {}
  void STDMETHODCALLTYPE OnCriticalError(HRESULT error) noexcept override {
    driver_->OnCriticalError(error);
  }

 private:
  XAudio2AudioDriver* driver_;
};

class XAudio2AudioDriver::VoiceCallback final : public IXAudio2VoiceCallback {
 public:
  explicit VoiceCallback(XAudio2AudioDriver* driver) : driver_(driver) {}
  void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32) noexcept override {}
  void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() noexcept override {}
  void STDMETHODCALLTYPE OnStreamEnd() noexcept override {}
  void STDMETHODCALLTYPE OnBufferStart(void*) noexcept override {}
  void STDMETHODCALLTYPE OnBufferEnd(void* context) noexcept override {
    const auto value = reinterpret_cast<uintptr_t>(context);
    driver_->OnBufferEnd(uint32_t(value & 0xFF), uint32_t(value >> 8));
  }
  void STDMETHODCALLTYPE OnLoopEnd(void*) noexcept override {}
  void STDMETHODCALLTYPE OnVoiceError(void*, HRESULT error) noexcept override {
    REXAPU_WARN("XAudio2 voice error 0x{:08X}", static_cast<uint32_t>(error));
  }

 private:
  XAudio2AudioDriver* driver_;
};

XAudio2AudioDriver::XAudio2AudioDriver(memory::Memory* memory, rex::thread::Semaphore* semaphore)
    : XAudio2AudioDriver(memory, semaphore, Options{}) {}

XAudio2AudioDriver::XAudio2AudioDriver(memory::Memory* memory, rex::thread::Semaphore* semaphore,
                                       Options options)
    : AudioDriver(memory),
      semaphore_(semaphore),
      options_(options),
      simulate_no_device_(options.simulate_no_device) {
  free_slots_.reserve(kFrameSlots);
  for (uint32_t i = kFrameSlots; i-- > 0;) {
    free_slots_.push_back(i);
  }
}

XAudio2AudioDriver::~XAudio2AudioDriver() {
  Shutdown();
}

bool XAudio2AudioDriver::Initialize() {
  engine_callback_ = new EngineCallback(this);
  voice_callback_ = new VoiceCallback(this);

  // XAudio2 needs COM in the MTA. The service thread holds an MTA scope for
  // the driver's lifetime, which also makes guest threads that submit frames
  // implicitly MTA (https://devblogs.microsoft.com/oldnewthing/?p=4613).
  service_thread_ = std::thread(&XAudio2AudioDriver::ServiceThread, this);
  std::unique_lock<std::mutex> lock(mutex_);
  wake_.wait(lock, [this] { return service_started_; });
  if (!service_ok_) {
    lock.unlock();
    service_thread_.join();
    return false;
  }
  return true;
}

void XAudio2AudioDriver::Shutdown() {
  if (service_thread_.joinable()) {
    {
      std::lock_guard<std::mutex> lock(mutex_);
      shutdown_requested_ = true;
    }
    wake_.notify_all();
    service_thread_.join();
  }
  delete voice_callback_;
  voice_callback_ = nullptr;
  delete engine_callback_;
  engine_callback_ = nullptr;
}

void XAudio2AudioDriver::SubmitFrame(uint32_t frame_ptr) {
  SubmitGuestFrame(memory_->TranslateVirtual<const float*>(frame_ptr));
}

void XAudio2AudioDriver::SubmitGuestFrame(const float* frame) {
  uint32_t slot;
  uint32_t generation;
  uint32_t channels;
  {
    std::lock_guard<std::mutex> lock(mutex_);
    if (free_slots_.empty()) {
      // More frames in flight than AudioSystem ever queues. Keep the one
      // release per frame so the client cannot stall.
      REXAPU_WARN("XAudio2: no free frame slot, frame dropped");
      ++frames_released_;
      semaphore_->Release(1, nullptr);
      return;
    }
    slot = free_slots_.back();
    free_slots_.pop_back();
    slots_[slot].state = SlotState::kFilling;
    generation = generation_;
    channels = output_channels_;
  }

  // Same conversion and mix controls as the SDL output, applied per frame.
  float* out = slots_[slot].samples.data();
  if (REXCVAR_GET(audio_mute)) {
    std::memset(out, 0, sizeof(float) * channels * kChannelSamples);
  } else if (channels == 2) {
    conversion::sequential_6_BE_to_interleaved_2_LE(out, frame, kChannelSamples, GetStereoFold(),
                                                    GetOutputGain());
  } else {
    conversion::sequential_6_BE_to_interleaved_6_LE(out, frame, kChannelSamples, GetSurroundMix(),
                                                    GetOutputGain());
  }

  std::lock_guard<std::mutex> lock(mutex_);
  const Clock::time_point now = Clock::now();
  slots_[slot].generation = generation;
  // The device may have changed while this frame was converted; a frame mixed
  // for another channel count is paced instead of played.
  if (engine_live_ && generation == generation_) {
    XAUDIO2_BUFFER buffer = {};
    buffer.AudioBytes = uint32_t(sizeof(float) * channels * kChannelSamples);
    buffer.pAudioData = reinterpret_cast<const BYTE*>(out);
    buffer.pContext = EncodeContext(slot, generation);
    const HRESULT hr = source_voice_->SubmitSourceBuffer(&buffer);
    if (SUCCEEDED(hr)) {
      slots_[slot].state = SlotState::kEngine;
      if (engine_frames_++ == 0) {
        // Start the stall watchdog's clock.
        engine_progress_ = now;
        wake_.notify_all();
      }
      return;
    }
    REXAPU_WARN("XAudio2 SubmitSourceBuffer failed with 0x{:08X}", static_cast<uint32_t>(hr));
    MarkEngineLostLocked("SubmitSourceBuffer failed");
  }
  PaceLocked(slot, now);
  wake_.notify_all();
}

bool XAudio2AudioDriver::has_device() const {
  std::lock_guard<std::mutex> lock(mutex_);
  return engine_live_;
}

uint32_t XAudio2AudioDriver::output_channels() const {
  std::lock_guard<std::mutex> lock(mutex_);
  return output_channels_;
}

void XAudio2AudioDriver::SimulateDeviceLoss() {
  {
    std::lock_guard<std::mutex> lock(mutex_);
    MarkEngineLostLocked("simulated device loss");
  }
  wake_.notify_all();
}

void XAudio2AudioDriver::SimulateStall() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (engine_live_) {
    source_voice_->Stop();
  }
}

void XAudio2AudioDriver::SetSimulateNoDevice(bool no_device) {
  std::lock_guard<std::mutex> lock(mutex_);
  simulate_no_device_ = no_device;
}

void XAudio2AudioDriver::OnBufferEnd(uint32_t slot, uint32_t generation) {
  std::lock_guard<std::mutex> lock(mutex_);
  // Buffers of a torn-down engine were already moved to the paced queue.
  if (!engine_live_ || generation != generation_ || slot >= kFrameSlots ||
      slots_[slot].state != SlotState::kEngine) {
    return;
  }
  --engine_frames_;
  engine_progress_ = Clock::now();
  ReleaseSlotLocked(slot);
}

void XAudio2AudioDriver::OnCriticalError(long hr) {
  REXAPU_WARN("XAudio2 critical error 0x{:08X}", static_cast<uint32_t>(hr));
  {
    std::lock_guard<std::mutex> lock(mutex_);
    MarkEngineLostLocked("critical error");
  }
  wake_.notify_all();
}

void XAudio2AudioDriver::PaceLocked(uint32_t slot, Clock::time_point now) {
  slots_[slot].state = SlotState::kPaced;
  const Clock::time_point deadline = std::max(now, last_paced_deadline_) +
                                     std::chrono::duration_cast<Clock::duration>(kFramePeriod);
  last_paced_deadline_ = deadline;
  paced_.emplace_back(slot, deadline);
}

void XAudio2AudioDriver::ReleaseSlotLocked(uint32_t slot) {
  slots_[slot].state = SlotState::kFree;
  free_slots_.push_back(slot);
  ++frames_released_;
  if (!semaphore_->Release(1, nullptr)) {
    REXAPU_WARN("XAudio2: client semaphore already at its maximum");
  }
}

void XAudio2AudioDriver::MarkEngineLostLocked(const char* reason) {
  if (!engine_live_) {
    return;
  }
  REXAPU_WARN("XAudio2 output lost ({}); pacing frames until a device returns", reason);
  engine_live_ = false;
  engine_lost_ = true;
  ++generation_;
  ++device_losses_;
  // A dead voice never ends its buffers; release them on the clock instead.
  const Clock::time_point now = Clock::now();
  for (uint32_t i = 0; i < kFrameSlots; ++i) {
    if (slots_[i].state == SlotState::kEngine) {
      PaceLocked(i, now);
    }
  }
  engine_frames_ = 0;
}

bool XAudio2AudioDriver::CreateEngine() {
  {
    std::lock_guard<std::mutex> lock(mutex_);
    if (simulate_no_device_) {
      if (!create_failure_logged_) {
        REXAPU_WARN("XAudio2: no audio device (simulated); pacing frames");
        create_failure_logged_ = true;
      }
      return false;
    }
  }

  IXAudio2* xaudio2 = nullptr;
  IXAudio2MasteringVoice* mastering = nullptr;
  IXAudio2SourceVoice* source = nullptr;
  auto fail = [&](const char* what, HRESULT hr) {
    if (!create_failure_logged_) {
      REXAPU_WARN("XAudio2: {} failed with 0x{:08X}; pacing frames until a device appears", what,
                  static_cast<uint32_t>(hr));
      create_failure_logged_ = true;
    }
    if (source) {
      source->DestroyVoice();
    }
    if (mastering) {
      mastering->DestroyVoice();
    }
    if (xaudio2) {
      xaudio2->UnregisterForCallbacks(engine_callback_);
      xaudio2->Release();
    }
    return false;
  };

  HRESULT hr = XAudio2Create(&xaudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
  if (FAILED(hr)) {
    xaudio2 = nullptr;
    return fail("XAudio2Create", hr);
  }
  hr = xaudio2->RegisterForCallbacks(engine_callback_);
  if (FAILED(hr)) {
    return fail("RegisterForCallbacks", hr);
  }
  // Default device, channels and rate: the default device ID selects the
  // virtual audio client, which follows default-device changes itself, and
  // not forcing a rate lets it switch to a 44.1 kHz endpoint.
  hr = xaudio2->CreateMasteringVoice(&mastering);
  if (FAILED(hr)) {
    mastering = nullptr;
    return fail("CreateMasteringVoice", hr);
  }
  XAUDIO2_VOICE_DETAILS details = {};
  mastering->GetVoiceDetails(&details);
  DWORD device_mask = 0;
  mastering->GetChannelMask(&device_mask);
  // A mono or stereo endpoint gets the stereo fold, as with SDL; anything
  // wider gets 5.1 and XAudio2 maps it onto the endpoint's layout.
  const uint32_t channels = details.InputChannels > 2 ? 6 : 2;

  WAVEFORMATEXTENSIBLE format = {};
  format.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
  format.Format.nChannels = WORD(channels);
  format.Format.nSamplesPerSec = kFrameFrequency;
  format.Format.wBitsPerSample = 32;
  format.Format.nBlockAlign = WORD(channels * sizeof(float));
  format.Format.nAvgBytesPerSec = kFrameFrequency * format.Format.nBlockAlign;
  format.Format.cbSize = sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX);
  format.Samples.wValidBitsPerSample = 32;
  format.dwChannelMask = channels == 6 ? kMask51 : kMaskStereo;
  format.SubFormat = kSubtypeIeeeFloat;
  hr = xaudio2->CreateSourceVoice(&source, &format.Format, 0, XAUDIO2_DEFAULT_FREQ_RATIO,
                                  voice_callback_);
  if (FAILED(hr)) {
    source = nullptr;
    return fail("CreateSourceVoice", hr);
  }
  hr = source->Start();
  if (FAILED(hr)) {
    return fail("IXAudio2SourceVoice::Start", hr);
  }

  REXAPU_INFO("XAudio2 output: device {} ch (mask 0x{:X}), {} Hz; submitting {} ch",
              details.InputChannels, static_cast<uint32_t>(device_mask), details.InputSampleRate,
              channels);
  std::lock_guard<std::mutex> lock(mutex_);
  xaudio2_ = xaudio2;
  mastering_voice_ = mastering;
  source_voice_ = source;
  output_channels_ = channels;
  ++generation_;
  engine_live_ = true;
  engine_lost_ = false;
  engine_frames_ = 0;
  create_failure_logged_ = false;
  return true;
}

void XAudio2AudioDriver::DestroyEngine() {
  IXAudio2* xaudio2;
  IXAudio2MasteringVoice* mastering;
  IXAudio2SourceVoice* source;
  {
    std::lock_guard<std::mutex> lock(mutex_);
    if (engine_live_) {
      // An orderly teardown, not a loss: same bookkeeping without counting it.
      MarkEngineLostLocked("engine shut down");
      --device_losses_;
    }
    engine_lost_ = false;
    xaudio2 = xaudio2_;
    mastering = mastering_voice_;
    source = source_voice_;
    xaudio2_ = nullptr;
    mastering_voice_ = nullptr;
    source_voice_ = nullptr;
  }
  // Callbacks may still be running; they take mutex_, so none of this may
  // happen under it. Stopping the engine first ends in-flight callbacks before
  // the voices go (xenia-edge 9371e73d9).
  if (xaudio2) {
    xaudio2->StopEngine();
  }
  if (source) {
    source->DestroyVoice();
  }
  if (mastering) {
    mastering->DestroyVoice();
  }
  if (xaudio2) {
    xaudio2->UnregisterForCallbacks(engine_callback_);
    xaudio2->Release();
  }
}

void XAudio2AudioDriver::ServiceThread() {
  rex::thread::set_current_thread_name("XAudio2 Service");
  const HRESULT com_hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
  const bool com_ok = SUCCEEDED(com_hr);
  if (!com_ok) {
    REXAPU_ERROR("XAudio2: CoInitializeEx failed with 0x{:08X}", static_cast<uint32_t>(com_hr));
  }
  if (com_ok) {
    // Initialize() reports once the first device attempt is done, so a caller
    // sees has_device() settled.
    CreateEngine();
  }
  {
    std::lock_guard<std::mutex> lock(mutex_);
    service_ok_ = com_ok;
    service_started_ = true;
  }
  wake_.notify_all();
  if (!com_ok) {
    return;
  }

  Clock::time_point retry_at = Clock::now() + options_.retry_interval;

  std::unique_lock<std::mutex> lock(mutex_);
  while (!shutdown_requested_) {
    const Clock::time_point now = Clock::now();
    while (!paced_.empty() && paced_.front().second <= now) {
      ReleaseSlotLocked(paced_.front().first);
      paced_.pop_front();
    }
    if (engine_live_ && engine_frames_ > 0 && now - engine_progress_ > options_.stall_timeout) {
      MarkEngineLostLocked("no buffer finished within the stall timeout");
    }
    if (engine_lost_) {
      // Recreate straight away: the loss is often a device switch the virtual
      // client could not follow, and the new default is already there.
      lock.unlock();
      DestroyEngine();
      CreateEngine();
      lock.lock();
      retry_at = Clock::now() + options_.retry_interval;
      continue;
    }
    if (!engine_live_ && now >= retry_at) {
      lock.unlock();
      CreateEngine();
      lock.lock();
      retry_at = Clock::now() + options_.retry_interval;
      continue;
    }

    Clock::time_point wake_at = now + std::chrono::milliseconds(250);
    if (!paced_.empty()) {
      wake_at = std::min(wake_at, paced_.front().second);
    }
    if (!engine_live_) {
      wake_at = std::min(wake_at, retry_at);
    } else if (engine_frames_ > 0) {
      wake_at = std::min(wake_at,
                         engine_progress_ + options_.stall_timeout + std::chrono::milliseconds(1));
    }
    // Never spin: a deadline already past still yields the lock for a moment.
    wake_.wait_until(lock, std::max(wake_at, now + std::chrono::milliseconds(1)));
  }
  lock.unlock();

  DestroyEngine();
  CoUninitialize();
}

}  // namespace rex::audio::xaudio2
