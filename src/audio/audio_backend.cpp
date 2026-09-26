/**
 * @file        audio/audio_backend.cpp
 * @brief       Audio output backend chosen by the audio_backend cvar
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/audio/audio_backend.h>

#include <rex/audio/nop/nop_audio_system.h>
#include <rex/audio/sdl/sdl_audio_system.h>
#include <rex/cvar.h>
#include <rex/logging.h>
#include <rex/platform.h>

#if REX_PLATFORM_WIN32
#include <rex/audio/xaudio2/xaudio2_audio_system.h>
#endif

REXCVAR_DEFINE_STRING(audio_backend, "sdl", "Audio",
                      "Audio output: sdl, xaudio2 (Windows; falls back to sdl) or nop")
    .allowed({"sdl", "xaudio2", "nop"})
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);

namespace rex::audio {

std::unique_ptr<AudioSystem> CreateDefaultAudioSystem(
    runtime::FunctionDispatcher* function_dispatcher) {
  const auto& backend = REXCVAR_GET(audio_backend);
  if (backend == "nop") {
    return nop::NopAudioSystem::Create(function_dispatcher);
  }
  if (backend == "xaudio2") {
#if REX_PLATFORM_WIN32
    return xaudio2::XAudio2AudioSystem::Create(function_dispatcher);
#else
    REXAPU_WARN("audio_backend=xaudio2 is Windows only; using SDL");
#endif
  }
  return sdl::SDLAudioSystem::Create(function_dispatcher);
}

}  // namespace rex::audio
