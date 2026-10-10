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

REXCVAR_DEFINE_STRING(audio_backend, "xaudio2", "Audio", "Audio output: xaudio2 (default) or nop")
    .allowed({"xaudio2", "nop", "sdl"})
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);

REXCVAR_DEFINE_BOOL(audio_mute, false, "Audio", "Mute audio output");
REXCVAR_DEFINE_BOOL(audio_mute_minimized, true, "Audio",
                    "Silence the game while its window is minimised");
REXCVAR_DEFINE_INT32(audio_volume, 100, "Audio",
                     "Master volume of the title's audio output, 0-100 (the title's own "
                     "volume settings still apply first)")
    .range(0, 100);
REXCVAR_DEFINE_STRING(audio_output_device, "", "Audio",
                      "Windows audio output the game plays through, by endpoint ID; empty "
                      "follows the Windows default output");

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

}
