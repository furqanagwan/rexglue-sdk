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

#include <rex/assert.h>
#include <rex/kernel/xboxkrnl/private.h>
#include <rex/logging.h>
#include <rex/hook.h>
#include <rex/types.h>
#include <rex/system/kernel_state.h>
#include <rex/system/util/string_utils.h>
#include <rex/system/kernel_event.h>
#include <rex/system/kernel_object.h>
#include <rex/system/kernel_semaphore.h>
#include <rex/system/kernel_thread.h>
#include <rex/system/xtypes.h>

namespace rex::kernel::xboxkrnl {
using namespace rex::system;

u32 ObOpenObjectByName_entry(mapped_void obj_attributes_ptr, mapped_void object_type_ptr, u32 unk,
                             mapped_u32 handle_ptr) {
  if (!obj_attributes_ptr) {
    return X_STATUS_INVALID_PARAMETER;
  }

  auto obj_attributes = REX_KERNEL_MEMORY()->TranslateVirtual<X_OBJECT_ATTRIBUTES*>(
      obj_attributes_ptr.guest_address());
  assert_true(obj_attributes->name_ptr != 0);
  auto name = util::TranslateAnsiStringAddress(REX_KERNEL_MEMORY(), obj_attributes->name_ptr);

  X_HANDLE handle = X_INVALID_HANDLE_VALUE;
  X_STATUS result = REX_KERNEL_OBJECTS()->GetObjectByName(name, &handle);
  if (XSUCCEEDED(result)) {
    *handle_ptr = handle;
  }

  return result;
}

u32 ObOpenObjectByPointer_entry(mapped_void object_ptr, mapped_u32 out_handle_ptr) {
  auto object = XObject::GetNativeObject<XObject>(REX_KERNEL_STATE(), object_ptr);
  if (!object) {
    return X_STATUS_UNSUCCESSFUL;
  }

  object->RetainHandle();
  *out_handle_ptr = object->handle();
  return X_STATUS_SUCCESS;
}

u32 ObLookupThreadByThreadId_entry(u32 thread_id, mapped_u32 out_object_ptr) {
  auto thread = REX_KERNEL_STATE()->GetThreadByID(thread_id);
  if (!thread) {
    return X_STATUS_NOT_FOUND;
  }

  thread->RetainHandle();
  *out_object_ptr = thread->guest_object();
  return X_STATUS_SUCCESS;
}

u32 ObReferenceObjectByHandle_entry(u32 handle, u32 object_type_ptr, mapped_u32 out_object_ptr) {
  REXKRNL_IMPORT_TRACE("ObReferenceObjectByHandle", "handle={:#x} type={:#x}", (uint32_t)handle,
                       (uint32_t)object_type_ptr);

  object_ref<XObject> object;

  uint32_t handle_val = static_cast<uint32_t>(handle);
  if (handle_val == 0xFFFFFFFE) {
    auto thread = XThread::GetCurrentThread();
    if (!thread) {
      return X_STATUS_INVALID_HANDLE;
    }
    object = retain_object(static_cast<XObject*>(thread));
  } else {
    object = REX_KERNEL_OBJECTS()->LookupObject<XObject>(handle);
  }

  if (!object) {
    return X_STATUS_INVALID_HANDLE;
  }

  uint32_t native_ptr = object->guest_object();

  if (object_type_ptr) {
    uint32_t globals_base = REX_KERNEL_STATE()->GetKernelGuestGlobals();
    uint32_t expected_type = 0;
    switch (object->type()) {
      case XObject::Type::Thread:
        expected_type = globals_base + offsetof(KernelGuestGlobals, ExThreadObjectType);
        break;
      case XObject::Type::Event:
        expected_type = globals_base + offsetof(KernelGuestGlobals, ExEventObjectType);
        break;
      case XObject::Type::Mutant:
        expected_type = globals_base + offsetof(KernelGuestGlobals, ExMutantObjectType);
        break;
      case XObject::Type::Semaphore:
        expected_type = globals_base + offsetof(KernelGuestGlobals, ExSemaphoreObjectType);
        break;
      case XObject::Type::Timer:
        expected_type = globals_base + offsetof(KernelGuestGlobals, ExTimerObjectType);
        break;
      default:
        break;
    }
    if (expected_type && object_type_ptr != expected_type) {
      return X_STATUS_OBJECT_TYPE_MISMATCH;
    }
  }

  object->RetainHandle();
  if (out_object_ptr.guest_address()) {
    *out_object_ptr = native_ptr;
  }
  REXKRNL_IMPORT_RESULT("ObReferenceObjectByHandle", "0x0 obj={:#x}", native_ptr);
  return X_STATUS_SUCCESS;
}

u32 ObReferenceObjectByName_entry(mapped_string name, u32 attributes, u32 object_type_ptr,
                                  mapped_void parse_context, mapped_u32 out_object_ptr) {
  X_HANDLE handle = X_INVALID_HANDLE_VALUE;
  X_STATUS result = REX_KERNEL_OBJECTS()->GetObjectByName(name.value(), &handle);
  if (XSUCCEEDED(result)) {
    return ObReferenceObjectByHandle_entry(handle, object_type_ptr, out_object_ptr);
  }

  return result;
}

u32 ObDereferenceObject_entry(u32 native_ptr) {
  REXKRNL_IMPORT_TRACE("ObDereferenceObject", "ptr={:#x}", (uint32_t)native_ptr);

  if (native_ptr == 0xDEADF00D) {
    return 0;
  }

  auto object = XObject::GetNativeObject<XObject>(
      REX_KERNEL_STATE(), REX_KERNEL_MEMORY()->TranslateVirtual(native_ptr));
  if (object) {
    object->ReleaseHandle();
  }

  return 0;
}

u32 ObCreateSymbolicLink_entry(ppc_ptr_t<X_ANSI_STRING> path_ptr,
                               ppc_ptr_t<X_ANSI_STRING> target_ptr) {
  auto path = rex::string::utf8_canonicalize_guest_path(
      util::TranslateAnsiPath(REX_KERNEL_MEMORY(), path_ptr));
  auto target = rex::string::utf8_canonicalize_guest_path(
      util::TranslateAnsiPath(REX_KERNEL_MEMORY(), target_ptr));

  if (rex::string::utf8_starts_with(path, u8"\\??\\")) {
    path = path.substr(4);
  }

  if (!REX_KERNEL_FS()->RegisterSymbolicLink(path, target)) {
    return X_STATUS_UNSUCCESSFUL;
  }

  return X_STATUS_SUCCESS;
}

u32 ObDeleteSymbolicLink_entry(ppc_ptr_t<X_ANSI_STRING> path_ptr) {
  auto path = util::TranslateAnsiPath(REX_KERNEL_MEMORY(), path_ptr);
  if (!REX_KERNEL_FS()->UnregisterSymbolicLink(path)) {
    return X_STATUS_UNSUCCESSFUL;
  }

  return X_STATUS_SUCCESS;
}

u32 NtDuplicateObject_entry(u32 handle, mapped_u32 new_handle_ptr, u32 options) {
  X_HANDLE new_handle = X_INVALID_HANDLE_VALUE;
  X_STATUS result = REX_KERNEL_OBJECTS()->DuplicateHandle(handle, &new_handle);

  if (new_handle_ptr) {
    *new_handle_ptr = new_handle;
  }

  if (options == 1) {
    REX_KERNEL_OBJECTS()->RemoveHandle(handle);
  }

  return result;
}

u32 NtClose_entry(u32 handle) {
  REXKRNL_IMPORT_TRACE("NtClose", "handle={:#x}", (uint32_t)handle);
  auto result = REX_KERNEL_OBJECTS()->ReleaseHandle(handle);
  REXKRNL_IMPORT_RESULT("NtClose", "{:#x}", result);
  return result;
}

u32 NtQueryEvent_entry(u32 handle, mapped_u32 out_struc) {
  X_STATUS result = X_STATUS_SUCCESS;

  auto ev = REX_KERNEL_OBJECTS()->LookupObject<XEvent>(handle);
  if (ev) {
    uint32_t type_tmp, state_tmp;
    ev->Query(&type_tmp, &state_tmp);
    out_struc[0] = type_tmp;
    out_struc[1] = state_tmp;
  } else {
    result = X_STATUS_INVALID_HANDLE;
  }

  return result;
}

}

REX_EXPORT(__imp__ObOpenObjectByName, rex::kernel::xboxkrnl::ObOpenObjectByName_entry)
REX_EXPORT(__imp__ObOpenObjectByPointer, rex::kernel::xboxkrnl::ObOpenObjectByPointer_entry)
REX_EXPORT(__imp__ObLookupThreadByThreadId, rex::kernel::xboxkrnl::ObLookupThreadByThreadId_entry)
REX_EXPORT(__imp__ObReferenceObjectByHandle, rex::kernel::xboxkrnl::ObReferenceObjectByHandle_entry)
REX_EXPORT(__imp__ObReferenceObjectByName, rex::kernel::xboxkrnl::ObReferenceObjectByName_entry)
REX_EXPORT(__imp__ObDereferenceObject, rex::kernel::xboxkrnl::ObDereferenceObject_entry)
REX_EXPORT(__imp__ObCreateSymbolicLink, rex::kernel::xboxkrnl::ObCreateSymbolicLink_entry)
REX_EXPORT(__imp__ObDeleteSymbolicLink, rex::kernel::xboxkrnl::ObDeleteSymbolicLink_entry)
REX_EXPORT(__imp__NtDuplicateObject, rex::kernel::xboxkrnl::NtDuplicateObject_entry)
REX_EXPORT(__imp__NtClose, rex::kernel::xboxkrnl::NtClose_entry)
REX_EXPORT(__imp__NtQueryEvent, rex::kernel::xboxkrnl::NtQueryEvent_entry)

REX_EXPORT_STUB(__imp__ObCreateObject);
REX_EXPORT_STUB(__imp__ObGetWaitableObject);
REX_EXPORT_STUB(__imp__ObInsertObject);
REX_EXPORT_STUB(__imp__ObIsTitleObject);
REX_EXPORT_STUB(__imp__ObLookupAnyThreadByThreadId);
REX_EXPORT_STUB(__imp__ObMakeTemporaryObject);
REX_EXPORT_STUB(__imp__ObReferenceObject);
REX_EXPORT_STUB(__imp__ObTranslateSymbolicLink);
REX_EXPORT_STUB(__imp__NtCreateDirectoryObject);
REX_EXPORT_STUB(__imp__NtCreateSymbolicLinkObject);
REX_EXPORT_STUB(__imp__NtMakeTemporaryObject);
REX_EXPORT_STUB(__imp__NtOpenDirectoryObject);
REX_EXPORT_STUB(__imp__NtQueryDirectoryObject);
REX_EXPORT_STUB(__imp__NtQueryIoCompletion);
REX_EXPORT_STUB(__imp__NtQueryMutant);
REX_EXPORT_STUB(__imp__NtQuerySemaphore);
REX_EXPORT_STUB(__imp__NtQueryTimer);
