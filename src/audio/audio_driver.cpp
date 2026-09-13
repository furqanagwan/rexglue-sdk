/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include <rex/audio/audio_driver.h>
#include <rex/audio/flags.h>
#include <rex/cvar.h>

REXCVAR_DEFINE_BOOL(audio_mute, false, "Audio", "Mute audio output");

namespace rex::audio {

AudioDriver::AudioDriver(memory::Memory* memory) : memory_(memory) {}

AudioDriver::~AudioDriver() = default;

}  // namespace rex::audio
