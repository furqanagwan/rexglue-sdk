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

#include <rex/cvar.h>
#include <rex/kernel/xboxkrnl/private.h>
#include <rex/kernel/xboxkrnl/xconfig.h>
#include <rex/logging.h>
#include <rex/hook.h>
#include <rex/types.h>
#include <rex/system/flags.h>
#include <rex/system/kernel_state.h>
#include <rex/system/user_module.h>
#include <rex/system/user_language.h>
#include <rex/system/xtypes.h>

namespace rex::kernel::xboxkrnl {

X_STATUS xeExGetXConfigSetting(uint16_t category, uint16_t setting, void* buffer,
                               uint16_t buffer_size, uint16_t* required_size) {
  uint16_t setting_size = 0;
  alignas(uint32_t) uint8_t value[4];

  switch (category) {
    case 0x0002:

      switch (setting) {
        case 0x0002:
          setting_size = 4;
          memory::store_and_swap<uint32_t>(value, 0x00001000);
          break;
        default:
          REXKRNL_WARN("Unimplemented XConfig SECURED setting 0x{:04X}", setting);
          return X_STATUS_INVALID_PARAMETER_2;
      }
      break;
    case 0x0003:

      switch (setting) {
        case 0x0001:
        case 0x0002:
        case 0x0003:
        case 0x0004:
        case 0x0005:
        case 0x0006:
        case 0x0007:
          setting_size = 4;

          memory::store_and_swap<uint32_t>(value, 0);
          break;
        case 0x0009:
          setting_size = 4;
          memory::store_and_swap<uint32_t>(value, uint32_t(system::GetUserLanguage()));
          break;
        case 0x000A:
          setting_size = 4;
          memory::store_and_swap<uint32_t>(value, kXConfigUserVideoFlags);
          break;
        case 0x000B:
          setting_size = 4;
          memory::store_and_swap<uint32_t>(value, kXConfigUserAudioFlags);
          break;
        case 0x000C:
          setting_size = 4;
          memory::store_and_swap<uint32_t>(value, 0x40);
          break;
        case 0x000E:
          setting_size = 1;
          value[0] = static_cast<uint8_t>(REXCVAR_GET(user_country));
          break;
        case 0x0019:
          setting_size = 1;

          value[0] = 0x03;
          break;
        default:
          REXKRNL_WARN("Unimplemented XConfig USER setting 0x{:04X}", setting);
          return X_STATUS_INVALID_PARAMETER_2;
      }
      break;
    default:
      REXKRNL_WARN("Unimplemented XConfig category 0x{:04X}", category);
      return X_STATUS_INVALID_PARAMETER_1;
  }

  if (buffer) {
    if (buffer_size < setting_size) {
      return X_STATUS_BUFFER_TOO_SMALL;
    }
    std::memcpy(buffer, value, setting_size);
  } else {
    if (buffer_size) {
      return X_STATUS_INVALID_PARAMETER_3;
    }
  }

  if (required_size) {
    *required_size = setting_size;
  }

  return X_STATUS_SUCCESS;
}

u32 ExGetXConfigSetting_entry(u16 category, u16 setting, mapped_void buffer_ptr, u16 buffer_size,
                              mapped_u16 required_size_ptr) {
  uint16_t required_size = 0;
  X_STATUS result =
      xeExGetXConfigSetting(category, setting, buffer_ptr, buffer_size, &required_size);

  if (required_size_ptr) {
    *required_size_ptr = required_size;
  }

  return result;
}

}

REX_EXPORT(__imp__ExGetXConfigSetting, rex::kernel::xboxkrnl::ExGetXConfigSetting_entry)
REX_EXPORT_STUB(__imp__ExSetXConfigSetting);
