/**
 * @file        audio/nop/ui_sound_player_nop.cpp
 * @brief       Interface sounds where the platform has no host audio output
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include <rex/audio/ui_sound.h>

namespace rex::audio {

struct UiSoundPlayer::Impl {};

UiSoundPlayer::UiSoundPlayer() : impl_(std::make_unique<Impl>()) {}

UiSoundPlayer::~UiSoundPlayer() = default;

void UiSoundPlayer::Play(const PcmSound&, float) {}

}  // namespace rex::audio
