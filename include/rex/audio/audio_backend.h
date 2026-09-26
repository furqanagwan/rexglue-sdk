/**
 * @file        audio/audio_backend.h
 * @brief       Audio output backend chosen by the audio_backend cvar
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <memory>

#include <rex/audio/audio_system.h>

namespace rex::audio {

/// The audio system for the audio_backend cvar: "sdl" (default), "xaudio2"
/// (Windows) or "nop". An unavailable choice falls back to SDL with a warning.
std::unique_ptr<AudioSystem> CreateDefaultAudioSystem(
    runtime::FunctionDispatcher* function_dispatcher);

}  // namespace rex::audio
