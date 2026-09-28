/**
 * @file        audio/audio_backend.cpp
 * @brief       Audio output backend chosen by the audio_backend cvar
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/audio/audio_backend.h>

#include <rex/audio/nop/nop_audio_system.h>
#include <rex/audio/xaudio2/xaudio2_audio_system.h>
#include <rex/cvar.h>
#include <rex/logging.h>

// "sdl" is still accepted so an old config starts: SDL was removed
// (RG-GDK-033), and it now means XAudio2, with a warning.
REXCVAR_DEFINE_STRING(audio_backend, "xaudio2", "Audio", "Audio output: xaudio2 (default) or nop")
    .allowed({"xaudio2", "nop", "sdl"})
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);

// Applied by every output driver; defined here since the SDL driver that
// held it was removed.
REXCVAR_DEFINE_BOOL(audio_mute, false, "Audio", "Mute audio output");

namespace rex::audio {

std::unique_ptr<AudioSystem> CreateDefaultAudioSystem(
    runtime::FunctionDispatcher* function_dispatcher) {
  const auto& backend = REXCVAR_GET(audio_backend);
  if (backend == "nop") {
    return nop::NopAudioSystem::Create(function_dispatcher);
  }
  if (backend == "sdl") {
    REXAPU_WARN("audio_backend=sdl: SDL was removed; using XAudio2");
  }
  return xaudio2::XAudio2AudioSystem::Create(function_dispatcher);
}

}  // namespace rex::audio
