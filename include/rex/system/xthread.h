#pragma once
/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2020 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <string>

#include <rex/platform.h>
#include <rex/thread/fiber.h>
#include <rex/system/thread_state.h>
#include <rex/system/util/native_list.h>
#include <rex/system/xmutant.h>
#include <rex/system/xobject.h>
#include <rex/system/xsemaphore.h>
#include <rex/system/xtimer.h>
#include <rex/system/xtypes.h>
#include <rex/thread.h>
#include <rex/thread/mutex.h>

namespace rex::system {

constexpr memory::fourcc_t kThreadSaveSignature = memory::make_fourcc("THRD");

class XEvent;

enum IRQL_FLAGS : uint8_t {
  IRQL_PASSIVE = 0,
  IRQL_APC = 1,
  IRQL_DISPATCH = 2,
  IRQL_DPC = 3,
  IRQL_AUDIO = 68,
  IRQL_CLOCK = 116,
  IRQL_HIGHEST = 124
};

enum X_DISPATCHER_FLAGS {
  DISPATCHER_MANUAL_RESET_EVENT = 0,
  DISPATCHER_AUTO_RESET_EVENT = 1,
  DISPATCHER_MUTANT = 2,
  DISPATCHER_QUEUE = 4,
  DISPATCHER_SEMAPHORE = 5,
  DISPATCHER_THREAD = 6,
  DISPATCHER_MANUAL_RESET_TIMER = 8,
  DISPATCHER_AUTO_RESET_TIMER = 9,
};

enum X_KTHREAD_STATE_FLAGS : uint8_t {
  KTHREAD_STATE_INITIALIZED = 0,
  KTHREAD_STATE_READY = 1,
  KTHREAD_STATE_RUNNING = 2,
  KTHREAD_STATE_STANDBY = 3,
  KTHREAD_STATE_TERMINATED = 4,
  KTHREAD_STATE_WAITING = 5,
  KTHREAD_STATE_UNKNOWN = 6,
};

constexpr uint32_t X_CREATE_SUSPENDED = 0x00000001;

constexpr uint32_t X_TLS_OUT_OF_INDEXES = UINT32_MAX;

struct XDPC {
  rex::be<uint16_t> type;
  uint8_t selected_cpu_number;
  uint8_t desired_cpu_number;
  X_LIST_ENTRY list_entry;
  rex::be<uint32_t> routine;
  rex::be<uint32_t> context;
  rex::be<uint32_t> arg1;
  rex::be<uint32_t> arg2;

  void Initialize(uint32_t guest_func, uint32_t guest_context) {
    type = 19;
    selected_cpu_number = 0;
    desired_cpu_number = 0;
    routine = guest_func;
    context = guest_context;
  }
};

struct XAPC {
  static constexpr uint32_t kSize = 40;
  static constexpr uint32_t kDummyKernelRoutine = 0xF00DFF00;
  static constexpr uint32_t kDummyRundownRoutine = 0xF00DFF01;

  uint16_t type;
  uint8_t apc_mode;
  uint8_t enqueued;
  rex::be<uint32_t> thread_ptr;
  X_LIST_ENTRY list_entry;
  rex::be<uint32_t> kernel_routine;
  rex::be<uint32_t> rundown_routine;
  rex::be<uint32_t> normal_routine;
  rex::be<uint32_t> normal_context;
  rex::be<uint32_t> arg1;
  rex::be<uint32_t> arg2;
};
static_assert_size(XAPC, 40);

struct X_FIBER_CONTEXT {
  rex::be<uint32_t> fiber_data;
  rex::be<uint32_t> stack_alloc_base;
  rex::be<uint32_t> stack_base;
  rex::be<uint32_t> stack_limit;
  uint8_t reserved_10[0x0C];
  rex::be<uint32_t> lr_save;
  uint8_t reserved_20[0x10];
  rex::be<uint64_t> sp_save;
  uint8_t register_save_area[0xA50 - 0x38];
};
static_assert_size(X_FIBER_CONTEXT, 0xA50);
static_assert(sizeof(X_FIBER_CONTEXT::register_save_area) >= ::PPCContext::kNonVolatileSaveSize,
              "fiber register save area too small for PPCContext non-volatiles");

struct X_KTHREAD;
struct X_KPROCESS;

struct X_KWAIT_BLOCK {
  X_LIST_ENTRY wait_list_entry;
  TypedGuestPointer<X_KTHREAD> thread;
  TypedGuestPointer<X_DISPATCH_HEADER> object;
  TypedGuestPointer<X_KWAIT_BLOCK> next_wait_block;
  rex::be<uint16_t> wait_result_xstatus;
  rex::be<uint16_t> wait_type;
};
static_assert_size(X_KWAIT_BLOCK, 0x18);

struct X_KPRCB {
  TypedGuestPointer<X_KTHREAD> current_thread;
  TypedGuestPointer<X_KTHREAD> next_thread;
  TypedGuestPointer<X_KTHREAD> idle_thread;
  uint8_t current_cpu;
  uint8_t unk_D[3];
  rex::be<uint32_t> processor_mask;
  rex::be<uint32_t> dpc_clock;
  rex::be<uint32_t> interrupt_clock;
  rex::be<uint32_t> unk_1C;
  rex::be<uint32_t> unk_20;
  rex::be<uint32_t> ipi_args[3];
  rex::be<uint32_t> targeted_ipi_cpus_mask;
  rex::be<uint32_t> ipi_function;
  TypedGuestPointer<X_KPRCB> ipi_initiator_prcb;
  rex::be<uint32_t> unk_3C;
  rex::be<uint32_t> dpc_related_40;
  rex::be<uint32_t> dpc_lock;
  X_LIST_ENTRY queued_dpcs_list_head;
  rex::be<uint32_t> dpc_active;
  X_KSPINLOCK spin_lock;
  TypedGuestPointer<X_KTHREAD> running_idle_thread;
  X_SINGLE_LIST_ENTRY enqueued_threads_list;
  rex::be<uint32_t> has_ready_thread_by_priority;
  rex::be<uint32_t> unk_mask_64;
  X_LIST_ENTRY unk_68[32];
  XDPC thread_exit_dpc;
  X_LIST_ENTRY terminating_threads_list;
  XDPC switch_thread_processor_dpc;
};

struct X_KPCR {
  rex::be<uint32_t> tls_ptr;
  rex::be<uint32_t> msr_mask;
  union {
    rex::be<uint16_t> software_interrupt_state;
    struct {
      uint8_t generic_software_interrupt;
      uint8_t apc_software_interrupt_state;
    };
  };
  rex::be<uint16_t> unk_0A;
  uint8_t processtype_value_in_dpc;
  uint8_t timeslice_ended;
  uint8_t timer_pending;
  uint8_t unk_0F;
  rex::be<uint32_t> thread_fpu_related;
  rex::be<uint32_t> thread_vmx_related;
  uint8_t current_irql;
  uint8_t background_scheduling_active;
  uint8_t background_scheduling_1A;
  uint8_t background_scheduling_1B;
  rex::be<uint32_t> timer_related;
  uint8_t unk_20[0x10];
  rex::be<uint64_t> pcr_ptr;
  union {
    uint8_t unk_38[8];
    uint64_t host_stash;
  };
  uint8_t unk_40[28];
  rex::be<uint32_t> unk_stack_5c;
  uint8_t unk_60[12];
  rex::be<uint32_t> use_alternative_stack;
  rex::be<uint32_t> stack_base_ptr;
  rex::be<uint32_t> stack_end_ptr;
  rex::be<uint32_t> alt_stack_base_ptr;
  rex::be<uint32_t> alt_stack_end_ptr;
  rex::be<uint32_t> interrupt_handlers[32];
  X_KPRCB prcb_data;
  TypedGuestPointer<X_KPRCB> prcb;
  uint8_t unk_2AC[0x2C];
};

struct X_KTHREAD {
  X_DISPATCH_HEADER header;
  rex::be<uint32_t> unk_10;
  rex::be<uint32_t> unk_14;
  X_KTIMER wait_timeout_timer;
  X_KWAIT_BLOCK wait_timeout_block;
  uint8_t unk_58[0x4];
  rex::be<uint32_t> stack_base;
  rex::be<uint32_t> stack_limit;
  rex::be<uint32_t> stack_kernel;
  rex::be<uint32_t> tls_address;
  uint8_t thread_state;
  uint8_t alerted[2];
  uint8_t alertable;
  uint8_t priority;
  uint8_t fpu_exceptions_on;
  uint8_t process_type_dup;
  uint8_t process_type;

  util::X_TYPED_LIST<XAPC, offsetof(XAPC, list_entry)> apc_lists[2];
  TypedGuestPointer<X_KPROCESS> process;
  uint8_t executing_kernel_apc;
  uint8_t deferred_apc_software_interrupt_state;
  uint8_t user_apc_pending;
  uint8_t may_queue_apcs;
  X_KSPINLOCK apc_lock;
  rex::be<uint32_t> num_context_switches_to;
  X_LIST_ENTRY ready_prcb_entry;
  rex::be<uint32_t> msr_mask;
  rex::be<X_STATUS> wait_result;
  uint8_t wait_irql;
  uint8_t unk_A5[0xB];
  int32_t apc_disable_count;
  rex::be<int32_t> quantum;
  uint8_t unk_B8;
  uint8_t unk_B9;
  uint8_t unk_BA;
  uint8_t boost_disabled;
  uint8_t suspend_count;
  uint8_t was_preempted;
  uint8_t terminated;
  uint8_t current_cpu;
  TypedGuestPointer<X_KPRCB> a_prcb_ptr;
  TypedGuestPointer<X_KPRCB> another_prcb_ptr;
  uint8_t unk_C8;
  uint8_t unk_C9;
  uint8_t unk_CA;
  uint8_t unk_CB;
  X_KSPINLOCK timer_list_lock;
  rex::be<uint32_t> stack_alloc_base;
  XAPC on_suspend;
  X_KSEMAPHORE suspend_sema;
  X_LIST_ENTRY process_threads;
  rex::be<uint32_t> unk_118;
  X_LIST_ENTRY queue_related;
  rex::be<uint32_t> unk_124;
  rex::be<uint32_t> unk_128;
  rex::be<uint32_t> unk_12C;
  rex::be<uint64_t> create_time;
  rex::be<uint64_t> exit_time;
  rex::be<uint32_t> exit_status;
  X_LIST_ENTRY timer_list;
  rex::be<uint32_t> thread_id;
  rex::be<uint32_t> start_address;
  X_LIST_ENTRY unk_154;
  uint8_t unk_15C[0x4];
  rex::be<uint32_t> last_error;
  rex::be<uint32_t> fiber_ptr;
  uint8_t unk_168[0x4];
  rex::be<uint32_t> creation_flags;
  uint8_t unk_170[0xC];
  rex::be<uint32_t> unk_17C;
  uint8_t unk_180[0x930];
};
static_assert_size(X_KTHREAD, 0xAB0);

class XThread : public XObject {
 public:
  static const XObject::Type kObjectType = XObject::Type::Thread;

  static constexpr uint32_t kStackAddressRangeBegin = 0x70000000;
  static constexpr uint32_t kStackAddressRangeEnd = 0x7F000000;

  struct CreationParams {
    uint32_t stack_size;
    uint32_t xapi_thread_startup;
    uint32_t start_address;
    uint32_t start_context;
    uint32_t creation_flags;
    uint32_t guest_process;
  };

  XThread(KernelState* kernel_state);
  XThread(KernelState* kernel_state, uint32_t stack_size, uint32_t xapi_thread_startup,
          uint32_t start_address, uint32_t start_context, uint32_t creation_flags,
          bool guest_thread, bool main_thread = false, uint32_t guest_process = 0);
  ~XThread() override;

  static bool IsInThread(XThread* other);
  static bool IsInThread();
  static XThread* GetCurrentThread();
  static uint32_t GetCurrentThreadHandle();
  static uint32_t GetCurrentThreadId();

  static void CheckTitleTermination();

  static uint32_t GetLastError();
  static void SetLastError(uint32_t error_code);

  const CreationParams* creation_params() const { return &creation_params_; }
  uint32_t tls_ptr() const { return tls_static_address_; }
  uint32_t pcr_ptr() const { return pcr_address_; }

  bool is_guest_thread() const { return guest_thread_; }
  bool main_thread() const { return main_thread_; }
  bool is_running() const { return running_; }

  uint32_t thread_id() const { return thread_id_; }

  uint32_t stack_base() const { return stack_base_; }
  uint32_t stack_limit() const { return stack_limit_; }
  uint32_t last_error();
  void set_last_error(uint32_t error_code);
  void set_name(const std::string_view name);

  X_STATUS Create();
  X_STATUS Exit(int exit_code);
  X_STATUS Terminate(int exit_code);

  virtual void Execute();

  rex::thread::Fiber* main_fiber() const { return main_fiber_; }
  void set_main_fiber(rex::thread::Fiber* fiber) { main_fiber_ = fiber; }

  void EnterCriticalRegion();
  void LeaveCriticalRegion();

  void DeliverAPCs();
  void LockApc();
  void UnlockApc(bool queue_delivery);
  void EnqueueApc(uint32_t normal_routine, uint32_t normal_context, uint32_t arg1, uint32_t arg2);

  int32_t priority() const { return priority_; }
  int32_t QueryPriority();
  void SetPriority(int32_t increment);

  void SetAffinity(uint32_t affinity);
  uint8_t active_cpu() const;
  void SetActiveCpu(uint8_t cpu_index);

  bool GetTLSValue(uint32_t slot, uint32_t* value_out);
  bool SetTLSValue(uint32_t slot, uint32_t value);

  uint32_t suspend_count();
  X_STATUS Resume(uint32_t* out_suspend_count = nullptr);
  X_STATUS Suspend(uint32_t* out_suspend_count = nullptr);
  X_STATUS Delay(uint32_t processor_mode, uint32_t alertable, uint64_t interval);

  rex::thread::Thread* thread() { return thread_.get(); }
  runtime::ThreadState* thread_state() { return thread_state_.get(); }

  virtual bool Save(stream::ByteStream* stream) override;
  static object_ref<XThread> Restore(KernelState* kernel_state, stream::ByteStream* stream);

  void AcquireMutantOnStartup(object_ref<XMutant> mutant) {
    pending_mutant_acquires_.push_back(mutant);
  }

 protected:
  bool AllocateStack(uint32_t size);
  void FreeStack();
  void InitializeGuestObject();

  void RundownAPCs();

  rex::thread::WaitHandle* GetWaitHandle() override { return thread_.get(); }

  CreationParams creation_params_ = {0, 0, 0, 0, 0, 0};

  std::vector<object_ref<XMutant>> pending_mutant_acquires_;

  uint32_t thread_id_ = 0;
  uint32_t scratch_address_ = 0;
  uint32_t scratch_size_ = 0;
  uint32_t tls_static_address_ = 0;
  uint32_t tls_dynamic_address_ = 0;
  uint32_t tls_total_size_ = 0;
  uint32_t pcr_address_ = 0;
  uint32_t stack_alloc_base_ = 0;
  uint32_t stack_alloc_size_ = 0;
  uint32_t stack_base_ = 0;
  uint32_t stack_limit_ = 0;
  bool guest_thread_ = false;
  bool main_thread_ = false;

  std::atomic<bool> running_{false};

  std::string thread_name_;
  std::unique_ptr<runtime::ThreadState> thread_state_;

  int32_t priority_ = 0;

  std::mutex thread_lock_;

  rex::thread::global_critical_region global_critical_region_;
  uint32_t apc_lock_old_irql_ = 0;

  std::unique_ptr<rex::thread::Thread> thread_ = nullptr;
  rex::thread::Fiber* main_fiber_ = nullptr;
};

class XHostThread : public XThread {
 public:
  XHostThread(KernelState* kernel_state, uint32_t stack_size, uint32_t creation_flags,
              std::function<int()> host_fn);

  virtual void Execute();

 private:
  std::function<int()> host_fn_;
};

}
