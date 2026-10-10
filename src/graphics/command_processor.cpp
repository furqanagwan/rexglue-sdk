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

#include <algorithm>
#include <cinttypes>
#include <cmath>
#include <cstring>
#include <string_view>

#include <fmt/format.h>

#include <rex/cvar.h>
#include <rex/dbg.h>
#include <rex/perf/counter.h>
#include <rex/chrono/clock.h>
#include <rex/graphics/command_processor.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/graphics_system.h>
#include <rex/graphics/pipeline/texture/info.h>
#include <rex/graphics/sampler_info.h>
#include <rex/graphics/xenos.h>
#include <rex/logging.h>
#include <rex/math.h>
#include <rex/memory.h>
#include <rex/memory/ring_buffer.h>
#include <rex/stream.h>
#include <rex/system/kernel_state.h>
#include <rex/system/user_module.h>

REXCVAR_DEFINE_BOOL(vsync, true, "GPU", "Enable vertical sync");

REXCVAR_DEFINE_INT32(frame_stats_interval, 0, "GPU",
                     "Log guest frame pacing (fps and frame time percentiles between swaps) "
                     "every this many seconds; 0 = off")
    .range(0, 3600);

REXCVAR_DEFINE_BOOL(clear_memory_page_state, true, "GPU",
                    "Refresh page-valid state from GPU-written memory at frame end. "
                    "Disable for minor CPU overhead reduction, but may break memory coherency.")
    .lifecycle(rex::cvar::Lifecycle::kHotReload);

REXCVAR_DEFINE_BOOL(occlusion_query_enable, true, "GPU",
                    "Enable host occlusion queries for EVENT_WRITE_ZPD. When disabled, "
                    "occlusion_query is treated as fake.")
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);

REXCVAR_DEFINE_STRING(occlusion_query, "fast", "GPU",
                      "Controls host occlusion query behavior for EVENT_WRITE_ZPD.\n"
                      "Used for effects like lens flares, object culling, and auto-exposure.\n"
                      " fake: Write a fake result without asking the GPU.\n"
                      " fast: Ask the GPU but don't wait for the answer. Writes a cached\n"
                      "       result immediately and corrects it when the GPU catches up.\n"
                      "       Cached results bias toward visible when guessing. (default)\n"
                      " fast-alt: Like fast, but keeps cached zero results for unresolved\n"
                      "           reports. May improve effects relying on precise visibility,\n"
                      "           but may be less stable for occlusion culling.\n"
                      " strict: Ask the GPU and wait for the real result before the guest\n"
                      "         sees it. Most accurate, may be slower.")
    .allowed({"fake", "fast", "fast-alt", "strict"})
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);

REXCVAR_DEFINE_BOOL(occlusion_query_viz, false, "GPU",
                    "VIZ_QUERY visibility tests for draws with a VIZ token, the Xbox 360's "
                    "conditional rendering: occlusion queries over the survey draws predicate "
                    "the draws that use them, skipping hidden ones on the GPU (xenia-canary "
                    "#1111). Costs most with ROV")
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);
REXCVAR_DEFINE_BOOL(occlusion_query_full_counters, false, "GPU",
                    "Also count the samples that fail the depth or stencil test in occlusion "
                    "queries, as the Xbox 360 does. Only the ROV path "
                    "(render_target_path_d3d12 = \"rov\") counts them; otherwise they stay "
                    "0 and the total equals the passed count. Changes the translated shaders")
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);

REXCVAR_DEFINE_STRING(readback_resolve, "fast", "GPU",
                      "Controls CPU readback of render-to-texture resolve results.\n"
                      " none: Disable readback (breaks titles that read results back)\n"
                      " fast: Read previous frame (delayed, copy every frame; default)\n"
                      " some: Read previous frame (delayed, copy on cache miss)\n"
                      " full: Immediate sync readback (accurate but stalls)")
    .allowed({"none", "fast", "some", "full"})
    .lifecycle(rex::cvar::Lifecycle::kHotReload);

REXCVAR_DEFINE_BOOL(readback_resolve_half_pixel_offset, false, "GPU",
                    "When draw resolution scaling is active, sample from the center of each "
                    "scaled block during resolve readback downscale")
    .lifecycle(rex::cvar::Lifecycle::kHotReload);

REXCVAR_DEFINE_BOOL(readback_memexport, true, "GPU",
                    "Enable CPU readback of shader memexport writes for guest memory "
                    "coherency (can reduce correctness issues, but may add GPU/CPU sync cost)")
    .lifecycle(rex::cvar::Lifecycle::kHotReload);

REXCVAR_DEFINE_BOOL(readback_memexport_fast, true, "GPU",
                    "Use fast double-buffered memexport readback when possible, with "
                    "automatic fallback to full synchronous readback")
    .lifecycle(rex::cvar::Lifecycle::kHotReload);

REXCVAR_DEFINE_INT32(query_occlusion_fake_sample_count, 1000, "GPU",
                     "Samples each occlusion query interval reports in fake mode")
    .range(1, 100000)
    .lifecycle(rex::cvar::Lifecycle::kHotReload);

REXCVAR_DEFINE_BOOL(async_shader_compilation, true, "GPU",
                    "Compile shaders and create pipelines asynchronously in background "
                    "threads. This reduces stutter but may cause brief visual artifacts while "
                    "pipelines are being prepared.")
    .lifecycle(rex::cvar::Lifecycle::kHotReload);

namespace rex::graphics {

using namespace rex::graphics::xenos;

namespace {

ReadbackResolveMode ParseReadbackResolveMode(std::string_view value) {
  if (value == "fast") {
    return ReadbackResolveMode::kFast;
  }
  if (value == "some") {
    return ReadbackResolveMode::kSome;
  }
  if (value == "full") {
    return ReadbackResolveMode::kFull;
  }
  return ReadbackResolveMode::kDisabled;
}

}

ZPDMode GetZPDMode() {
  if (!REXCVAR_GET(occlusion_query_enable)) {
    return ZPDMode::kFake;
  }
  const std::string& mode = REXCVAR_GET(occlusion_query);
  if (mode == "fake") {
    return ZPDMode::kFake;
  }
  if (mode == "strict") {
    return ZPDMode::kStrict;
  }
  if (mode == "fast-alt") {
    return ZPDMode::kFastAlt;
  }
  return ZPDMode::kFast;
}

CommandProcessor::CommandProcessor(GraphicsSystem* graphics_system,
                                   system::KernelState* kernel_state)
    : memory_(graphics_system->memory()),
      kernel_state_(kernel_state),
      graphics_system_(graphics_system),
      register_file_(graphics_system_->register_file()),
      worker_running_(true),
      write_ptr_index_event_(rex::thread::Event::CreateAutoResetEvent(false)),
      write_ptr_index_(0) {
  assert_not_null(write_ptr_index_event_);
}

CommandProcessor::~CommandProcessor() = default;

bool CommandProcessor::Initialize() {
  for (uint32_t i = 0; i < 256; ++i) {
    uint32_t value = i * 0x3FF / 0xFF;
    reg::DC_LUT_30_COLOR& gamma_ramp_entry = gamma_ramp_256_entry_table_[i];
    gamma_ramp_entry.color_10_blue = value;
    gamma_ramp_entry.color_10_green = value;
    gamma_ramp_entry.color_10_red = value;
  }
  for (uint32_t i = 0; i < 128; ++i) {
    reg::DC_LUT_PWL_DATA gamma_ramp_entry = {};
    gamma_ramp_entry.base = (i * 0xFFFF / 0x7F) & ~UINT32_C(0x3F);
    gamma_ramp_entry.delta = i < 0x7F ? 0x200 : 0;
    for (uint32_t j = 0; j < 3; ++j) {
      gamma_ramp_pwl_rgb_[i][j] = gamma_ramp_entry;
    }
  }

  worker_running_ = true;
  worker_thread_ = system::object_ref<system::XHostThread>(
      new system::XHostThread(kernel_state_, 128 * 1024, 0, [this]() {
        WorkerThreadMain();
        return 0;
      }));
  worker_thread_->set_name("GPU Commands");
  worker_thread_->Create();

  return true;
}

void CommandProcessor::Shutdown() {
  worker_running_ = false;
  write_ptr_index_event_->Set();
  worker_thread_->Wait(0, 0, 0, nullptr);
  worker_thread_.reset();
}

void CommandProcessor::InitializeShaderStorage(const std::filesystem::path& cache_root,
                                               uint32_t title_id, bool blocking) {}

void CommandProcessor::CallInThread(std::function<void()> fn) {
  if (pending_fns_.empty() && system::XThread::IsInThread(worker_thread_.get())) {
    fn();
  } else {
    pending_fns_.push(std::move(fn));
  }
}

void CommandProcessor::ClearCaches() {}

void CommandProcessor::InvalidateGpuMemory() {}

ReadbackResolveMode CommandProcessor::GetReadbackResolveMode(
    bool legacy_readback_resolve_enabled) const {
  ReadbackResolveMode shared_mode = ParseReadbackResolveMode(REXCVAR_GET(readback_resolve));
  bool shared_mode_overrides_legacy = shared_mode != ReadbackResolveMode::kDisabled ||
                                      rex::cvar::HasNonDefaultValue("readback_resolve");
  if (shared_mode_overrides_legacy) {
    return shared_mode;
  }
  return legacy_readback_resolve_enabled ? ReadbackResolveMode::kFast
                                         : ReadbackResolveMode::kDisabled;
}

bool CommandProcessor::IsReadbackMemexportEnabled(bool legacy_backend_flag) const {
  if (legacy_readback_memexport_cvar_name_ &&
      rex::cvar::HasNonDefaultValue(legacy_readback_memexport_cvar_name_)) {
    return legacy_backend_flag;
  }
  return REXCVAR_GET(readback_memexport);
}

void CommandProcessor::SetDesiredSwapPostEffect(SwapPostEffect swap_post_effect) {
  if (swap_post_effect_desired_ == swap_post_effect) {
    return;
  }
  swap_post_effect_desired_ = swap_post_effect;
  CallInThread([this, swap_post_effect]() { swap_post_effect_actual_ = swap_post_effect; });
}

void CommandProcessor::WorkerThreadMain() {
  if (!SetupContext()) {
    rex::FatalError("Unable to setup command processor internal state");
    return;
  }

  while (worker_running_) {
    while (!pending_fns_.empty()) {
      auto fn = std::move(pending_fns_.front());
      pending_fns_.pop();
      fn();
    }

    uint32_t write_ptr_index = write_ptr_index_.load();
    if (write_ptr_index == 0xBAADF00D || read_ptr_index_ == write_ptr_index) {
      SCOPE_profile_cpu_i("gpu", "rex::graphics::CommandProcessor::Stall");

      PrepareForWait();
      const uint64_t idle_start = rex::chrono::Clock::QueryHostTickCount();
      uint32_t loop_count = 0;
      do {
        if (loop_count > 500) {
          const int wait_time_ms = 5;
          rex::thread::Wait(write_ptr_index_event_.get(), true,
                            std::chrono::milliseconds(wait_time_ms));

          if (zpd_mode_ == ZPDMode::kStrict && zpd_awaited_report_count_) {
            PrepareForWait();
          }
        }

        rex::thread::MaybeYield();
        loop_count++;
        write_ptr_index = write_ptr_index_.load();
      } while (worker_running_ && pending_fns_.empty() &&
               (write_ptr_index == 0xBAADF00D || read_ptr_index_ == write_ptr_index));
      frame_stats_idle_ticks_ += rex::chrono::Clock::QueryHostTickCount() - idle_start;
      ReturnFromWait();
      if (!worker_running_ || !pending_fns_.empty()) {
        continue;
      }
    }
    assert_true(read_ptr_index_ != write_ptr_index);

    read_ptr_index_ = ExecutePrimaryBuffer(read_ptr_index_, write_ptr_index);

    if (read_ptr_writeback_ptr_) {
      memory::store_and_swap<uint32_t>(memory_->TranslatePhysical(read_ptr_writeback_ptr_),
                                       read_ptr_index_);
    }
  }

  ShutdownContext();
}

void CommandProcessor::Pause() {
  if (paused_) {
    return;
  }
  paused_ = true;

  thread::Fence fence;
  CallInThread([&fence]() {
    fence.Signal();
    thread::Thread::GetCurrentThread()->Suspend();
  });

  fence.Wait();
}

void CommandProcessor::Resume() {
  if (!paused_) {
    return;
  }
  paused_ = false;

  worker_thread_->thread()->Resume();
}

bool CommandProcessor::Save(::rex::stream::ByteStream* stream) {
  assert_true(paused_);

  stream->Write<uint32_t>(primary_buffer_ptr_);
  stream->Write<uint32_t>(primary_buffer_size_);
  stream->Write<uint32_t>(read_ptr_index_);
  stream->Write<uint32_t>(read_ptr_update_freq_);
  stream->Write<uint32_t>(read_ptr_writeback_ptr_);
  stream->Write<uint32_t>(write_ptr_index_.load());

  return true;
}

bool CommandProcessor::Restore(::rex::stream::ByteStream* stream) {
  assert_true(paused_);

  primary_buffer_ptr_ = stream->Read<uint32_t>();
  primary_buffer_size_ = stream->Read<uint32_t>();
  read_ptr_index_ = stream->Read<uint32_t>();
  read_ptr_update_freq_ = stream->Read<uint32_t>();
  read_ptr_writeback_ptr_ = stream->Read<uint32_t>();
  write_ptr_index_.store(stream->Read<uint32_t>());

  return true;
}

bool CommandProcessor::SetupContext() {
  ResetVIZState();
  ResetZPDState();
  return true;
}

void CommandProcessor::ShutdownContext() {
  ResetVIZState();
  ResetZPDState();
}

void CommandProcessor::InitializeRingBuffer(uint32_t ptr, uint32_t size_log2) {
  read_ptr_index_ = 0;
  primary_buffer_ptr_ = ptr;
  primary_buffer_size_ = uint32_t(1) << (size_log2 + 3);
}

void CommandProcessor::EnableReadPointerWriteBack(uint32_t ptr, uint32_t block_size_log2) {
  read_ptr_writeback_ptr_ = ptr;

  read_ptr_update_freq_ = (uint32_t(1) << std::min(block_size_log2, 19u)) * 2;
}

void CommandProcessor::UpdateWritePointer(uint32_t value) {
  write_ptr_index_ = value;
  write_ptr_index_event_->Set();
}

uint32_t CommandProcessor::ReadRegisterValue(uint32_t index) const {
  if (index < RegisterFile::kRegisterCount) {
    return register_file_->values[index];
  }
  auto it = extended_register_values_.find(index);
  return it != extended_register_values_.end() ? it->second : 0;
}

void CommandProcessor::WriteRegister(uint32_t index, uint32_t value) {
  RegisterFile& regs = *register_file_;
  if (index >= RegisterFile::kRegisterCount) {
    auto [it, inserted] = extended_register_values_.insert_or_assign(index, value);
    (void)it;
    if (inserted) {
      REXGPU_WARN(
          "CommandProcessor::WriteRegister index out of bounds: {} (stored as extended register)",
          index);
    }
    return;
  }

  const_cast<volatile uint32_t&>(regs.values[index]) = value;
  if (!regs.GetRegisterInfo(index)) {
    REXGPU_DEBUG("GPU: Write to unknown register ({:04X} = {:08X})", index, value);
  }

  if (index >= XE_GPU_REG_SCRATCH_REG0 && index <= XE_GPU_REG_SCRATCH_REG7) {
    uint32_t scratch_reg = index - XE_GPU_REG_SCRATCH_REG0;
    if ((1 << scratch_reg) & regs.values[XE_GPU_REG_SCRATCH_UMSK]) {
      uint32_t scratch_addr = regs.values[XE_GPU_REG_SCRATCH_ADDR];
      uint32_t mem_addr = scratch_addr + (scratch_reg * 4);
      memory::store_and_swap<uint32_t>(memory_->TranslatePhysical(mem_addr), value);
    }
  } else {
    switch (index) {
      case XE_GPU_REG_COHER_STATUS_HOST: {
        const_cast<volatile uint32_t&>(regs.values[index]) |= UINT32_C(0x80000000);
      } break;

      case XE_GPU_REG_DC_LUT_RW_INDEX: {
        gamma_ramp_rw_component_ = 0;
      } break;

      case XE_GPU_REG_DC_LUT_SEQ_COLOR: {
        assert_zero(regs[XE_GPU_REG_DC_LUT_RW_MODE] & 0b1);
        auto gamma_ramp_rw_index = regs.Get<reg::DC_LUT_RW_INDEX>();

        bool write_gamma_ramp_component = (regs[XE_GPU_REG_DC_LUT_WRITE_EN_MASK] &
                                           (UINT32_C(1) << (2 - gamma_ramp_rw_component_))) != 0;
        if (write_gamma_ramp_component) {
          reg::DC_LUT_30_COLOR& gamma_ramp_entry =
              gamma_ramp_256_entry_table_[gamma_ramp_rw_index.rw_index];

          uint32_t gamma_ramp_seq_color = regs.Get<reg::DC_LUT_SEQ_COLOR>().seq_color >> 6;
          switch (gamma_ramp_rw_component_) {
            case 0:
              gamma_ramp_entry.color_10_red = gamma_ramp_seq_color;
              break;
            case 1:
              gamma_ramp_entry.color_10_green = gamma_ramp_seq_color;
              break;
            case 2:
              gamma_ramp_entry.color_10_blue = gamma_ramp_seq_color;
              break;
          }
        }
        if (++gamma_ramp_rw_component_ >= 3) {
          gamma_ramp_rw_component_ = 0;
          reg::DC_LUT_RW_INDEX new_gamma_ramp_rw_index = gamma_ramp_rw_index;
          ++new_gamma_ramp_rw_index.rw_index;
          WriteRegister(XE_GPU_REG_DC_LUT_RW_INDEX,
                        rex::memory::Reinterpret<uint32_t>(new_gamma_ramp_rw_index));
        }
        if (write_gamma_ramp_component) {
          OnGammaRamp256EntryTableValueWritten();
        }
      } break;

      case XE_GPU_REG_DC_LUT_PWL_DATA: {
        assert_not_zero(regs[XE_GPU_REG_DC_LUT_RW_MODE] & 0b1);
        auto gamma_ramp_rw_index = regs.Get<reg::DC_LUT_RW_INDEX>();

        uint32_t gamma_ramp_rw_index_pwl = gamma_ramp_rw_index.rw_index & 0x7F;

        bool write_gamma_ramp_component = (regs[XE_GPU_REG_DC_LUT_WRITE_EN_MASK] &
                                           (UINT32_C(1) << (2 - gamma_ramp_rw_component_))) != 0;
        if (write_gamma_ramp_component) {
          reg::DC_LUT_PWL_DATA& gamma_ramp_entry =
              gamma_ramp_pwl_rgb_[gamma_ramp_rw_index_pwl][gamma_ramp_rw_component_];
          auto gamma_ramp_value = regs.Get<reg::DC_LUT_PWL_DATA>();

          gamma_ramp_entry.base = gamma_ramp_value.base & ~UINT32_C(0x3F);
          gamma_ramp_entry.delta = gamma_ramp_value.delta & ~UINT32_C(0x3F);
        }
        if (++gamma_ramp_rw_component_ >= 3) {
          gamma_ramp_rw_component_ = 0;
          reg::DC_LUT_RW_INDEX new_gamma_ramp_rw_index = gamma_ramp_rw_index;

          new_gamma_ramp_rw_index.rw_index = (gamma_ramp_rw_index.rw_index & ~UINT32_C(0x7F)) |
                                             ((gamma_ramp_rw_index_pwl + 1) & 0x7F);
          WriteRegister(XE_GPU_REG_DC_LUT_RW_INDEX,
                        rex::memory::Reinterpret<uint32_t>(new_gamma_ramp_rw_index));
        }
        if (write_gamma_ramp_component) {
          OnGammaRampPWLValueWritten();
        }
      } break;

      case XE_GPU_REG_DC_LUT_30_COLOR: {
        assert_zero(regs[XE_GPU_REG_DC_LUT_RW_MODE] & 0b1);
        auto gamma_ramp_rw_index = regs.Get<reg::DC_LUT_RW_INDEX>();
        uint32_t gamma_ramp_write_enable_mask = regs[XE_GPU_REG_DC_LUT_WRITE_EN_MASK] & 0b111;
        if (gamma_ramp_write_enable_mask) {
          reg::DC_LUT_30_COLOR& gamma_ramp_entry =
              gamma_ramp_256_entry_table_[gamma_ramp_rw_index.rw_index];
          auto gamma_ramp_value = regs.Get<reg::DC_LUT_30_COLOR>();
          if (gamma_ramp_write_enable_mask & 0b001) {
            gamma_ramp_entry.color_10_blue = gamma_ramp_value.color_10_blue;
          }
          if (gamma_ramp_write_enable_mask & 0b010) {
            gamma_ramp_entry.color_10_green = gamma_ramp_value.color_10_green;
          }
          if (gamma_ramp_write_enable_mask & 0b100) {
            gamma_ramp_entry.color_10_red = gamma_ramp_value.color_10_red;
          }
        }

        gamma_ramp_rw_component_ = 0;
        reg::DC_LUT_RW_INDEX new_gamma_ramp_rw_index = gamma_ramp_rw_index;
        ++new_gamma_ramp_rw_index.rw_index;
        WriteRegister(XE_GPU_REG_DC_LUT_RW_INDEX,
                      rex::memory::Reinterpret<uint32_t>(new_gamma_ramp_rw_index));
        if (gamma_ramp_write_enable_mask) {
          OnGammaRamp256EntryTableValueWritten();
        }
      } break;
    }
  }
}

void CommandProcessor::WriteRegistersFromMem(uint32_t start_index, uint32_t* base,
                                             uint32_t num_registers) {
  for (uint32_t i = 0; i < num_registers; ++i) {
    uint32_t data = memory::load_and_swap<uint32_t>(base + i);
    WriteRegister(start_index + i, data);
  }
}

void CommandProcessor::WriteRegisterRangeFromRing(memory::RingBuffer* ring, uint32_t base,
                                                  uint32_t num_registers) {
  if (!num_registers) {
    return;
  }
  memory::RingBuffer::ReadRange range = ring->BeginRead(size_t(num_registers) * sizeof(uint32_t));
  if (range.first_length != 0) {
    uint32_t first_count = uint32_t(range.first_length / sizeof(uint32_t));
    WriteRegistersFromMem(base, reinterpret_cast<uint32_t*>(const_cast<uint8_t*>(range.first)),
                          first_count);
    base += first_count;
  }
  if (range.second_length != 0) {
    WriteRegistersFromMem(base, reinterpret_cast<uint32_t*>(const_cast<uint8_t*>(range.second)),
                          uint32_t(range.second_length / sizeof(uint32_t)));
  }
  ring->EndRead(range);
}

void CommandProcessor::WriteALURangeFromRing(memory::RingBuffer* ring, uint32_t base,
                                             uint32_t num_registers) {
  WriteRegisterRangeFromRing(ring, base + 0x4000, num_registers);
}

void CommandProcessor::WriteFetchRangeFromRing(memory::RingBuffer* ring, uint32_t base,
                                               uint32_t num_registers) {
  WriteRegisterRangeFromRing(ring, base + 0x4800, num_registers);
}

void CommandProcessor::WriteBoolRangeFromRing(memory::RingBuffer* ring, uint32_t base,
                                              uint32_t num_registers) {
  WriteRegisterRangeFromRing(ring, base + 0x4900, num_registers);
}

void CommandProcessor::WriteLoopRangeFromRing(memory::RingBuffer* ring, uint32_t base,
                                              uint32_t num_registers) {
  WriteRegisterRangeFromRing(ring, base + 0x4908, num_registers);
}

void CommandProcessor::WriteREGISTERSRangeFromRing(memory::RingBuffer* ring, uint32_t base,
                                                   uint32_t num_registers) {
  WriteRegisterRangeFromRing(ring, base + 0x2000, num_registers);
}

void CommandProcessor::WriteALURangeFromMem(uint32_t start_index, uint32_t* base,
                                            uint32_t num_registers) {
  WriteRegistersFromMem(start_index + 0x4000, base, num_registers);
}

void CommandProcessor::WriteFetchRangeFromMem(uint32_t start_index, uint32_t* base,
                                              uint32_t num_registers) {
  WriteRegistersFromMem(start_index + 0x4800, base, num_registers);
}

void CommandProcessor::WriteBoolRangeFromMem(uint32_t start_index, uint32_t* base,
                                             uint32_t num_registers) {
  WriteRegistersFromMem(start_index + 0x4900, base, num_registers);
}

void CommandProcessor::WriteLoopRangeFromMem(uint32_t start_index, uint32_t* base,
                                             uint32_t num_registers) {
  WriteRegistersFromMem(start_index + 0x4908, base, num_registers);
}

void CommandProcessor::WriteREGISTERSRangeFromMem(uint32_t start_index, uint32_t* base,
                                                  uint32_t num_registers) {
  WriteRegistersFromMem(start_index + 0x2000, base, num_registers);
}

void CommandProcessor::MakeCoherent() {
  SCOPE_profile_cpu_f("gpu");

  volatile uint32_t* regs_volatile = register_file_->values;
  auto status_host = rex::memory::Reinterpret<reg::COHER_STATUS_HOST>(
      uint32_t(regs_volatile[XE_GPU_REG_COHER_STATUS_HOST]));
  uint32_t base_host = regs_volatile[XE_GPU_REG_COHER_BASE_HOST];
  uint32_t size_host = regs_volatile[XE_GPU_REG_COHER_SIZE_HOST];

  if (!status_host.status) {
    return;
  }

  const char* action = "N/A";
  if (status_host.vc_action_ena && status_host.tc_action_ena) {
    action = "VC | TC";
  } else if (status_host.tc_action_ena) {
    action = "TC";
  } else if (status_host.vc_action_ena) {
    action = "VC";
  }

  REXGPU_TRACE("Make {:08X} -> {:08X} ({}b) coherent, action = {}", base_host,
               base_host + size_host, size_host, action);

  regs_volatile[XE_GPU_REG_COHER_STATUS_HOST] = 0;
}

void CommandProcessor::PrepareForWait() {
  if (zpd_mode_ == ZPDMode::kStrict && zpd_awaited_report_count_) {
    PrepareZPDForWait();
  }
  if (viz_pending_resolves_) {
    PollCompletedSubmission();
  }
}

void CommandProcessor::ReturnFromWait() {}

uint32_t CommandProcessor::ExecutePrimaryBuffer(uint32_t read_index, uint32_t write_index) {
  SCOPE_profile_cpu_f("gpu");

  memory::RingBuffer reader(memory_->TranslatePhysical(primary_buffer_ptr_), primary_buffer_size_);
  reader.set_read_offset(read_index * sizeof(uint32_t));
  reader.set_write_offset(write_index * sizeof(uint32_t));

  const size_t writeback_stride = size_t(read_ptr_update_freq_) * sizeof(uint32_t);
  size_t remaining = reader.read_count();
  size_t remaining_at_writeback = remaining;
  do {
    if (!ExecutePacket(&reader)) {
      REXGPU_ERROR("**** PRIMARY RINGBUFFER: Failed to execute packet.");
      assert_always();
      break;
    }
    remaining = reader.read_count();

    if (writeback_stride && remaining <= remaining_at_writeback &&
        remaining_at_writeback - remaining >= writeback_stride) {
      uint32_t writeback_ptr = read_ptr_writeback_ptr_;
      if (writeback_ptr) {
        std::atomic_thread_fence(std::memory_order_release);
        memory::store_and_swap<uint32_t>(memory_->TranslatePhysical(writeback_ptr),
                                         uint32_t(reader.read_offset() / sizeof(uint32_t)));
      }
      remaining_at_writeback = remaining;
    }
  } while (remaining);

  OnPrimaryBufferEnd();

  return write_index;
}

void CommandProcessor::ExecuteIndirectBuffer(uint32_t ptr, uint32_t count) {
  SCOPE_profile_cpu_f("gpu");

  memory::RingBuffer reader(memory_->TranslatePhysical(ptr), count * sizeof(uint32_t));
  reader.set_write_offset(count * sizeof(uint32_t));
  do {
    if (!ExecutePacket(&reader)) {
      REXGPU_ERROR("**** INDIRECT RINGBUFFER: Failed to execute packet.");
      assert_always();
      break;
    }
  } while (reader.read_count());
}

void CommandProcessor::ExecutePacket(uint32_t ptr, uint32_t count) {
  memory::RingBuffer reader(memory_->TranslatePhysical(ptr), count * sizeof(uint32_t));
  reader.set_write_offset(count * sizeof(uint32_t));
  do {
    if (!ExecutePacket(&reader)) {
      REXGPU_ERROR("**** ExecutePacket: Failed to execute packet.");
      assert_always();
      break;
    }
  } while (reader.read_count());
}

bool CommandProcessor::ExecutePacket(memory::RingBuffer* reader) {
  const uint32_t packet = reader->ReadAndSwap<uint32_t>();
  const uint32_t packet_type = packet >> 30;
  if (packet == 0) {
    return true;
  }

  if (packet == 0xCDCDCDCD) {
    REXGPU_WARN("GPU packet is CDCDCDCD - probably read uninitialized memory!");
  }

  switch (packet_type) {
    case 0x00:
      return ExecutePacketType0(reader, packet);
    case 0x01:
      return ExecutePacketType1(reader, packet);
    case 0x02:
      return ExecutePacketType2(reader, packet);
    case 0x03:
      return ExecutePacketType3(reader, packet);
    default:
      assert_unhandled_case(packet_type);
      return false;
  }
}

bool CommandProcessor::ExecutePacketType0(memory::RingBuffer* reader, uint32_t packet) {
  uint32_t count = ((packet >> 16) & 0x3FFF) + 1;
  if (reader->read_count() < count * sizeof(uint32_t)) {
    REXGPU_ERROR("ExecutePacketType0 overflow (read count {:08X}, packet count {:08X})",
                 reader->read_count(), count * sizeof(uint32_t));
    return false;
  }

  uint32_t base_index = (packet & 0x7FFF);
  uint32_t write_one_reg = (packet >> 15) & 0x1;
  for (uint32_t m = 0; m < count; m++) {
    uint32_t reg_data = reader->ReadAndSwap<uint32_t>();
    uint32_t target_index = write_one_reg ? base_index : base_index + m;
    WriteRegister(target_index, reg_data);
  }

  return true;
}

bool CommandProcessor::ExecutePacketType1(memory::RingBuffer* reader, uint32_t packet) {
  uint32_t reg_index_1 = packet & 0x7FF;
  uint32_t reg_index_2 = (packet >> 11) & 0x7FF;
  uint32_t reg_data_1 = reader->ReadAndSwap<uint32_t>();
  uint32_t reg_data_2 = reader->ReadAndSwap<uint32_t>();
  WriteRegister(reg_index_1, reg_data_1);
  WriteRegister(reg_index_2, reg_data_2);
  return true;
}

bool CommandProcessor::ExecutePacketType2(memory::RingBuffer* reader, uint32_t packet) {
  return true;
}

bool CommandProcessor::ExecutePacketType3(memory::RingBuffer* reader, uint32_t packet) {
  uint32_t opcode = (packet >> 8) & 0x7F;
  uint32_t count = ((packet >> 16) & 0x3FFF) + 1;
  auto data_start_offset = reader->read_offset();

  if (reader->read_count() < count * sizeof(uint32_t)) {
    REXGPU_ERROR("ExecutePacketType3 overflow (read count {:08X}, packet count {:08X})",
                 reader->read_count(), count * sizeof(uint32_t));
    return false;
  }

  if (packet & 1) {
    bool any_pass = (bin_select_ & bin_mask_) != 0;
    if (!any_pass || opcode == PM4_XE_SWAP) {
      reader->AdvanceRead(count * sizeof(uint32_t));
      return true;
    }
  }

  bool result = false;
  switch (opcode) {
    case PM4_ME_INIT:
      result = ExecutePacketType3_ME_INIT(reader, packet, count);
      break;
    case PM4_NOP:
      result = ExecutePacketType3_NOP(reader, packet, count);
      break;
    case PM4_INTERRUPT:
      result = ExecutePacketType3_INTERRUPT(reader, packet, count);
      break;
    case PM4_XE_SWAP:
      result = ExecutePacketType3_XE_SWAP(reader, packet, count);
      break;
    case PM4_INDIRECT_BUFFER:
    case PM4_INDIRECT_BUFFER_PFD:
      result = ExecutePacketType3_INDIRECT_BUFFER(reader, packet, count);
      break;
    case PM4_WAIT_REG_MEM:
      result = ExecutePacketType3_WAIT_REG_MEM(reader, packet, count);
      break;
    case PM4_REG_RMW:
      result = ExecutePacketType3_REG_RMW(reader, packet, count);
      break;
    case PM4_REG_TO_MEM:
      result = ExecutePacketType3_REG_TO_MEM(reader, packet, count);
      break;
    case PM4_MEM_WRITE:
      result = ExecutePacketType3_MEM_WRITE(reader, packet, count);
      break;
    case PM4_COND_WRITE:
      result = ExecutePacketType3_COND_WRITE(reader, packet, count);
      break;
    case PM4_EVENT_WRITE:
      result = ExecutePacketType3_EVENT_WRITE(reader, packet, count);
      break;
    case PM4_EVENT_WRITE_SHD:
      result = ExecutePacketType3_EVENT_WRITE_SHD(reader, packet, count);
      break;
    case PM4_EVENT_WRITE_EXT:
      result = ExecutePacketType3_EVENT_WRITE_EXT(reader, packet, count);
      break;
    case PM4_EVENT_WRITE_ZPD:
      result = ExecutePacketType3_EVENT_WRITE_ZPD(reader, packet, count);
      break;
    case PM4_DRAW_INDX:
      result = ExecutePacketType3_DRAW_INDX(reader, packet, count);
      break;
    case PM4_DRAW_INDX_2:
      result = ExecutePacketType3_DRAW_INDX_2(reader, packet, count);
      break;
    case PM4_SET_CONSTANT:
      result = ExecutePacketType3_SET_CONSTANT(reader, packet, count);
      break;
    case PM4_SET_CONSTANT2:
      result = ExecutePacketType3_SET_CONSTANT2(reader, packet, count);
      break;
    case PM4_LOAD_ALU_CONSTANT:
      result = ExecutePacketType3_LOAD_ALU_CONSTANT(reader, packet, count);
      break;
    case PM4_SET_SHADER_CONSTANTS:
      result = ExecutePacketType3_SET_SHADER_CONSTANTS(reader, packet, count);
      break;
    case PM4_IM_LOAD:
      result = ExecutePacketType3_IM_LOAD(reader, packet, count);
      break;
    case PM4_IM_LOAD_IMMEDIATE:
      result = ExecutePacketType3_IM_LOAD_IMMEDIATE(reader, packet, count);
      break;
    case PM4_INVALIDATE_STATE:
      result = ExecutePacketType3_INVALIDATE_STATE(reader, packet, count);
      break;
    case PM4_VIZ_QUERY:
      result = ExecutePacketType3_VIZ_QUERY(reader, packet, count);
      break;

    case PM4_SET_BIN_MASK_LO: {
      uint32_t value = reader->ReadAndSwap<uint32_t>();
      bin_mask_ = (bin_mask_ & 0xFFFFFFFF00000000ull) | value;
      result = true;
    } break;
    case PM4_SET_BIN_MASK_HI: {
      uint32_t value = reader->ReadAndSwap<uint32_t>();
      bin_mask_ = (bin_mask_ & 0xFFFFFFFFull) | (static_cast<uint64_t>(value) << 32);
      result = true;
    } break;
    case PM4_SET_BIN_SELECT_LO: {
      uint32_t value = reader->ReadAndSwap<uint32_t>();
      bin_select_ = (bin_select_ & 0xFFFFFFFF00000000ull) | value;
      result = true;
    } break;
    case PM4_SET_BIN_SELECT_HI: {
      uint32_t value = reader->ReadAndSwap<uint32_t>();
      bin_select_ = (bin_select_ & 0xFFFFFFFFull) | (static_cast<uint64_t>(value) << 32);
      result = true;
    } break;
    case PM4_SET_BIN_MASK: {
      assert_true(count == 2);
      uint64_t val_hi = reader->ReadAndSwap<uint32_t>();
      uint64_t val_lo = reader->ReadAndSwap<uint32_t>();
      bin_mask_ = (val_hi << 32) | val_lo;
      result = true;
    } break;
    case PM4_SET_BIN_SELECT: {
      assert_true(count == 2);
      uint64_t val_hi = reader->ReadAndSwap<uint32_t>();
      uint64_t val_lo = reader->ReadAndSwap<uint32_t>();
      bin_select_ = (val_hi << 32) | val_lo;
      result = true;
    } break;
    case PM4_CONTEXT_UPDATE: {
      assert_true(count == 1);
      uint32_t value = reader->ReadAndSwap<uint32_t>();
      REXGPU_INFO("GPU context update = {:08X}", value);
      assert_true(value == 0);
      result = true;
      break;
    }
    case PM4_WAIT_IB_PFD_COMPLETE: {
      reader->AdvanceRead(count * sizeof(uint32_t));
      result = true;
      break;
    }
    case PM4_WAIT_FOR_IDLE: {
      assert_true(count == 1);
      uint32_t value = reader->ReadAndSwap<uint32_t>();
      REXGPU_INFO("GPU wait for idle = {:08X}", value);
      result = true;
      break;
    }

    default:
      REXGPU_INFO("Unimplemented GPU OPCODE: 0x{:02X}\t\tCOUNT: {}\n", opcode, count);
      assert_always();
      reader->AdvanceRead(count * sizeof(uint32_t));
      break;
  }

  assert_true(reader->read_offset() ==
              (data_start_offset + (count * sizeof(uint32_t))) % reader->capacity());
  return result;
}

bool CommandProcessor::ExecutePacketType3_ME_INIT(memory::RingBuffer* reader, uint32_t packet,
                                                  uint32_t count) {
  me_bin_.clear();
  for (uint32_t i = 0; i < count; i++) {
    me_bin_.push_back(reader->ReadAndSwap<uint32_t>());
  }

  return true;
}

bool CommandProcessor::ExecutePacketType3_NOP(memory::RingBuffer* reader, uint32_t packet,
                                              uint32_t count) {
  reader->AdvanceRead(count * sizeof(uint32_t));
  return true;
}

bool CommandProcessor::ExecutePacketType3_INTERRUPT(memory::RingBuffer* reader, uint32_t packet,
                                                    uint32_t count) {
  SCOPE_profile_cpu_f("gpu");

  uint32_t cpu_mask = reader->ReadAndSwap<uint32_t>();
  for (int n = 0; n < 6; n++) {
    if (cpu_mask & (1 << n)) {
      if (graphics_system_) {
        graphics_system_->DispatchInterruptCallback(1, n);
      }
    }
  }
  return true;
}

bool CommandProcessor::ExecutePacketType3_XE_SWAP(memory::RingBuffer* reader, uint32_t packet,
                                                  uint32_t count) {
  SCOPE_profile_cpu_f("gpu");

#ifdef REXGLUE_ENABLE_PERF_COUNTERS
  {
    static uint64_t last_frame_tick = 0;
    uint64_t now = rex::chrono::Clock::QueryHostTickCount();
    if (last_frame_tick) {
      uint64_t freq = rex::chrono::Clock::QueryHostTickFrequency();
      int64_t dt_us = static_cast<int64_t>((now - last_frame_tick) * 1000000 / freq);
      PROFILE_FRAME_TIME_US(dt_us);
      PROFILE_FPS(freq / (now - last_frame_tick));
    }
    last_frame_tick = now;
  }
#endif
  rex::perf::Profiler::Flip();

  if (int32_t interval = REXCVAR_GET(frame_stats_interval); interval > 0) {
    uint64_t now = rex::chrono::Clock::QueryHostTickCount();
    if (frame_stats_last_swap_tick_) {
      uint64_t freq = rex::chrono::Clock::QueryHostTickFrequency();
      const double frame_ms = double(now - frame_stats_last_swap_tick_) * 1000.0 / double(freq);
      frame_stats_.Add(frame_ms);

      if (frame_ms > 50.0) {
        const double idle_ms = double(frame_stats_idle_ticks_) * 1000.0 / double(freq);
        const double wait_reg_ms = double(frame_stats_wait_reg_ticks_) * 1000.0 / double(freq);
        REXGPU_INFO(
            "Long frame: {:.1f} ms; waiting for guest commands {:.1f} ms, in WAIT_REG_MEM "
            "{:.1f} ms, processing {:.1f} ms{}",
            frame_ms, idle_ms, wait_reg_ms, std::max(0.0, frame_ms - idle_ms - wait_reg_ms),
            TakeFrameTimingDetail());
      } else {
        TakeFrameTimingDetail();
      }
      if (frame_stats_.window_seconds() >= double(interval)) {
        REXGPU_INFO("Frame pacing: {}", FrameStats::Format(frame_stats_.Take()));
      }
    }
    frame_stats_last_swap_tick_ = now;
    frame_stats_idle_ticks_ = 0;
    frame_stats_wait_reg_ticks_ = 0;
  }

  uint32_t magic = reader->ReadAndSwap<memory::fourcc_t>();
  assert_true(magic == kSwapSignature);

  uint32_t frontbuffer_ptr = reader->ReadAndSwap<uint32_t>();
  uint32_t frontbuffer_width = reader->ReadAndSwap<uint32_t>();
  uint32_t frontbuffer_height = reader->ReadAndSwap<uint32_t>();
  reader->AdvanceRead((count - 4) * sizeof(uint32_t));

  IssueSwap(frontbuffer_ptr, frontbuffer_width, frontbuffer_height);

  ++counter_;
  return true;
}

bool CommandProcessor::ExecutePacketType3_INDIRECT_BUFFER(memory::RingBuffer* reader,
                                                          uint32_t packet, uint32_t count) {
  uint32_t list_ptr = CpuToGpu(reader->ReadAndSwap<uint32_t>());
  uint32_t list_length = reader->ReadAndSwap<uint32_t>();
  assert_zero(list_length & ~0xFFFFF);
  list_length &= 0xFFFFF;
  ExecuteIndirectBuffer(GpuToCpu(list_ptr), list_length);
  return true;
}

bool CommandProcessor::ExecutePacketType3_WAIT_REG_MEM(memory::RingBuffer* reader, uint32_t packet,
                                                       uint32_t count) {
  SCOPE_profile_cpu_f("gpu");

  uint32_t wait_info = reader->ReadAndSwap<uint32_t>();
  uint32_t poll_reg_addr = reader->ReadAndSwap<uint32_t>();
  uint32_t ref = reader->ReadAndSwap<uint32_t>();
  uint32_t mask = reader->ReadAndSwap<uint32_t>();
  uint32_t wait = reader->ReadAndSwap<uint32_t>();

  bool is_memory = (wait_info & 0x10) != 0;

  const uint64_t wait_start = rex::chrono::Clock::QueryHostTickCount();
  bool matched = false;
  do {
    uint32_t value = 0;
    if (is_memory) {
      value =
          *reinterpret_cast<uint32_t*>(memory_->TranslatePhysical(poll_reg_addr & ~uint32_t(0x3)));
      value = xenos::GpuSwap(value, static_cast<xenos::Endian>(poll_reg_addr & 0x3));
    } else {
      value = ReadRegisterValue(poll_reg_addr);
      if (poll_reg_addr == XE_GPU_REG_COHER_STATUS_HOST) {
        MakeCoherent();
        value = ReadRegisterValue(poll_reg_addr);
      }
    }
    switch (wait_info & 0x7) {
      case 0x0:
        matched = false;
        break;
      case 0x1:
        matched = (value & mask) < ref;
        break;
      case 0x2:
        matched = (value & mask) <= ref;
        break;
      case 0x3:
        matched = (value & mask) == ref;
        break;
      case 0x4:
        matched = (value & mask) != ref;
        break;
      case 0x5:
        matched = (value & mask) >= ref;
        break;
      case 0x6:
        matched = (value & mask) > ref;
        break;
      case 0x7:
        matched = true;
        break;
    }
    if (!matched) {
      if (wait >= 0x100) {
        PrepareForWait();
        if (!REXCVAR_GET(vsync)) {
          rex::thread::MaybeYield();
        } else {
          rex::thread::Sleep(std::chrono::milliseconds(wait / 0x100));
        }
        rex::thread::SyncMemory();
        ReturnFromWait();

        if (!worker_running_) {
          return false;
        }
      } else {
        rex::thread::MaybeYield();
      }
    }
  } while (!matched);
  frame_stats_wait_reg_ticks_ += rex::chrono::Clock::QueryHostTickCount() - wait_start;

  return true;
}

bool CommandProcessor::ExecutePacketType3_REG_RMW(memory::RingBuffer* reader, uint32_t packet,
                                                  uint32_t count) {
  uint32_t rmw_info = reader->ReadAndSwap<uint32_t>();
  uint32_t and_mask = reader->ReadAndSwap<uint32_t>();
  uint32_t or_mask = reader->ReadAndSwap<uint32_t>();
  uint32_t value = register_file_->values[rmw_info & 0x1FFF];
  if ((rmw_info >> 31) & 0x1) {
    value &= register_file_->values[and_mask & 0x1FFF];
  } else {
    value &= and_mask;
  }
  if ((rmw_info >> 30) & 0x1) {
    value |= register_file_->values[or_mask & 0x1FFF];
  } else {
    value |= or_mask;
  }
  WriteRegister(rmw_info & 0x1FFF, value);
  return true;
}

bool CommandProcessor::ExecutePacketType3_REG_TO_MEM(memory::RingBuffer* reader, uint32_t packet,
                                                     uint32_t count) {
  uint32_t reg_addr = reader->ReadAndSwap<uint32_t>();
  uint32_t mem_addr = reader->ReadAndSwap<uint32_t>();

  uint32_t reg_val = ReadRegisterValue(reg_addr);

  auto endianness = static_cast<xenos::Endian>(mem_addr & 0x3);
  mem_addr &= ~0x3;
  reg_val = GpuSwap(reg_val, endianness);
  memory::store(memory_->TranslatePhysical(mem_addr), reg_val);

  return true;
}

bool CommandProcessor::ExecutePacketType3_MEM_WRITE(memory::RingBuffer* reader, uint32_t packet,
                                                    uint32_t count) {
  uint32_t write_addr = reader->ReadAndSwap<uint32_t>();
  for (uint32_t i = 0; i < count - 1; i++) {
    uint32_t write_data = reader->ReadAndSwap<uint32_t>();

    auto endianness = static_cast<xenos::Endian>(write_addr & 0x3);
    auto addr = write_addr & ~0x3;
    write_data = GpuSwap(write_data, endianness);
    memory::store(memory_->TranslatePhysical(addr), write_data);
    write_addr += 4;
  }

  return true;
}

bool CommandProcessor::ExecutePacketType3_COND_WRITE(memory::RingBuffer* reader, uint32_t packet,
                                                     uint32_t count) {
  uint32_t wait_info = reader->ReadAndSwap<uint32_t>();
  uint32_t poll_reg_addr = reader->ReadAndSwap<uint32_t>();
  uint32_t ref = reader->ReadAndSwap<uint32_t>();
  uint32_t mask = reader->ReadAndSwap<uint32_t>();
  uint32_t write_reg_addr = reader->ReadAndSwap<uint32_t>();
  uint32_t write_data = reader->ReadAndSwap<uint32_t>();
  uint32_t value;
  if (wait_info & 0x10) {
    auto endianness = static_cast<xenos::Endian>(poll_reg_addr & 0x3);
    poll_reg_addr &= ~0x3;
    value = memory::load<uint32_t>(memory_->TranslatePhysical(poll_reg_addr));
    value = GpuSwap(value, endianness);
  } else {
    value = ReadRegisterValue(poll_reg_addr);
  }
  bool matched = false;
  switch (wait_info & 0x7) {
    case 0x0:
      matched = false;
      break;
    case 0x1:
      matched = (value & mask) < ref;
      break;
    case 0x2:
      matched = (value & mask) <= ref;
      break;
    case 0x3:
      matched = (value & mask) == ref;
      break;
    case 0x4:
      matched = (value & mask) != ref;
      break;
    case 0x5:
      matched = (value & mask) >= ref;
      break;
    case 0x6:
      matched = (value & mask) > ref;
      break;
    case 0x7:
      matched = true;
      break;
  }
  if (matched) {
    if (wait_info & 0x100) {
      auto endianness = static_cast<xenos::Endian>(write_reg_addr & 0x3);
      write_reg_addr &= ~0x3;
      write_data = GpuSwap(write_data, endianness);
      memory::store(memory_->TranslatePhysical(write_reg_addr), write_data);
    } else {
      WriteRegister(write_reg_addr, write_data);
    }
  }
  return true;
}

bool CommandProcessor::ExecutePacketType3_EVENT_WRITE(memory::RingBuffer* reader, uint32_t packet,
                                                      uint32_t count) {
  uint32_t initiator = reader->ReadAndSwap<uint32_t>();

  WriteRegister(XE_GPU_REG_VGT_EVENT_INITIATOR, initiator & 0x3F);
  if (count == 1) {
  } else {
    assert_always();
    reader->AdvanceRead((count - 1) * sizeof(uint32_t));
  }
  return true;
}

bool CommandProcessor::ExecutePacketType3_EVENT_WRITE_SHD(memory::RingBuffer* reader,
                                                          uint32_t packet, uint32_t count) {
  uint32_t initiator = reader->ReadAndSwap<uint32_t>();
  uint32_t address = reader->ReadAndSwap<uint32_t>();
  uint32_t value = reader->ReadAndSwap<uint32_t>();

  WriteRegister(XE_GPU_REG_VGT_EVENT_INITIATOR, initiator & 0x3F);
  uint32_t data_value;
  if ((initiator >> 31) & 0x1) {
    data_value = counter_;
  } else {
    data_value = value;
  }
  auto endianness = static_cast<xenos::Endian>(address & 0x3);
  address &= ~0x3;
  data_value = GpuSwap(data_value, endianness);
  memory::store(memory_->TranslatePhysical(address), data_value);
  return true;
}

bool CommandProcessor::ExecutePacketType3_EVENT_WRITE_EXT(memory::RingBuffer* reader,
                                                          uint32_t packet, uint32_t count) {
  uint32_t initiator = reader->ReadAndSwap<uint32_t>();
  uint32_t address = reader->ReadAndSwap<uint32_t>();

  WriteRegister(XE_GPU_REG_VGT_EVENT_INITIATOR, initiator & 0x3F);
  auto endianness = static_cast<xenos::Endian>(address & 0x3);
  address &= ~0x3;

  uint16_t extents[] = {
      0 >> 3, xenos::kTexture2DCubeMaxWidthHeight >> 3,
      0 >> 3, xenos::kTexture2DCubeMaxWidthHeight >> 3,
      0,      1,
  };
  assert_true(endianness == xenos::Endian::k8in16);
  memory::copy_and_swap_16_unaligned(memory_->TranslatePhysical(address), extents,
                                     rex::countof(extents));
  return true;
}

bool CommandProcessor::ExecutePacketType3_EVENT_WRITE_ZPD(memory::RingBuffer* reader,
                                                          uint32_t packet, uint32_t count) {
  assert_true(count == 1);
  uint32_t initiator = reader->ReadAndSwap<uint32_t>();

  WriteRegister(XE_GPU_REG_VGT_EVENT_INITIATOR, initiator & 0x3F);

  uint32_t report_address = register_file_->values[XE_GPU_REG_RB_SAMPLE_COUNT_ADDR];

  if (!report_address || !memory_->TranslatePhysical(report_address)) {
    return true;
  }

  if (zpd_mode_ != ZPDMode::kFake && !zpd_force_fake_fallback_) {
    QueueZPDReport(report_address);
    return true;
  }

  zpd_speculative_sample_counter_ +=
      XenosZPDReport::FromNativeQuery(uint32_t(REXCVAR_GET(query_occlusion_fake_sample_count)));
  zpd_sample_counter_ = zpd_speculative_sample_counter_;
  WriteZPDReport(report_address, zpd_sample_counter_);
  return true;
}

bool CommandProcessor::ExecutePacketType3Draw(memory::RingBuffer* reader, uint32_t packet,
                                              const char* opcode_name, uint32_t viz_query_condition,
                                              uint32_t count_remaining) {
  assert_not_zero(count_remaining);
  if (!count_remaining) {
    REXGPU_ERROR("{}: Packet too small, can't read VGT_DRAW_INITIATOR", opcode_name);
    return false;
  }
  reg::VGT_DRAW_INITIATOR vgt_draw_initiator;
  vgt_draw_initiator.value = reader->ReadAndSwap<uint32_t>();
  --count_remaining;
  WriteRegister(XE_GPU_REG_VGT_DRAW_INITIATOR, vgt_draw_initiator.value);

  bool draw_succeeded = true;

  bool is_indexed = false;
  IndexBufferInfo index_buffer_info;
  switch (vgt_draw_initiator.source_select) {
    case xenos::SourceSelect::kDMA: {
      is_indexed = true;

      assert_not_zero(count_remaining);
      if (!count_remaining) {
        REXGPU_ERROR("{}: Packet too small, can't read VGT_DMA_BASE", opcode_name);
        return false;
      }
      uint32_t vgt_dma_base = reader->ReadAndSwap<uint32_t>();
      --count_remaining;
      WriteRegister(XE_GPU_REG_VGT_DMA_BASE, vgt_dma_base);
      reg::VGT_DMA_SIZE vgt_dma_size;
      assert_not_zero(count_remaining);
      if (!count_remaining) {
        REXGPU_ERROR("{}: Packet too small, can't read VGT_DMA_SIZE", opcode_name);
        return false;
      }
      vgt_dma_size.value = reader->ReadAndSwap<uint32_t>();
      --count_remaining;
      WriteRegister(XE_GPU_REG_VGT_DMA_SIZE, vgt_dma_size.value);

      uint32_t index_size_bytes = vgt_draw_initiator.index_size == xenos::IndexFormat::kInt16
                                      ? sizeof(uint16_t)
                                      : sizeof(uint32_t);

      index_buffer_info.guest_base = vgt_dma_base & ~(index_size_bytes - 1);
      index_buffer_info.endianness = vgt_dma_size.swap_mode;
      index_buffer_info.format = vgt_draw_initiator.index_size;
      index_buffer_info.length = vgt_dma_size.num_words * index_size_bytes;
      index_buffer_info.count = vgt_draw_initiator.num_indices;
    } break;
    case xenos::SourceSelect::kImmediate: {
      REXGPU_ERROR(
          "{}: Using immediate vertex indices, which are not supported yet. "
          "Report the game to Xenia developers!",
          opcode_name, uint32_t(vgt_draw_initiator.source_select));
      draw_succeeded = false;
      assert_always();
    } break;
    case xenos::SourceSelect::kAutoIndex: {
      index_buffer_info.guest_base = 0;
      index_buffer_info.length = 0;
    } break;
    default: {
      draw_succeeded = false;
      assert_unhandled_case(vgt_draw_initiator.source_select);
    } break;
  }

  reader->AdvanceRead(count_remaining * sizeof(uint32_t));

  if (draw_succeeded) {
    if (PrepareVIZDraw(viz_query_condition)) {
      bool major_mode_explicit =
          xenos::IsMajorModeExplicit(vgt_draw_initiator.major_mode, vgt_draw_initiator.prim_type);
      draw_succeeded = IssueDraw(vgt_draw_initiator.prim_type, vgt_draw_initiator.num_indices,
                                 is_indexed ? &index_buffer_info : nullptr, major_mode_explicit);
      viz_draw_predicate_ = {};
      if (!draw_succeeded) {
        auto vgt_output_path_cntl = register_file_->Get<reg::VGT_OUTPUT_PATH_CNTL>();
        auto vgt_hos_cntl = register_file_->Get<reg::VGT_HOS_CNTL>();
        auto rb_modecontrol = register_file_->Get<reg::RB_MODECONTROL>();
        REXGPU_ERROR(
            "{}({}, {}, {}): Failed in backend "
            "(major_mode={}, explicit_major={}, path_select={}, tess_mode={}, edram_mode={})",
            opcode_name, static_cast<uint32_t>(vgt_draw_initiator.num_indices),
            uint32_t(vgt_draw_initiator.prim_type), uint32_t(vgt_draw_initiator.source_select),
            uint32_t(vgt_draw_initiator.major_mode), uint32_t(major_mode_explicit),
            uint32_t(vgt_output_path_cntl.path_select), uint32_t(vgt_hos_cntl.tess_mode),
            uint32_t(rb_modecontrol.edram_mode));
      }
    }
  }

  if (!draw_succeeded) {
    OnVIZSurveyDraw(false);
  }

  return true;
}

bool CommandProcessor::ExecutePacketType3_DRAW_INDX(memory::RingBuffer* reader, uint32_t packet,
                                                    uint32_t count) {
  uint32_t count_remaining = count;
  assert_not_zero(count_remaining);
  if (!count_remaining) {
    REXGPU_ERROR("PM4_DRAW_INDX: Packet too small, can't read the viz query token");
    return false;
  }
  uint32_t viz_query_condition = reader->ReadAndSwap<uint32_t>();
  --count_remaining;
  return ExecutePacketType3Draw(reader, packet, "PM4_DRAW_INDX", viz_query_condition,
                                count_remaining);
}

bool CommandProcessor::ExecutePacketType3_DRAW_INDX_2(memory::RingBuffer* reader, uint32_t packet,
                                                      uint32_t count) {
  return ExecutePacketType3Draw(reader, packet, "PM4_DRAW_INDX_2", 0, count);
}

bool CommandProcessor::ExecutePacketType3_SET_CONSTANT(memory::RingBuffer* reader, uint32_t packet,
                                                       uint32_t count) {
  uint32_t offset_type = reader->ReadAndSwap<uint32_t>();
  uint32_t index = offset_type & 0x7FF;
  uint32_t type = (offset_type >> 16) & 0xFF;
  uint32_t count_registers = count - 1;
  switch (type) {
    case 0:
      WriteALURangeFromRing(reader, index, count_registers);
      break;
    case 1:
      WriteFetchRangeFromRing(reader, index, count_registers);
      break;
    case 2:
      WriteBoolRangeFromRing(reader, index, count_registers);
      break;
    case 3:
      WriteLoopRangeFromRing(reader, index, count_registers);
      break;
    case 4:
      WriteREGISTERSRangeFromRing(reader, index, count_registers);
      break;
    default:
      assert_always();
      reader->AdvanceRead((count - 1) * sizeof(uint32_t));
      return true;
  }
  return true;
}

bool CommandProcessor::ExecutePacketType3_SET_CONSTANT2(memory::RingBuffer* reader, uint32_t packet,
                                                        uint32_t count) {
  uint32_t offset_type = reader->ReadAndSwap<uint32_t>();
  uint32_t index = offset_type & 0xFFFF;
  WriteRegisterRangeFromRing(reader, index, count - 1);
  return true;
}

bool CommandProcessor::ExecutePacketType3_LOAD_ALU_CONSTANT(memory::RingBuffer* reader,
                                                            uint32_t packet, uint32_t count) {
  uint32_t address = reader->ReadAndSwap<uint32_t>();
  address &= 0x3FFFFFFF;
  uint32_t offset_type = reader->ReadAndSwap<uint32_t>();
  uint32_t index = offset_type & 0x7FF;
  uint32_t size_dwords = reader->ReadAndSwap<uint32_t>();
  size_dwords &= 0xFFF;
  uint32_t type = (offset_type >> 16) & 0xFF;
  uint32_t* xlat_address = memory_->TranslatePhysical<uint32_t*>(address);
  switch (type) {
    case 0:
      WriteALURangeFromMem(index, xlat_address, size_dwords);
      break;
    case 1:
      WriteFetchRangeFromMem(index, xlat_address, size_dwords);
      break;
    case 2:
      WriteBoolRangeFromMem(index, xlat_address, size_dwords);
      break;
    case 3:
      WriteLoopRangeFromMem(index, xlat_address, size_dwords);
      break;
    case 4:
      WriteREGISTERSRangeFromMem(index, xlat_address, size_dwords);
      break;
    default:
      assert_always();
      return true;
  }
  return true;
}

bool CommandProcessor::ExecutePacketType3_SET_SHADER_CONSTANTS(memory::RingBuffer* reader,
                                                               uint32_t packet, uint32_t count) {
  uint32_t offset_type = reader->ReadAndSwap<uint32_t>();
  uint32_t index = offset_type & 0xFFFF;
  WriteRegisterRangeFromRing(reader, index, count - 1);
  return true;
}

bool CommandProcessor::ExecutePacketType3_IM_LOAD(memory::RingBuffer* reader, uint32_t packet,
                                                  uint32_t count) {
  SCOPE_profile_cpu_f("gpu");

  uint32_t addr_type = reader->ReadAndSwap<uint32_t>();
  auto shader_type = static_cast<xenos::ShaderType>(addr_type & 0x3);
  uint32_t addr = addr_type & ~0x3;
  uint32_t start_size = reader->ReadAndSwap<uint32_t>();
  uint32_t start = start_size >> 16;
  uint32_t size_dwords = start_size & 0xFFFF;
  assert_true(start == 0);

  auto shader =
      LoadShader(shader_type, addr, memory_->TranslatePhysical<uint32_t*>(addr), size_dwords);
  switch (shader_type) {
    case xenos::ShaderType::kVertex:
      active_vertex_shader_ = shader;
      break;
    case xenos::ShaderType::kPixel:
      active_pixel_shader_ = shader;
      break;
    default:
      assert_unhandled_case(shader_type);
      return false;
  }
  return true;
}

bool CommandProcessor::ExecutePacketType3_IM_LOAD_IMMEDIATE(memory::RingBuffer* reader,
                                                            uint32_t packet, uint32_t count) {
  SCOPE_profile_cpu_f("gpu");

  uint32_t dword0 = reader->ReadAndSwap<uint32_t>();
  uint32_t dword1 = reader->ReadAndSwap<uint32_t>();
  auto shader_type = static_cast<xenos::ShaderType>(dword0);
  uint32_t start_size = dword1;
  uint32_t start = start_size >> 16;
  uint32_t size_dwords = start_size & 0xFFFF;
  assert_true(start == 0);
  assert_true(reader->read_count() >= size_dwords * 4);
  assert_true(count - 2 >= size_dwords);
  auto shader = LoadShader(shader_type, uint32_t(reader->read_ptr()),
                           reinterpret_cast<uint32_t*>(reader->read_ptr()), size_dwords);
  switch (shader_type) {
    case xenos::ShaderType::kVertex:
      active_vertex_shader_ = shader;
      break;
    case xenos::ShaderType::kPixel:
      active_pixel_shader_ = shader;
      break;
    default:
      assert_unhandled_case(shader_type);
      return false;
  }
  reader->AdvanceRead(size_dwords * sizeof(uint32_t));
  return true;
}

bool CommandProcessor::ExecutePacketType3_INVALIDATE_STATE(memory::RingBuffer* reader,
                                                           uint32_t packet, uint32_t count) {
  reader->ReadAndSwap<uint32_t>();

  return true;
}

bool CommandProcessor::ExecutePacketType3_VIZ_QUERY(memory::RingBuffer* reader, uint32_t packet,
                                                    uint32_t count) {
  assert_true(count == 1);

  uint32_t dword0 = reader->ReadAndSwap<uint32_t>();

  uint32_t id = dword0 & 0x3F;
  uint32_t end = dword0 & 0x100;
  if (!end) {
    WriteRegister(XE_GPU_REG_VGT_EVENT_INITIATOR, VIZQUERY_START);
    if (REXCVAR_GET(occlusion_query_viz)) {
      BeginVIZQuery(id);
    }
  } else {
    WriteRegister(XE_GPU_REG_VGT_EVENT_INITIATOR, VIZQUERY_END);
    if (REXCVAR_GET(occlusion_query_viz)) {
      EndVIZQuery(id);
    }

    if (id < 32) {
      register_file_->values[XE_GPU_REG_PA_SC_VIZ_QUERY_STATUS_0] |= uint32_t(1) << id;
    } else {
      register_file_->values[XE_GPU_REG_PA_SC_VIZ_QUERY_STATUS_1] |= uint32_t(1) << (id - 32);
    }
  }

  return true;
}

void CommandProcessor::BeginVIZQuery(uint32_t id) {
  if (zpd_active_segment_.viz.generation != kInvalidVIZGeneration) {
    CloseQuerySegment();
    zpd_active_segment_.viz = {};
  }
  VIZQuery& query = viz_queries_[id];
  const uint64_t generation = query.generation + 1;
  query = {};
  query.generation = generation;
  query.resolved = false;
  query.active = true;
}

void CommandProcessor::EndVIZQuery(uint32_t id) {
  VIZQuery& query = viz_queries_[id];
  if (zpd_active_segment_.viz.id == id && zpd_active_segment_.viz.generation == query.generation) {
    CloseQuerySegment();
    zpd_active_segment_.viz = {};
  }
  query.active = false;
  if (query.resolved) {
    return;
  }
  if (!query.surveyed) {
    query.resolved = true;
    query.visible = false;
  } else if (query.fallback || !query.pending_segments) {
    query.resolved = true;
    query.visible = query.fallback || query.accumulated_visible;
  }
}

void CommandProcessor::OnVIZSurveyDraw(bool measured) {
  const reg::PA_SC_VIZ_QUERY viz_query = register_file_->Get<reg::PA_SC_VIZ_QUERY>();
  if (!viz_query.viz_query_ena) {
    return;
  }
  VIZQuery& query = viz_queries_[viz_query.viz_query_id];
  if (!query.active) {
    return;
  }
  query.surveyed = true;
  if (measured && zpd_active_segment_.segment_active &&
      zpd_active_segment_.viz.id == viz_query.viz_query_id &&
      zpd_active_segment_.viz.generation == query.generation) {
    return;
  }
  query.fallback = true;
}

void CommandProcessor::OnVIZQueryResolved(uint32_t id, uint64_t generation, bool visible) {
  if (viz_pending_resolves_) {
    --viz_pending_resolves_;
  }
  VIZQuery& query = viz_queries_[id];
  if (query.generation != generation) {
    return;
  }
  if (query.pending_segments) {
    --query.pending_segments;
  }
  query.accumulated_visible |= visible;

  if (!query.resolved && !query.active && !query.pending_segments) {
    query.resolved = true;
    query.visible = query.fallback || query.accumulated_visible;
  }
}

bool CommandProcessor::PrepareVIZDraw(uint32_t token) {
  viz_draw_predicate_ = {};
  if (!(token & 0x100)) {
    return true;
  }
  const uint32_t id = token & 0x3F;
  VIZQuery& query = viz_queries_[id];
  if (!query.resolved) {
    PumpQueryResolves();
  }
  if (!query.resolved && query.pending_segments) {
    if (query.predicate_armed && !query.fallback &&
        !(zpd_active_segment_.viz.generation != kInvalidVIZGeneration &&
          zpd_active_segment_.viz.id == id)) {
      viz_draw_predicate_.id = id;
      viz_draw_predicate_.generation = query.generation;

    } else if (!query.active) {
      AwaitVIZQueryResolve(query.last_segment_end_submission);
    }
  }
  const bool draw =
      viz_draw_predicate_.generation != kInvalidVIZGeneration || !query.resolved || query.visible;
  if (draw && viz_draw_predicate_.generation == kInvalidVIZGeneration) {
    return true;
  }

  const bool memexport_used_vertex =
      active_vertex_shader_ && (!active_vertex_shader_->is_ucode_analyzed() ||
                                active_vertex_shader_->memexport_eM_written());
  const bool memexport_used_pixel =
      active_pixel_shader_ &&
      (!active_pixel_shader_->is_ucode_analyzed() || active_pixel_shader_->memexport_eM_written());
  if (!memexport_used_vertex && !memexport_used_pixel &&
      register_file_->Get<reg::RB_MODECONTROL>().edram_mode != xenos::EdramMode::kCopy) {
    return draw;
  }
  viz_draw_predicate_ = {};
  return true;
}

void CommandProcessor::QueueZPDReport(uint32_t report_address) {
  if (zpd_active_segment_.report) {
    CloseQuerySegment();
  }

  ZPDReport& report = zpd_current_report_;
  report.address = report_address;
  if (zpd_mode_ == ZPDMode::kStrict) {
    const uint32_t kPendingSentinel = rex::byte_swap(0xFFFFFEEDu);
    const auto* guest =
        memory_->TranslatePhysical<xenos::xe_gpu_depth_sample_counts*>(report_address);
    report.awaited = guest->ZPass_A == kPendingSentinel || guest->ZFail_A == kPendingSentinel;
  } else {
    auto cache_it = fast_zpd_report_cached_deltas_.find(report_address);
    if (cache_it != fast_zpd_report_cached_deltas_.end() &&
        (cache_it->second.z_pass || zpd_mode_ == ZPDMode::kFastAlt)) {
      report.speculative_delta = cache_it->second;
    } else {
      report.speculative_delta = XenosZPDReport::FromNativeQuery(1);
    }
    zpd_speculative_sample_counter_ += report.speculative_delta;
    report.speculative_value = zpd_speculative_sample_counter_;
    report.speculative = true;
    WriteZPDReport(report_address, report.speculative_value);
  }
  zpd_awaited_report_count_ += report.awaited;
  zpd_reports_.push_back(report);

  zpd_current_report_ = {};
  zpd_current_report_.handle = zpd_next_report_handle_++;
  zpd_active_segment_.segment_pending_begin = true;
}

void CommandProcessor::OpenQuerySegment(bool can_close_submission) {
  ActiveZPDSegment& segment = zpd_active_segment_;
  if (segment.segment_active || query_segment_opening_ || !CanOpenZPDQuery()) {
    return;
  }
  const bool report = zpd_current_report_.handle != kInvalidReportHandle &&
                      segment.segment_pending_begin && !segment.survey;
  const bool viz = segment.viz.generation != kInvalidVIZGeneration;
  if (!report && !viz) {
    return;
  }

  EnsureZPDQueryResources();
  if (!IsZPDQueryPoolReady()) {
    if (viz) {
      viz_queries_[segment.viz.id].fallback = true;
    }
    if (report) {
      zpd_force_fake_fallback_ = true;
      zpd_current_report_ = {};
      segment = {};
    } else {
      segment.viz = {};
    }
    return;
  }

  PumpQueryResolves();

  segment.report = report;
  query_segment_opening_ = true;
  QueryOpenResult result = OpenZPDQuery(can_close_submission);
  query_segment_opening_ = false;
  if (result == QueryOpenResult::kPoolExhausted && zpd_mode_ != ZPDMode::kStrict) {
    if (report) {
      zpd_current_report_.delta.z_pass = std::max<uint64_t>(zpd_current_report_.delta.z_pass, 1);
      segment.segment_pending_begin = false;
    }
    if (viz) {
      viz_queries_[segment.viz.id].fallback = true;
    }
    segment.report = false;
    segment.viz = {};
    return;
  }
  if (result != QueryOpenResult::kOpened) {
    segment.report = false;

    if (result != QueryOpenResult::kDeferred && viz) {
      viz_queries_[segment.viz.id].fallback = true;
      segment.viz = {};
    }
    return;
  }
  segment.segment_active = true;
  if (report) {
    segment.segment_pending_begin = false;
  }
}

void CommandProcessor::CloseQuerySegment() {
  ActiveZPDSegment& segment = zpd_active_segment_;
  if (!segment.segment_active) {
    return;
  }
  uint64_t submission = 0;
  const bool closed = CloseZPDQuery(
      segment.report ? zpd_current_report_.handle : kInvalidReportHandle, segment.viz, submission);
  if (segment.report && closed) {
    zpd_current_report_.pending_segments++;
    zpd_current_report_.last_segment_end_submission = submission;
  }
  if (segment.viz.generation != kInvalidVIZGeneration) {
    VIZQuery& query = viz_queries_[segment.viz.id];
    if (closed) {
      ++query.pending_segments;
      query.last_segment_end_submission = submission;
      ++viz_pending_resolves_;
    } else {
      query.fallback = true;
    }
  }

  const bool pending_begin = segment.report || segment.segment_pending_begin;
  segment = {};
  segment.segment_pending_begin = pending_begin;
}

void CommandProcessor::UpdateZPDSegment(uint32_t scale_area, bool count_total, bool survey) {
  ActiveZPDSegment& segment = zpd_active_segment_;
  const reg::PA_SC_VIZ_QUERY viz_query = register_file_->Get<reg::PA_SC_VIZ_QUERY>();
  const VIZQuery& viz_active = viz_queries_[viz_query.viz_query_id];
  const bool viz = REXCVAR_GET(occlusion_query_viz) && viz_query.viz_query_ena && viz_active.active;

  const bool report =
      zpd_current_report_.handle != kInvalidReportHandle && !survey && segment.report_measuring();
  if (!segment.report && !report && !viz) {
    return;
  }
  count_total &= report;

  if (segment.segment_active &&
      ((segment.report && ((segment.scale_area && segment.scale_area != scale_area) ||
                           segment.count_total != count_total)) ||
       segment.report != report ||
       (viz && !(segment.viz.id == viz_query.viz_query_id &&
                 segment.viz.generation == viz_active.generation)))) {
    CloseQuerySegment();
  }

  segment.scale_area = scale_area;
  segment.count_total = count_total;

  if (segment.segment_active) {
    return;
  }
  segment.survey = survey;
  segment.viz = {};
  if (viz) {
    segment.viz.id = viz_query.viz_query_id;
    segment.viz.generation = viz_active.generation;
  }
  OpenQuerySegment(false);
}

void CommandProcessor::OnZPDQueryResolved(ReportHandle report_handle,
                                          const XenosZPDReport& raw_counts, uint32_t scale_area) {
  ZPDReport* report = FindZPDReport(report_handle);
  if (!report) {
    return;
  }
  assert_true(report->pending_segments);
  --report->pending_segments;
  report->delta += raw_counts.Normalized(scale_area);
}

CommandProcessor::ZPDReport* CommandProcessor::FindZPDReport(ReportHandle report_handle) {
  if (report_handle == kInvalidReportHandle) {
    return nullptr;
  }
  if (zpd_current_report_.handle == report_handle) {
    return &zpd_current_report_;
  }
  if (!zpd_reports_.empty() && report_handle >= zpd_reports_.front().handle) {
    size_t index = size_t(report_handle - zpd_reports_.front().handle);
    if (index < zpd_reports_.size()) {
      assert_true(zpd_reports_[index].handle == report_handle);
      return &zpd_reports_[index];
    }
  }
  return nullptr;
}

void CommandProcessor::PrepareZPDForWait() {
  ReportHandle awaited_handle = kInvalidReportHandle;
  for (const ZPDReport& report : zpd_reports_) {
    if (report.awaited) {
      awaited_handle = report.handle;
      break;
    }
  }
  if (awaited_handle == kInvalidReportHandle) {
    return;
  }

  PollCompletedSubmission();
  PumpPendingRetire();

  ZPDReport* wait_report = FindZPDReport(awaited_handle);
  if (wait_report && !wait_report->pending_segments && !zpd_reports_.empty() &&
      zpd_reports_.front().pending_segments) {
    wait_report = &zpd_reports_.front();
  }
  if (!wait_report || !wait_report->pending_segments) {
    return;
  }
  if (AwaitQueryResolve(wait_report->handle, wait_report->last_segment_end_submission)) {
    PumpPendingRetire();
    return;
  }

  uint64_t now_ms = chrono::Clock::QueryHostUptimeMillis();
  if (!zpd_pending_retire_start_ms_) {
    zpd_pending_retire_start_ms_ = now_ms;
    return;
  }
  if (now_ms - zpd_pending_retire_start_ms_ < kStrictZPDRetireDeadlineMs) {
    return;
  }

  ZPDReport& front = zpd_reports_.front();

  front.delta.z_pass = std::max<uint64_t>(front.delta.z_pass, 1);
  front.pending_segments = 0;
  PumpPendingRetire();
}

void CommandProcessor::PumpPendingRetire() {
  bool rebase_needed = false;
  while (!zpd_reports_.empty()) {
    ZPDReport& front = zpd_reports_.front();
    if (front.pending_segments) {
      if (zpd_mode_ == ZPDMode::kStrict) {
        break;
      }

      uint64_t now_ms = chrono::Clock::QueryHostUptimeMillis();
      if (!zpd_pending_retire_start_ms_) {
        zpd_pending_retire_start_ms_ = now_ms;
        break;
      }
      if (now_ms - zpd_pending_retire_start_ms_ < kFastZPDRetireDeadlineMs) {
        break;
      }
      front.delta.z_pass = std::max<uint64_t>(front.delta.z_pass, 1);
      front.pending_segments = 0;
    }
    zpd_pending_retire_start_ms_ = 0;

    zpd_sample_counter_ += front.delta;
    if (front.speculative) {
      if (fast_zpd_report_cached_deltas_.size() >= kFastZPDCacheMaxEntries &&
          !fast_zpd_report_cached_deltas_.count(front.address)) {
        fast_zpd_report_cached_deltas_.clear();
      }
      fast_zpd_report_cached_deltas_[front.address] = front.delta;
    }
    if (!front.speculative) {
      WriteZPDReport(front.address, zpd_sample_counter_);
    } else if (front.speculative_value != zpd_sample_counter_) {
      WriteZPDReport(front.address, zpd_sample_counter_);
      rebase_needed = true;
    }
    if (front.awaited) {
      assert_true(zpd_awaited_report_count_);
      --zpd_awaited_report_count_;
    }
    zpd_reports_.pop_front();
  }

  if (rebase_needed) {
    XenosZPDReport running = zpd_sample_counter_;
    for (ZPDReport& report : zpd_reports_) {
      assert_true(report.speculative);
      running += report.speculative_delta;
      if (report.speculative_value != running) {
        WriteZPDReport(report.address, running);
        report.speculative_value = running;
      }
    }
    zpd_speculative_sample_counter_ = running;
  } else if (zpd_reports_.empty()) {
    zpd_speculative_sample_counter_ = zpd_sample_counter_;
  }
}

void CommandProcessor::WriteZPDReport(uint32_t report_address, const XenosZPDReport& value) {
  auto* guest = memory_->TranslatePhysical<xenos::xe_gpu_depth_sample_counts*>(report_address);
  if (guest) {
    value.WriteTo(guest);
  }
}

void CommandProcessor::ResetZPDState() {
  zpd_mode_ = GetZPDMode();
  zpd_active_segment_ = {};
  zpd_next_report_handle_ = 1;
  zpd_current_report_ = {};
  zpd_reports_.clear();
  zpd_awaited_report_count_ = 0;
  fast_zpd_report_cached_deltas_.clear();
  zpd_sample_counter_ = {};
  zpd_speculative_sample_counter_ = {};
  zpd_pending_retire_start_ms_ = 0;
  zpd_force_fake_fallback_ = false;
}

}
