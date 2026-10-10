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

#pragma once

#include <array>
#include <atomic>
#include <cstring>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include <rex/graphics/frame_stats.h>
#include <rex/graphics/register_file.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/xenos.h>
#include <rex/graphics/xenos_zpd_report.h>
#include <rex/memory.h>
#include <rex/memory/ring_buffer.h>
#include <rex/system/kernel_thread.h>
#include <rex/thread.h>
#include <rex/ui/presenter.h>

namespace rex::stream {
class ByteStream;
}

namespace rex::graphics {

class GraphicsSystem;
class Shader;

enum class ReadbackResolveMode {
  kDisabled,
  kFast,
  kSome,
  kFull,
};

enum class ZPDMode {
  kFake,
  kFast,
  kFastAlt,
  kStrict,
};

ZPDMode GetZPDMode();

constexpr uint32_t kZPDQueryPoolCapacity = 8192;

constexpr uint64_t kStrictZPDRetireDeadlineMs = 2;

constexpr uint64_t kFastZPDRetireDeadlineMs = 250;

constexpr size_t kFastZPDCacheMaxEntries = 1024;

struct SwapState {
  std::mutex mutex;

  uint32_t width = 0;
  uint32_t height = 0;

  uintptr_t front_buffer_texture = 0;

  uintptr_t back_buffer_texture = 0;

  void* backend_data = nullptr;

  bool pending = false;
};

enum class SwapMode {
  kNormal,
  kIgnored,
};

enum class GammaRampType {
  kUnknown = 0,
  kTable,
  kPWL,
};

class CommandProcessor {
 public:
  enum class SwapPostEffect {
    kNone,
    kFxaa,
    kFxaaExtreme,
  };

  CommandProcessor(GraphicsSystem* graphics_system, system::KernelState* kernel_state);
  virtual ~CommandProcessor();

  uint32_t counter() const { return counter_; }
  void increment_counter() { counter_++; }

  Shader* active_vertex_shader() const { return active_vertex_shader_; }
  Shader* active_pixel_shader() const { return active_pixel_shader_; }

  virtual bool Initialize();
  virtual void Shutdown();

  void CallInThread(std::function<void()> fn);

  virtual void ClearCaches();
  virtual void InvalidateGpuMemory();

  SwapPostEffect GetDesiredSwapPostEffect() const { return swap_post_effect_desired_; }
  void SetDesiredSwapPostEffect(SwapPostEffect swap_post_effect);

  virtual void IssueSwap(uint32_t frontbuffer_ptr, uint32_t frontbuffer_width,
                         uint32_t frontbuffer_height) = 0;

  virtual void InitializeShaderStorage(const std::filesystem::path& cache_root, uint32_t title_id,
                                       bool blocking);

  void InitializeRingBuffer(uint32_t ptr, uint32_t size_log2);
  void EnableReadPointerWriteBack(uint32_t ptr, uint32_t block_size_log2);

  void UpdateWritePointer(uint32_t value);

  void ExecutePacket(uint32_t ptr, uint32_t count);

  bool is_paused() const { return paused_; }
  void Pause();
  void Resume();

  bool Save(::rex::stream::ByteStream* stream);
  bool Restore(::rex::stream::ByteStream* stream);

 protected:
  virtual std::string TakeFrameTimingDetail() { return {}; }
  struct IndexBufferInfo {
    xenos::IndexFormat format = xenos::IndexFormat::kInt16;
    xenos::Endian endianness = xenos::Endian::kNone;
    uint32_t count = 0;
    uint32_t guest_base = 0;
    size_t length = 0;
  };

  void WorkerThreadMain();
  virtual bool SetupContext() = 0;
  virtual void ShutdownContext() = 0;

  virtual void WriteRegister(uint32_t index, uint32_t value);
  uint32_t ReadRegisterValue(uint32_t index) const;
  virtual void WriteRegistersFromMem(uint32_t start_index, uint32_t* base, uint32_t num_registers);
  virtual void WriteRegisterRangeFromRing(memory::RingBuffer* ring, uint32_t base,
                                          uint32_t num_registers);
  void WriteALURangeFromRing(memory::RingBuffer* ring, uint32_t base, uint32_t num_registers);
  void WriteFetchRangeFromRing(memory::RingBuffer* ring, uint32_t base, uint32_t num_registers);
  void WriteBoolRangeFromRing(memory::RingBuffer* ring, uint32_t base, uint32_t num_registers);
  void WriteLoopRangeFromRing(memory::RingBuffer* ring, uint32_t base, uint32_t num_registers);
  void WriteREGISTERSRangeFromRing(memory::RingBuffer* ring, uint32_t base, uint32_t num_registers);
  void WriteALURangeFromMem(uint32_t start_index, uint32_t* base, uint32_t num_registers);
  void WriteFetchRangeFromMem(uint32_t start_index, uint32_t* base, uint32_t num_registers);
  void WriteBoolRangeFromMem(uint32_t start_index, uint32_t* base, uint32_t num_registers);
  void WriteLoopRangeFromMem(uint32_t start_index, uint32_t* base, uint32_t num_registers);
  void WriteREGISTERSRangeFromMem(uint32_t start_index, uint32_t* base, uint32_t num_registers);

  const reg::DC_LUT_30_COLOR* gamma_ramp_256_entry_table() const {
    return gamma_ramp_256_entry_table_;
  }
  const reg::DC_LUT_PWL_DATA* gamma_ramp_pwl_rgb() const { return gamma_ramp_pwl_rgb_[0]; }
  virtual void OnGammaRamp256EntryTableValueWritten() {}
  virtual void OnGammaRampPWLValueWritten() {}

  virtual void MakeCoherent();
  virtual void PrepareForWait();
  virtual void ReturnFromWait();

  virtual void PollCompletedSubmission() {}

  virtual uint64_t GetCompletedSubmission() const { return 0; }

  uint32_t ExecutePrimaryBuffer(uint32_t start_index, uint32_t end_index);
  virtual void OnPrimaryBufferEnd() {}

  using ReportHandle = uint64_t;
  static constexpr ReportHandle kInvalidReportHandle = 0;

  enum class QueryOpenResult {
    kOpened,
    kDeferred,
    kPoolExhausted,
    kFailed,
  };

  struct ZPDReport {
    ReportHandle handle = kInvalidReportHandle;

    uint32_t address = 0;

    XenosZPDReport delta;

    uint64_t last_segment_end_submission = 0;
    uint32_t pending_segments = 0;

    XenosZPDReport speculative_value;
    XenosZPDReport speculative_delta;
    bool speculative = false;

    bool awaited = false;
  };

  static constexpr uint64_t kInvalidVIZGeneration = 0;
  struct VIZQueryHandle {
    uint32_t id = 0;
    uint64_t generation = kInvalidVIZGeneration;
  };

  struct ActiveZPDSegment {
    uint32_t scale_area = 0;

    bool count_total = false;
    bool segment_active = false;
    bool segment_pending_begin = false;

    bool report = false;

    VIZQueryHandle viz;

    bool survey = false;
    bool report_measuring() const { return segment_pending_begin || (segment_active && report); }
  };

  virtual void EnsureZPDQueryResources() {}
  virtual bool IsZPDQueryPoolReady() const { return false; }
  virtual bool CanOpenZPDQuery() const { return true; }

  virtual QueryOpenResult OpenZPDQuery(bool can_close_submission) {
    return QueryOpenResult::kFailed;
  }

  virtual bool CloseZPDQuery(ReportHandle report_handle, const VIZQueryHandle& viz,
                             uint64_t& out_submission) {
    return false;
  }

  virtual void PumpQueryResolves() {}

  virtual bool AwaitQueryResolve(ReportHandle report_handle, uint64_t wait_for_submission) {
    return false;
  }

  void QueueZPDReport(uint32_t report_address);

  void OpenQuerySegment(bool can_close_submission);

  void CloseQuerySegment();
  void EndZPDFrame() {
    CloseQuerySegment();
    zpd_active_segment_.segment_pending_begin = false;
  }

  void UpdateZPDSegment(uint32_t scale_area, bool count_total = false, bool survey = false);

  struct VIZQuery {
    uint64_t generation = kInvalidVIZGeneration;
    uint32_t pending_segments = 0;
    bool resolved = true;
    bool visible = true;
    bool active = false;

    bool surveyed = false;

    bool accumulated_visible = false;

    bool fallback = false;
    uint64_t last_segment_end_submission = 0;

    bool predicate_armed = false;

    bool predicate_blocked = false;
  };

  void BeginVIZQuery(uint32_t id);
  void EndVIZQuery(uint32_t id);

  void OnVIZSurveyDraw(bool measured);

  void OnVIZQueryResolved(uint32_t id, uint64_t generation, bool visible);

  bool PrepareVIZDraw(uint32_t token);

  virtual void AwaitVIZQueryResolve(uint64_t wait_for_submission) {}

  bool CanArmVIZPredicate(uint32_t id, uint64_t generation) const {
    const VIZQuery& query = viz_queries_[id];
    return query.generation == generation && !query.predicate_armed && !query.predicate_blocked;
  }
  void ArmVIZPredicate(uint32_t id, uint64_t generation) {
    VIZQuery& query = viz_queries_[id];
    assert_true(query.generation == generation);
    query.predicate_armed = true;
  }
  void BlockVIZPredicate(uint32_t id, uint64_t generation) {
    VIZQuery& query = viz_queries_[id];
    assert_true(query.generation == generation);
    query.predicate_armed = false;
    query.predicate_blocked = true;
  }

  bool IsVIZPredicateArmed() const {
    return viz_draw_predicate_.generation != kInvalidVIZGeneration &&
           viz_queries_[viz_draw_predicate_.id].predicate_armed;
  }
  void ResetVIZState() {
    zpd_active_segment_.viz = {};
    viz_draw_predicate_ = {};
    viz_pending_resolves_ = 0;
    for (VIZQuery& query : viz_queries_) {
      query = {};
    }
  }

  void OnZPDQueryResolved(ReportHandle report_handle, const XenosZPDReport& raw_counts,
                          uint32_t scale_area);

  ZPDReport* FindZPDReport(ReportHandle report_handle);

  void PrepareZPDForWait();

  void PumpPendingRetire();

  void WriteZPDReport(uint32_t report_address, const XenosZPDReport& value);
  void ResetZPDState();
  void ExecuteIndirectBuffer(uint32_t ptr, uint32_t length);
  bool ExecutePacket(memory::RingBuffer* reader);
  bool ExecutePacketType0(memory::RingBuffer* reader, uint32_t packet);
  bool ExecutePacketType1(memory::RingBuffer* reader, uint32_t packet);
  bool ExecutePacketType2(memory::RingBuffer* reader, uint32_t packet);
  bool ExecutePacketType3(memory::RingBuffer* reader, uint32_t packet);
  bool ExecutePacketType3_ME_INIT(memory::RingBuffer* reader, uint32_t packet, uint32_t count);
  bool ExecutePacketType3_NOP(memory::RingBuffer* reader, uint32_t packet, uint32_t count);
  bool ExecutePacketType3_INTERRUPT(memory::RingBuffer* reader, uint32_t packet, uint32_t count);
  bool ExecutePacketType3_XE_SWAP(memory::RingBuffer* reader, uint32_t packet, uint32_t count);
  bool ExecutePacketType3_INDIRECT_BUFFER(memory::RingBuffer* reader, uint32_t packet,
                                          uint32_t count);
  bool ExecutePacketType3_WAIT_REG_MEM(memory::RingBuffer* reader, uint32_t packet, uint32_t count);
  bool ExecutePacketType3_REG_RMW(memory::RingBuffer* reader, uint32_t packet, uint32_t count);
  bool ExecutePacketType3_REG_TO_MEM(memory::RingBuffer* reader, uint32_t packet, uint32_t count);
  bool ExecutePacketType3_MEM_WRITE(memory::RingBuffer* reader, uint32_t packet, uint32_t count);
  bool ExecutePacketType3_COND_WRITE(memory::RingBuffer* reader, uint32_t packet, uint32_t count);
  bool ExecutePacketType3_EVENT_WRITE(memory::RingBuffer* reader, uint32_t packet, uint32_t count);
  bool ExecutePacketType3_EVENT_WRITE_SHD(memory::RingBuffer* reader, uint32_t packet,
                                          uint32_t count);
  bool ExecutePacketType3_EVENT_WRITE_EXT(memory::RingBuffer* reader, uint32_t packet,
                                          uint32_t count);
  bool ExecutePacketType3_EVENT_WRITE_ZPD(memory::RingBuffer* reader, uint32_t packet,
                                          uint32_t count);
  bool ExecutePacketType3Draw(memory::RingBuffer* reader, uint32_t packet, const char* opcode_name,
                              uint32_t viz_query_condition, uint32_t count_remaining);
  bool ExecutePacketType3_DRAW_INDX(memory::RingBuffer* reader, uint32_t packet, uint32_t count);
  bool ExecutePacketType3_DRAW_INDX_2(memory::RingBuffer* reader, uint32_t packet, uint32_t count);
  bool ExecutePacketType3_SET_CONSTANT(memory::RingBuffer* reader, uint32_t packet, uint32_t count);
  bool ExecutePacketType3_SET_CONSTANT2(memory::RingBuffer* reader, uint32_t packet,
                                        uint32_t count);
  bool ExecutePacketType3_LOAD_ALU_CONSTANT(memory::RingBuffer* reader, uint32_t packet,
                                            uint32_t count);
  bool ExecutePacketType3_SET_SHADER_CONSTANTS(memory::RingBuffer* reader, uint32_t packet,
                                               uint32_t count);
  bool ExecutePacketType3_IM_LOAD(memory::RingBuffer* reader, uint32_t packet, uint32_t count);
  bool ExecutePacketType3_IM_LOAD_IMMEDIATE(memory::RingBuffer* reader,

                                            uint32_t packet, uint32_t count);
  bool ExecutePacketType3_INVALIDATE_STATE(memory::RingBuffer* reader, uint32_t packet,
                                           uint32_t count);
  bool ExecutePacketType3_VIZ_QUERY(memory::RingBuffer* reader, uint32_t packet, uint32_t count);

  virtual Shader* LoadShader(xenos::ShaderType shader_type, uint32_t guest_address,
                             const uint32_t* host_address, uint32_t dword_count) = 0;

  virtual bool IssueDraw(xenos::PrimitiveType prim_type, uint32_t index_count,
                         IndexBufferInfo* index_buffer_info, bool major_mode_explicit) = 0;
  virtual bool IssueCopy() = 0;

  SwapPostEffect GetActualSwapPostEffect() const { return swap_post_effect_actual_; }

  ReadbackResolveMode GetReadbackResolveMode(bool legacy_readback_resolve_enabled) const;

  bool IsReadbackMemexportEnabled(bool legacy_backend_flag) const;

  memory::Memory* memory_ = nullptr;
  system::KernelState* kernel_state_ = nullptr;
  GraphicsSystem* graphics_system_ = nullptr;
  RegisterFile* register_file_ = nullptr;

  std::atomic<bool> worker_running_;
  system::object_ref<system::XHostThread> worker_thread_;

  std::queue<std::function<void()>> pending_fns_;

  std::vector<uint32_t> me_bin_;

  uint32_t counter_ = 0;

  uint32_t primary_buffer_ptr_ = 0;
  uint32_t primary_buffer_size_ = 0;

  uint32_t read_ptr_index_ = 0;
  uint32_t read_ptr_update_freq_ = 0;
  uint32_t read_ptr_writeback_ptr_ = 0;

  std::unique_ptr<rex::thread::Event> write_ptr_index_event_;
  std::atomic<uint32_t> write_ptr_index_;

  std::unordered_map<uint32_t, uint32_t> extended_register_values_;

  uint64_t bin_select_ = 0xFFFFFFFFull;
  uint64_t bin_mask_ = 0xFFFFFFFFull;

  Shader* active_vertex_shader_ = nullptr;
  Shader* active_pixel_shader_ = nullptr;

  bool paused_ = false;

  SwapPostEffect swap_post_effect_desired_ = SwapPostEffect::kNone;
  SwapPostEffect swap_post_effect_actual_ = SwapPostEffect::kNone;

  ZPDMode zpd_mode_ = ZPDMode::kFast;

  ReportHandle zpd_next_report_handle_ = 1;

  ZPDReport zpd_current_report_;
  ActiveZPDSegment zpd_active_segment_{};

  bool query_segment_opening_ = false;

  std::array<VIZQuery, 64> viz_queries_{};

  VIZQueryHandle viz_draw_predicate_{};

  uint32_t viz_pending_resolves_ = 0;

  std::deque<ZPDReport> zpd_reports_;

  uint32_t zpd_awaited_report_count_ = 0;

  FrameStats frame_stats_;
  uint64_t frame_stats_last_swap_tick_ = 0;

  uint64_t frame_stats_idle_ticks_ = 0;
  uint64_t frame_stats_wait_reg_ticks_ = 0;

  XenosZPDReport zpd_sample_counter_;
  XenosZPDReport zpd_speculative_sample_counter_;
  std::unordered_map<uint32_t, XenosZPDReport> fast_zpd_report_cached_deltas_;

  bool zpd_force_fake_fallback_ = false;

  uint64_t zpd_pending_retire_start_ms_ = 0;

  uint32_t zpd_draw_resolution_scale_x_ = 1;
  uint32_t zpd_draw_resolution_scale_y_ = 1;

  uint32_t GetZPDScaleArea() const {
    return zpd_active_segment_.scale_area
               ? zpd_active_segment_.scale_area
               : zpd_draw_resolution_scale_x_ * zpd_draw_resolution_scale_y_;
  }

  const char* legacy_readback_memexport_cvar_name_ = nullptr;

 private:
  reg::DC_LUT_30_COLOR gamma_ramp_256_entry_table_[256] = {};
  reg::DC_LUT_PWL_DATA gamma_ramp_pwl_rgb_[128][3] = {};
  uint32_t gamma_ramp_rw_component_ = 0;
};

}
