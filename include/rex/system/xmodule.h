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

#include <string>

#include <rex/system/module.h>
#include <rex/system/xio.h>
#include <rex/system/xobject.h>
#include <rex/system/xtypes.h>

namespace rex::system {

constexpr memory::fourcc_t kModuleSaveSignature = memory::make_fourcc("XMOD");

struct X_LDR_DATA_TABLE_ENTRY {
  X_LIST_ENTRY in_load_order_links;
  X_LIST_ENTRY in_memory_order_links;
  X_LIST_ENTRY in_initialization_order_links;

  rex::be<uint32_t> dll_base;
  rex::be<uint32_t> image_base;
  rex::be<uint32_t> image_size;

  X_UNICODE_STRING full_dll_name;
  X_UNICODE_STRING base_dll_name;

  rex::be<uint32_t> flags;
  rex::be<uint32_t> full_image_size;
  rex::be<uint32_t> entry_point;
  rex::be<uint16_t> load_count;
  rex::be<uint16_t> module_index;
  rex::be<uint32_t> dll_base_original;
  rex::be<uint32_t> checksum;
  rex::be<uint32_t> load_flags;
  rex::be<uint32_t> time_date_stamp;
  rex::be<uint32_t> loaded_imports;
  rex::be<uint32_t> xex_header_base;

  rex::be<uint32_t> closure_root;
  rex::be<uint32_t> traversal_parent;
};

class XModule : public XObject {
 public:
  enum class ModuleType {

    kKernelModule = 0,
    kUserModule = 1,
  };

  static const XObject::Type kObjectType = XObject::Type::Module;

  XModule(KernelState* kernel_state, ModuleType module_type);
  virtual ~XModule();

  ModuleType module_type() const { return module_type_; }
  virtual const std::string& path() const = 0;
  virtual const std::string& name() const = 0;
  bool Matches(const std::string_view name) const;

  rex::runtime::Module* processor_module() const { return processor_module_; }
  uint32_t hmodule_ptr() const { return hmodule_ptr_; }

  virtual uint32_t GetProcAddressByOrdinal(uint16_t ordinal, uint32_t caller_address = 0) = 0;
  virtual uint32_t GetProcAddressByName(const std::string_view name) = 0;
  virtual X_STATUS GetSection(const std::string_view name, uint32_t* out_section_data,
                              uint32_t* out_section_size);

  static object_ref<XModule> GetFromHModule(KernelState* kernel_state, void* hmodule);
  static uint32_t GetHandleFromHModule(void* hmodule);

  virtual bool Save(stream::ByteStream* stream) override;
  static object_ref<XModule> Restore(KernelState* kernel_state, stream::ByteStream* stream);

 protected:
  void OnLoad();
  void OnUnload();

  ModuleType module_type_;

  rex::runtime::Module* processor_module_;

  uint32_t hmodule_ptr_;
};

}
