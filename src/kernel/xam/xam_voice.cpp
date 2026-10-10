/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2022 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <rex/kernel/xam/private.h>
#include <rex/logging.h>
#include <rex/hook.h>
#include <rex/types.h>
#include <rex/system/kernel_state.h>
#include <rex/system/xtypes.h>

namespace rex {
namespace kernel {
namespace xam {

u32 XamVoiceIsActiveProcess_entry() {
  return 0;
}

u32 XamVoiceCreate_entry(u32 user_index, u32 max_attached_packets, mapped_u32 out_voice_ptr) {
  out_voice_ptr.Zero();
  return X_ERROR_ACCESS_DENIED;
}

u32 XamVoiceClose_entry(mapped_void voice_ptr) {
  return 0;
}

u32 XamVoiceHeadsetPresent_entry(mapped_void voice_ptr) {
  return 0;
}

}
}
}

REX_EXPORT(__imp__XamVoiceIsActiveProcess, rex::kernel::xam::XamVoiceIsActiveProcess_entry)
REX_EXPORT(__imp__XamVoiceCreate, rex::kernel::xam::XamVoiceCreate_entry)
REX_EXPORT(__imp__XamVoiceClose, rex::kernel::xam::XamVoiceClose_entry)
REX_EXPORT(__imp__XamVoiceHeadsetPresent, rex::kernel::xam::XamVoiceHeadsetPresent_entry)

REX_EXPORT_STUB(__imp__XamMuteSound);
REX_EXPORT_STUB(__imp__XamVoiceDisableMicArray);
REX_EXPORT_STUB(__imp__XamVoiceGetBatteryStatus);
REX_EXPORT_STUB(__imp__XamVoiceGetDirectionalData);
REX_EXPORT_STUB(__imp__XamVoiceGetMicArrayAudio);
REX_EXPORT_STUB(__imp__XamVoiceGetMicArrayAudioEx);
REX_EXPORT_STUB(__imp__XamVoiceGetMicArrayFilenameDesc);
REX_EXPORT_STUB(__imp__XamVoiceGetMicArrayStatus);
REX_EXPORT_STUB(__imp__XamVoiceGetMicArrayUnderrunStatus);
REX_EXPORT_STUB(__imp__XamVoiceMuteMicArray);
REX_EXPORT_STUB(__imp__XamVoiceRecordUserPrivileges);
REX_EXPORT_STUB(__imp__XamVoiceSetAudioCaptureRoutine);
REX_EXPORT_STUB(__imp__XamVoiceSetMicArrayBeamAngle);
REX_EXPORT_STUB(__imp__XamVoiceSetMicArrayIdleUsers);
REX_EXPORT_STUB(__imp__XamVoiceSubmitPacket);
