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

#include <algorithm>
#include <atomic>
#include <string>

#include <rex/cvar.h>
#include <rex/graphics/pipeline/texture/info.h>
#include <rex/graphics/register_file.h>
#include <rex/graphics/video_mode_util.h>
#include <rex/graphics/xenos.h>
#include <rex/kernel/xboxkrnl/private.h>
#include <rex/kernel/xboxkrnl/rtl.h>
#include <rex/kernel/xboxkrnl/video.h>
#include <rex/logging.h>
#include <rex/hook.h>
#include <rex/types.h>
#include <rex/runtime.h>
#include <rex/system/export_resolver.h>
#include <rex/system/kernel_state.h>
#include <rex/system/xtypes.h>
#include <rex/ui/flags.h>

namespace {

constexpr uint32_t kDisplayGammaType = 2;

constexpr double kDisplayGammaPower = 2.22222233;

void ConfiguredVideoMode(uint32_t& width, uint32_t& height) {
  int32_t configured_width = REXCVAR_GET(video_mode_width);
  int32_t configured_height = REXCVAR_GET(video_mode_height);
  if (!rex::cvar::HasNonDefaultValue("video_mode_width") &&
      !rex::cvar::HasNonDefaultValue("video_mode_height")) {
    rex::graphics::video_mode_util::ResolveConfiguredSize(configured_width, configured_height);
  }
  width = uint32_t(std::clamp(configured_width, 640, 0x0FFF));
  height = uint32_t(std::clamp(configured_height, 480, 0x0FFF));
}

float GetConfiguredVideoModeRefreshRate() {
  double refresh_rate_hz = std::clamp(REXCVAR_GET(video_mode_refresh_rate), 24.0, 240.0);
  return float(refresh_rate_hz);
}

void WarnNoGpuEmulation(const char* export_name, std::atomic<bool>& warned) {
  if (!warned.exchange(true)) {
    REXKRNL_WARN("{}: no GPU emulation loaded (gpu_plugin not set); call ignored", export_name);
  }
}
}

namespace rex::kernel::xboxkrnl {
using namespace rex::system;

REX_EXPORT_STUB(__imp__VdBlockUntilGUIIdle);
REX_EXPORT_STUB(__imp__VdDisplayFatalError);
REX_EXPORT_STUB(__imp__VdEnableClosedCaption);
REX_EXPORT_STUB(__imp__VdEnableDisablePowerSavingMode);
REX_EXPORT_STUB(__imp__VdGenerateGPUCSCCoefficients);
REX_EXPORT_STUB(__imp__VdGetClosedCaptionReadyStatus);
REX_EXPORT_STUB(__imp__VdGetDisplayModeOverride);
REX_EXPORT_STUB(__imp__VdInitializeScaler);
REX_EXPORT_STUB(__imp__VdQuerySystemCommandBuffer);
REX_EXPORT_STUB(__imp__VdReadDVERegisterUlong);
REX_EXPORT_STUB(__imp__VdReadWriteHSIOCalibrationFlag);
REX_EXPORT_STUB(__imp__VdRegisterGraphicsNotification);
REX_EXPORT_STUB(__imp__VdRegisterXamGraphicsNotification);
REX_EXPORT_STUB(__imp__VdSendClosedCaptionData);
REX_EXPORT_STUB(__imp__VdSetCGMSOption);
REX_EXPORT_STUB(__imp__VdSetColorProfileAdjustment);
REX_EXPORT_STUB(__imp__VdSetCscMatricesOverride);
REX_EXPORT_STUB(__imp__VdSetHDCPOption);
REX_EXPORT_STUB(__imp__VdSetMacrovisionOption);
REX_EXPORT_STUB(__imp__VdSetSystemCommandBuffer);
REX_EXPORT_STUB(__imp__VdSetWSSData);
REX_EXPORT_STUB(__imp__VdSetWSSOption);
REX_EXPORT_STUB(__imp__VdTurnDisplayOff);
REX_EXPORT_STUB(__imp__VdTurnDisplayOn);
REX_EXPORT_STUB(__imp__VdWriteDVERegisterUlong);
REX_EXPORT_STUB(__imp__VdInitializeEDRAM);
REX_EXPORT_STUB(__imp__VdReadEEDIDBlock);
REX_EXPORT_STUB(__imp__VdEnumerateVideoModes);
REX_EXPORT_STUB(__imp__VdEnableHDCP);
REX_EXPORT_STUB(__imp__VdRegisterHDCPNotification);
REX_EXPORT_STUB(__imp__VdGetDisplayDiscoveryData);
REX_EXPORT_STUB(__imp__VdStartDisplayDiscovery);
REX_EXPORT_STUB(__imp__VdSetHDCPRevocationList);
REX_EXPORT_STUB(__imp__VdEnableWMAProOverHDMI);
REX_EXPORT_STUB(__imp__VdQueryRealVideoMode);
REX_EXPORT_STUB(__imp__VdSetCGMSState);
REX_EXPORT_STUB(__imp__VdSetSCMSState);
REX_EXPORT_STUB(__imp__VdGetOption);
REX_EXPORT_STUB(__imp__VdSetOption);
REX_EXPORT_STUB(__imp__VdQueryVideoCapabilities);
REX_EXPORT_STUB(__imp__VdGet3dVideoFormat);
REX_EXPORT_STUB(__imp__VdGetWSS2Data);
REX_EXPORT_STUB(__imp__VdSet3dVideoFormat);
REX_EXPORT_STUB(__imp__VdSetWSS2Data);
REX_EXPORT_STUB(__imp__VdSetStudioRGBMode);

void VdGetCurrentDisplayGamma_entry(mapped_u32 type_ptr, mapped_f32 power_ptr) {
  *type_ptr = kDisplayGammaType;
  *power_ptr = float(kDisplayGammaPower);
}

struct X_D3DPRIVATE_RECT {
  rex::be<uint32_t> x1;
  rex::be<uint32_t> y1;
  rex::be<uint32_t> x2;
  rex::be<uint32_t> y2;
};
static_assert_size(X_D3DPRIVATE_RECT, 0x10);

struct X_D3DFILTER_PARAMETERS {
  rex::be<float> nyquist;
  rex::be<float> flicker_filter;
  rex::be<float> beta;
};
static_assert_size(X_D3DFILTER_PARAMETERS, 0xC);

struct X_D3DPRIVATE_SCALER_PARAMETERS {
  X_D3DPRIVATE_RECT scaler_source_rect;
  rex::be<uint32_t> scaled_output_width;
  rex::be<uint32_t> scaled_output_height;
  rex::be<uint32_t> vertical_filter_type;
  X_D3DFILTER_PARAMETERS vertical_filter_parameters;
  rex::be<uint32_t> horizontal_filter_type;
  X_D3DFILTER_PARAMETERS horizontal_filter_parameters;
};
static_assert_size(X_D3DPRIVATE_SCALER_PARAMETERS, 0x38);

struct X_DISPLAY_INFO {
  rex::be<uint16_t> front_buffer_width;
  rex::be<uint16_t> front_buffer_height;
  uint8_t front_buffer_color_format;
  uint8_t front_buffer_pixel_format;
  X_D3DPRIVATE_SCALER_PARAMETERS scaler_parameters;
  rex::be<uint16_t> display_window_overscan_left;
  rex::be<uint16_t> display_window_overscan_top;
  rex::be<uint16_t> display_window_overscan_right;
  rex::be<uint16_t> display_window_overscan_bottom;
  rex::be<uint16_t> display_width;
  rex::be<uint16_t> display_height;
  rex::be<float> display_refresh_rate;
  rex::be<uint32_t> display_interlaced;
  uint8_t display_color_format;
  rex::be<uint16_t> actual_display_width;
};
static_assert_size(X_DISPLAY_INFO, 0x58);

void VdGetCurrentDisplayInformation_entry(ppc_ptr_t<X_DISPLAY_INFO> display_info) {
  X_VIDEO_MODE mode;
  VdQueryVideoMode(&mode);
  display_info.Zero();
  display_info->front_buffer_width = (uint16_t)mode.display_width;
  display_info->front_buffer_height = (uint16_t)mode.display_height;

  display_info->scaler_parameters.scaler_source_rect.x2 = mode.display_width;
  display_info->scaler_parameters.scaler_source_rect.y2 = mode.display_height;
  display_info->scaler_parameters.scaled_output_width = mode.display_width;
  display_info->scaler_parameters.scaled_output_height = mode.display_height;
  display_info->scaler_parameters.horizontal_filter_type = 1;
  display_info->scaler_parameters.vertical_filter_type = 1;

  uint16_t overscan_x = uint16_t(uint32_t(mode.display_width) / 4);
  uint16_t overscan_y = uint16_t(uint32_t(mode.display_height) / 4);
  display_info->display_window_overscan_left = overscan_x;
  display_info->display_window_overscan_top = overscan_y;
  display_info->display_window_overscan_right = overscan_x;
  display_info->display_window_overscan_bottom = overscan_y;
  display_info->display_width = (uint16_t)mode.display_width;
  display_info->display_height = (uint16_t)mode.display_height;
  display_info->display_refresh_rate = mode.refresh_rate;
  display_info->actual_display_width = (uint16_t)mode.display_width;
}

void VdQueryVideoMode(X_VIDEO_MODE* video_mode) {
  uint32_t display_width = 0;
  uint32_t display_height = 0;
  ConfiguredVideoMode(display_width, display_height);
  float refresh_rate_hz = GetConfiguredVideoModeRefreshRate();

  std::memset(video_mode, 0, sizeof(X_VIDEO_MODE));
  video_mode->display_width = display_width;
  video_mode->display_height = display_height;
  video_mode->is_interlaced = 0;
  video_mode->is_widescreen = display_width * 3 >= display_height * 4;
  video_mode->is_hi_def = display_width >= 1280 || display_height >= 720;
  video_mode->refresh_rate = refresh_rate_hz;
  video_mode->video_standard = 1;
  video_mode->unknown_0x8a = 0x4A;
  video_mode->unknown_0x01 = 0x01;
}

void VdQueryVideoMode_entry(ppc_ptr_t<X_VIDEO_MODE> video_mode) {
  VdQueryVideoMode(video_mode);
}

u32 VdQueryVideoFlags_entry() {
  X_VIDEO_MODE mode;
  VdQueryVideoMode(&mode);

  uint32_t flags = 0;
  flags |= mode.is_widescreen ? 1 : 0;
  flags |= mode.display_width >= 1024 ? 2 : 0;
  flags |= mode.display_width >= 1920 ? 4 : 0;

  return flags;
}

u32 VdSetDisplayMode_entry(u32 flags) {
  return 0;
}

u32 VdSetDisplayModeOverride_entry(u32 width, u32 height, f64 refresh_rate, u32 unk3, u32 unk4) {
  return 0;
}

u32 VdInitializeEngines_entry(u32 unk0, u32 callback, mapped_void arg, mapped_u32 pfp_ptr,
                              mapped_u32 me_ptr) {
  return 1;
}

void VdShutdownEngines_entry() {}

u32 VdGetGraphicsAsicID_entry() {
  return 0x11;
}

u32 VdEnableDisableClockGating_entry(u32 enabled) {
  return 0;
}

void VdSetGraphicsInterruptCallback_entry(u32 callback, mapped_void user_data) {
  auto* graphics_system = REX_KERNEL_STATE()->emulator()->graphics_system();
  if (!graphics_system) {
    static std::atomic<bool> warned{false};
    WarnNoGpuEmulation("VdSetGraphicsInterruptCallback", warned);
    return;
  }
  graphics_system->SetInterruptCallback(callback, user_data.guest_address());
}

void VdInitializeRingBuffer_entry(mapped_void ptr, i32 size_log2) {
  auto* graphics_system = REX_KERNEL_STATE()->emulator()->graphics_system();
  if (!graphics_system) {
    static std::atomic<bool> warned{false};
    WarnNoGpuEmulation("VdInitializeRingBuffer", warned);
    return;
  }
  graphics_system->InitializeRingBuffer(ptr.guest_address(), size_log2);
}

void VdEnableRingBufferRPtrWriteBack_entry(mapped_void ptr, i32 block_size_log2) {
  auto* graphics_system = REX_KERNEL_STATE()->emulator()->graphics_system();
  if (!graphics_system) {
    static std::atomic<bool> warned{false};
    WarnNoGpuEmulation("VdEnableRingBufferRPtrWriteBack", warned);
    return;
  }
  graphics_system->EnableReadPointerWriteBack(ptr.guest_address(), block_size_log2);
}

void VdGetSystemCommandBuffer_entry(mapped_void p0_ptr, mapped_void p1_ptr) {
  p0_ptr.Zero(0x94);
  memory::store_and_swap<uint32_t>(p0_ptr, 0xBEEF0000);
  memory::store_and_swap<uint32_t>(p1_ptr, 0xBEEF0001);
}

void VdSetSystemCommandBufferGpuIdentifierAddress_entry(mapped_void unk) {}

u32 VdInitializeScalerCommandBuffer_entry(
    u32 scaler_source_xy, u32 scaler_source_wh, u32 scaled_output_xy, u32 scaled_output_wh,
    u32 front_buffer_wh, u32 vertical_filter_type,
    ppc_ptr_t<X_D3DFILTER_PARAMETERS> vertical_filter_params, u32 horizontal_filter_type,
    ppc_ptr_t<X_D3DFILTER_PARAMETERS> horizontal_filter_params, mapped_void unk9,
    mapped_void dest_ptr,

    u32 dest_count) {
  auto dest = dest_ptr.as_array<uint32_t>();
  for (size_t i = 0; i < dest_count; ++i) {
    dest[i] = 0x80000000;
  }
  return (uint32_t)dest_count;
}

struct BufferScaling {
  rex::be<uint16_t> fb_width;
  rex::be<uint16_t> fb_height;
  rex::be<uint16_t> bb_width;
  rex::be<uint16_t> bb_height;
};
void AppendParam(string::StringBuffer* string_buffer, ppc_ptr_t<BufferScaling> param) {
  string_buffer->AppendFormat("{:08X}(scale {}x{} -> {}x{}))", param.guest_address(),
                              uint16_t(param->bb_width), uint16_t(param->bb_height),
                              uint16_t(param->fb_width), uint16_t(param->fb_height));
}

u32 VdCallGraphicsNotificationRoutines_entry(u32 unk0, ppc_ptr_t<BufferScaling> args_ptr) {
  assert_true(unk0 == 1);

  return 0;
}

u32 VdIsHSIOTrainingSucceeded_entry() {
  return 1;
}

u32 VdPersistDisplay_entry(u32 unk0, mapped_u32 unk1_ptr) {
  if (unk1_ptr) {
    auto heap = REX_KERNEL_MEMORY()->LookupHeapByType(true, 16 * 1024);
    uint32_t unk1_value;
    heap->Alloc(64, 32, memory::kMemoryAllocationReserve | memory::kMemoryAllocationCommit,
                memory::kMemoryProtectNoAccess, false, &unk1_value);
    *unk1_ptr = unk1_value;
  }

  return 1;
}

u32 VdRetrainEDRAMWorker_entry(u32 unk0) {
  return 0;
}

u32 VdRetrainEDRAM_entry(u32 unk0, u32 unk1, u32 unk2, u32 unk3, u32 unk4, u32 unk5) {
  return 0;
}

void VdSwap_entry(mapped_void buffer_ptr, mapped_void fetch_ptr, mapped_void unk2, mapped_void unk3,
                  mapped_void unk4, mapped_u32 frontbuffer_ptr, mapped_u32 texture_format_ptr,
                  mapped_u32 color_space_ptr, mapped_u32 width, mapped_u32 height) {
  assert(buffer_ptr);
  assert(fetch_ptr);
  assert(frontbuffer_ptr);
  assert(texture_format_ptr);
  assert(width);
  assert(height);

  namespace xenos = rex::graphics::xenos;

  xenos::xe_gpu_texture_fetch_t gpu_fetch;
  memory::copy_and_swap_32_unaligned(&gpu_fetch,
                                     reinterpret_cast<uint32_t*>(fetch_ptr.host_address()), 6);

  uint32_t frontbuffer_virtual_address = gpu_fetch.base_address << 12;
  assert_true(*frontbuffer_ptr == frontbuffer_virtual_address);
  uint32_t frontbuffer_physical_address =
      REX_KERNEL_MEMORY()->GetPhysicalAddress(frontbuffer_virtual_address);
  assert_true(frontbuffer_physical_address != UINT32_MAX);
  if (frontbuffer_physical_address == UINT32_MAX) {
    REXKRNL_ERROR("VdSwap: Invalid front buffer virtual address 0x{:08X}",
                  frontbuffer_virtual_address);
    return;
  }
  gpu_fetch.base_address = frontbuffer_physical_address >> 12;

  auto texture_format = rex::graphics::xenos::TextureFormat(texture_format_ptr.value());
  auto color_space = *color_space_ptr;
  assert_true(texture_format == rex::graphics::xenos::TextureFormat::k_8_8_8_8 ||
              texture_format == rex::graphics::xenos::TextureFormat::k_2_10_10_10_AS_16_16_16_16);
  assert_true(color_space == 0);
  assert_true(*width == 1 + gpu_fetch.size_2d.width);
  assert_true(*height == 1 + gpu_fetch.size_2d.height);

  buffer_ptr.Zero(64 * 4);

  uint32_t offset = 0;
  auto dwords = buffer_ptr.as_array<uint32_t>();

  dwords[offset++] =
      xenos::MakePacketType0(rex::graphics::XE_GPU_REG_SHADER_CONSTANT_FETCH_00_0, 6);
  dwords[offset++] = gpu_fetch.dword_0;
  dwords[offset++] = gpu_fetch.dword_1;
  dwords[offset++] = gpu_fetch.dword_2;
  dwords[offset++] = gpu_fetch.dword_3;
  dwords[offset++] = gpu_fetch.dword_4;
  dwords[offset++] = gpu_fetch.dword_5;

  dwords[offset++] = xenos::MakePacketType3(xenos::PM4_XE_SWAP, 4);
  dwords[offset++] = rex::graphics::xenos::kSwapSignature;
  dwords[offset++] = frontbuffer_physical_address;

  dwords[offset++] = *width;
  dwords[offset++] = *height;

  for (uint32_t i = offset; i < 64; i++) {
    dwords[i] = xenos::MakePacketType2();
  }
}

void RegisterVideoExports(rex::runtime::ExportResolver* export_resolver,
                          KernelState* kernel_state) {
  auto memory = kernel_state->memory();

  uint32_t pVdGlobalDevice = memory->SystemHeapAlloc(4, 32, memory::kSystemHeapPhysical);
  export_resolver->SetVariableMapping("xboxkrnl.exe", 0x01BE, pVdGlobalDevice);
  memory::store_and_swap<uint32_t>(memory->TranslateVirtual(pVdGlobalDevice), 0);

  uint32_t pVdGlobalXamDevice = memory->SystemHeapAlloc(4, 32, memory::kSystemHeapPhysical);
  export_resolver->SetVariableMapping("xboxkrnl.exe", 0x01BF, pVdGlobalXamDevice);
  memory::store_and_swap<uint32_t>(memory->TranslateVirtual(pVdGlobalXamDevice), 0);

  uint32_t pVdGpuClockInMHz = memory->SystemHeapAlloc(4, 32, memory::kSystemHeapPhysical);
  export_resolver->SetVariableMapping("xboxkrnl.exe", 0x01C0, pVdGpuClockInMHz);
  memory::store_and_swap<uint32_t>(memory->TranslateVirtual(pVdGpuClockInMHz), 500);

  uint32_t pVdHSIOCalibrationLock = memory->SystemHeapAlloc(28, 32, memory::kSystemHeapPhysical);
  export_resolver->SetVariableMapping("xboxkrnl.exe", 0x01C1, pVdHSIOCalibrationLock);
  auto hsio_lock = memory->TranslateVirtual<X_RTL_CRITICAL_SECTION*>(pVdHSIOCalibrationLock);
  xeRtlInitializeCriticalSectionAndSpinCount(hsio_lock, pVdHSIOCalibrationLock, 10000);
}

}

REX_EXPORT(__imp__VdGetCurrentDisplayGamma, rex::kernel::xboxkrnl::VdGetCurrentDisplayGamma_entry)
REX_EXPORT(__imp__VdGetCurrentDisplayInformation,
           rex::kernel::xboxkrnl::VdGetCurrentDisplayInformation_entry)
REX_EXPORT(__imp__VdQueryVideoMode, rex::kernel::xboxkrnl::VdQueryVideoMode_entry)
REX_EXPORT(__imp__VdQueryVideoFlags, rex::kernel::xboxkrnl::VdQueryVideoFlags_entry)
REX_EXPORT(__imp__VdSetDisplayMode, rex::kernel::xboxkrnl::VdSetDisplayMode_entry)
REX_EXPORT(__imp__VdSetDisplayModeOverride, rex::kernel::xboxkrnl::VdSetDisplayModeOverride_entry)
REX_EXPORT(__imp__VdInitializeEngines, rex::kernel::xboxkrnl::VdInitializeEngines_entry)
REX_EXPORT(__imp__VdShutdownEngines, rex::kernel::xboxkrnl::VdShutdownEngines_entry)
REX_EXPORT(__imp__VdGetGraphicsAsicID, rex::kernel::xboxkrnl::VdGetGraphicsAsicID_entry)
REX_EXPORT(__imp__VdEnableDisableClockGating,
           rex::kernel::xboxkrnl::VdEnableDisableClockGating_entry)
REX_EXPORT(__imp__VdSetGraphicsInterruptCallback,
           rex::kernel::xboxkrnl::VdSetGraphicsInterruptCallback_entry)
REX_EXPORT(__imp__VdInitializeRingBuffer, rex::kernel::xboxkrnl::VdInitializeRingBuffer_entry)
REX_EXPORT(__imp__VdEnableRingBufferRPtrWriteBack,
           rex::kernel::xboxkrnl::VdEnableRingBufferRPtrWriteBack_entry)
REX_EXPORT(__imp__VdGetSystemCommandBuffer, rex::kernel::xboxkrnl::VdGetSystemCommandBuffer_entry)
REX_EXPORT(__imp__VdSetSystemCommandBufferGpuIdentifierAddress,
           rex::kernel::xboxkrnl::VdSetSystemCommandBufferGpuIdentifierAddress_entry)
REX_EXPORT(__imp__VdInitializeScalerCommandBuffer,
           rex::kernel::xboxkrnl::VdInitializeScalerCommandBuffer_entry)
REX_EXPORT(__imp__VdCallGraphicsNotificationRoutines,
           rex::kernel::xboxkrnl::VdCallGraphicsNotificationRoutines_entry)
REX_EXPORT(__imp__VdIsHSIOTrainingSucceeded, rex::kernel::xboxkrnl::VdIsHSIOTrainingSucceeded_entry)
REX_EXPORT(__imp__VdPersistDisplay, rex::kernel::xboxkrnl::VdPersistDisplay_entry)
REX_EXPORT(__imp__VdRetrainEDRAMWorker, rex::kernel::xboxkrnl::VdRetrainEDRAMWorker_entry)
REX_EXPORT(__imp__VdRetrainEDRAM, rex::kernel::xboxkrnl::VdRetrainEDRAM_entry)
REX_EXPORT(__imp__VdSwap, rex::kernel::xboxkrnl::VdSwap_entry)
