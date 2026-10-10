#pragma once
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

#include <algorithm>
#include <atomic>
#include <concepts>
#include <cstddef>
#include <string>
#include <vector>

#include <fmt/format.h>

#include <rex/system/xmemory.h>
#include <rex/system/xtypes.h>
#include <rex/thread.h>

namespace rex {
class Runtime;
namespace stream {
class ByteStream;
}
}

namespace rex::system {

constexpr memory::fourcc_t kXObjSignature = memory::make_fourcc('R', 'E', 'X', '\0');

class KernelState;

template <typename T>
class object_ref;

typedef struct {
  struct {
    uint8_t type;

    union {
      uint8_t abandoned;
      uint8_t absolute;
      uint8_t npx_irql;
      uint8_t signalling;
    };
    union {
      uint8_t size;
      uint8_t hand;
      uint8_t process_type;
    };
    union {
      uint8_t inserted;
      uint8_t debug_active;
      uint8_t dpc_active;
    };
  };

  rex::be<uint32_t> signal_state;
  rex::be<uint32_t> wait_list_flink;
  rex::be<uint32_t> wait_list_blink;
} X_DISPATCH_HEADER;
static_assert_size(X_DISPATCH_HEADER, 0x10);

struct X_OBJECT_HEADER {
  rex::be<uint32_t> pointer_count;
  union {
    rex::be<uint32_t> handle_count;
    rex::be<uint32_t> next_to_free;
  };
  uint8_t name_info_offset;
  uint8_t handle_info_offset;
  uint8_t quota_info_offset;
  uint8_t flags;
  union {
    rex::be<uint32_t> object_create_info;
    rex::be<uint32_t> quota_block_charged;
  };
  rex::be<uint32_t> object_type_ptr;
  rex::be<uint32_t> unk_04;
};

struct X_OBJECT_CREATE_INFORMATION {
  rex::be<uint32_t> attributes;
  rex::be<uint32_t> root_directory_ptr;
  rex::be<uint32_t> parse_context_ptr;
  rex::be<uint32_t> probe_mode;
  rex::be<uint32_t> paged_pool_charge;
  rex::be<uint32_t> non_paged_pool_charge;
  rex::be<uint32_t> security_descriptor_charge;
  rex::be<uint32_t> security_descriptor;
  rex::be<uint32_t> security_qos_ptr;
};

struct X_OBJECT_TYPE {
  rex::be<uint32_t> constructor;
  rex::be<uint32_t> destructor;
  rex::be<uint32_t> close_procedure;
  rex::be<uint32_t> delete_procedure;
  rex::be<uint32_t> parse_procedure;
  rex::be<uint32_t> default_object;
  rex::be<uint32_t> pool_tag;
};

class XObject {
 public:
  static constexpr uint32_t kHandleBase = 0xF8000000;

  enum class Type : uint32_t {
    Undefined,
    Enumerator,
    Event,
    File,
    IOCompletion,
    Module,
    Mutant,
    NotifyListener,
    Semaphore,
    Session,
    Socket,
    SymbolicLink,
    Thread,
    Timer,
  };

  XObject(Type type);
  XObject(KernelState* kernel_state, Type type);
  virtual ~XObject();

  rex::Runtime* emulator() const;
  KernelState* kernel_state() const;
  rex::memory::Memory* memory() const;

  Type type() const;

  X_HANDLE handle() const { return handles_[0]; }

  std::vector<X_HANDLE> handles() const { return handles_; }
  std::vector<X_HANDLE>& handles() { return handles_; }

  const std::string& name() const { return name_; }
  uint32_t guest_object() const { return guest_object_ptr_; }

  bool is_host_object() const { return host_object_; }
  void set_host_object(bool host_object) { host_object_ = host_object; }

  template <typename T>
  T* guest_object() {
    return memory()->TranslateVirtual<T*>(guest_object_ptr_);
  }

  void RetainHandle();
  bool ReleaseHandle();
  void Retain();
  void Release();
  X_STATUS Delete();

  virtual void OnAllHandlesClosed() {}

  virtual bool Save(stream::ByteStream* stream) {
    (void)stream;
    return false;
  }
  static object_ref<XObject> Restore(KernelState* kernel_state, Type type,
                                     stream::ByteStream* stream);

  void SetAttributes(uint32_t obj_attributes_ptr);

  X_STATUS Wait(uint32_t wait_reason, uint32_t processor_mode, uint32_t alertable,
                uint64_t* opt_timeout);
  static X_STATUS SignalAndWait(XObject* signal_object, XObject* wait_object, uint32_t wait_reason,
                                uint32_t processor_mode, uint32_t alertable, uint64_t* opt_timeout);
  static X_STATUS WaitMultiple(uint32_t count, XObject** objects, uint32_t wait_type,
                               uint32_t wait_reason, uint32_t processor_mode, uint32_t alertable,
                               uint64_t* opt_timeout);

  static object_ref<XObject> GetNativeObject(KernelState* kernel_state, void* native_ptr,
                                             int32_t as_type = -1);
  template <typename T>
  static object_ref<T> GetNativeObject(KernelState* kernel_state, void* native_ptr,
                                       int32_t as_type = -1);

 protected:
  bool SaveObject(stream::ByteStream* stream);
  bool RestoreObject(stream::ByteStream* stream);

  virtual void WaitCallback() {}

  virtual void BeginSignal() {}
  virtual void CancelSignal() {}

  virtual void SyncFromGuest() {}
  virtual rex::thread::WaitHandle* GetWaitHandle() { return nullptr; }

  uint8_t* CreateNative(uint32_t size);
  void SetNativePointer(uint32_t native_ptr, bool uninitialized = false);

  template <typename T>
  T* CreateNative() {
    return reinterpret_cast<T*>(CreateNative(sizeof(T)));
  }

  static void StashHandle(X_DISPATCH_HEADER* header, uint32_t handle) {
    header->wait_list_flink = kXObjSignature;
    header->wait_list_blink = handle;
  }

  static int64_t GuestTicksUntil(int64_t timeout_ticks);
  static uint32_t TimeoutTicksToMs(int64_t timeout_ticks);

  static std::chrono::microseconds GuestTimeoutToHost(int64_t timeout_ticks);

  KernelState* kernel_state_;

  bool host_object_ = false;

 private:
  std::atomic<int32_t> pointer_ref_count_;

  Type type_;
  std::vector<X_HANDLE> handles_;
  std::string name_;

  uint32_t guest_object_ptr_ = 0;
  bool allocated_guest_object_ = false;
};

template <typename T>
class object_ref {
 public:
  object_ref() noexcept : value_(nullptr) {}
  object_ref(std::nullptr_t) noexcept  // NOLINT(runtime/explicit)
      : value_(nullptr) {}
  object_ref& operator=(std::nullptr_t) noexcept {
    reset();
    return (*this);
  }

  explicit object_ref(T* value) noexcept : value_(value) {}
  explicit object_ref(const object_ref& right) noexcept {
    reset(right.get());
    if (value_)
      value_->Retain();
  }
  template <class V>
    requires std::convertible_to<V*, T*>
  object_ref(const object_ref<V>& right) noexcept {
    reset(right.get());
    if (value_)
      value_->Retain();
  }

  object_ref(object_ref&& right) noexcept : value_(right.release()) {}
  object_ref& operator=(object_ref&& right) noexcept {
    object_ref(std::move(right)).swap(*this);
    return (*this);
  }
  template <typename V>
  object_ref& operator=(object_ref<V>&& right) noexcept {
    object_ref(std::move(right)).swap(*this);
    return (*this);
  }

  object_ref& operator=(const object_ref& right) noexcept {
    object_ref(right).swap(*this);  // NOLINT(runtime/explicit): misrecognized?
    return (*this);
  }
  template <typename V>
  object_ref& operator=(const object_ref<V>& right) noexcept {
    object_ref(right).swap(*this);  // NOLINT(runtime/explicit): misrecognized?
    return (*this);
  }

  void swap(object_ref& right) noexcept { std::swap(value_, right.value_); }

  ~object_ref() noexcept {
    if (value_) {
      value_->Release();
      value_ = nullptr;
    }
  }

  typename std::add_lvalue_reference<T>::type operator*() const { return (*get()); }

  T* operator->() const noexcept { return std::pointer_traits<T*>::pointer_to(**this); }

  T* get() const noexcept { return value_; }

  template <typename V>
  V* get() const noexcept {
    return reinterpret_cast<V*>(value_);
  }

  explicit operator bool() const noexcept { return value_ != nullptr; }

  T* release() noexcept {
    T* value = value_;
    value_ = nullptr;
    return value;
  }

  void reset() noexcept { object_ref().swap(*this); }

  void reset(T* value) noexcept { object_ref(value).swap(*this); }

  inline bool operator==(const T* right) const noexcept { return value_ == right; }
  inline bool operator!=(const T* right) const noexcept { return value_ != right; }

  inline bool operator==(std::nullptr_t) const noexcept { return value_ == nullptr; }
  inline bool operator!=(std::nullptr_t) const noexcept { return value_ != nullptr; }

 private:
  T* value_ = nullptr;
};

template <class _Ty>
bool operator==(const object_ref<_Ty>& _Left, std::nullptr_t) noexcept {
  return (_Left.get() == reinterpret_cast<_Ty*>(0));
}

template <class _Ty>
bool operator==(std::nullptr_t, const object_ref<_Ty>& _Right) noexcept {
  return (reinterpret_cast<_Ty*>(0) == _Right.get());
}

template <class _Ty>
bool operator!=(const object_ref<_Ty>& _Left, std::nullptr_t _Right) noexcept {
  return (!(_Left == _Right));
}

template <class _Ty>
bool operator!=(std::nullptr_t _Left, const object_ref<_Ty>& _Right) noexcept {
  return (!(_Left == _Right));
}

template <class T, class... Args>
  requires(!std::is_array_v<T>)
object_ref<T> make_object(Args&&... args) {
  return object_ref<T>(new T(std::forward<Args>(args)...));
}

template <typename T>
object_ref<T> retain_object(T* ptr) {
  if (ptr)
    ptr->Retain();
  return object_ref<T>(ptr);
}

template <typename T>
object_ref<T> XObject::GetNativeObject(KernelState* kernel_state, void* native_ptr,
                                       int32_t as_type) {
  return object_ref<T>(
      reinterpret_cast<T*>(GetNativeObject(kernel_state, native_ptr, as_type).release()));
}

}

template <>
struct fmt::formatter<rex::system::XObject::Type> : fmt::formatter<uint32_t> {
  template <typename FormatContext>
  auto format(rex::system::XObject::Type t, FormatContext& ctx) const {
    return fmt::formatter<uint32_t>::format(static_cast<uint32_t>(t), ctx);
  }
};
