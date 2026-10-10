/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2026 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Ported from has207/xenia-edge 0788c561e3
 *              (RG-GDK-032) for the ReXGlue runtime
 */

#include <rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h>

#include <rex/platform.h>

#include <cstring>
#include <string>

#include "thirdparty/dxbc/DXBCChecksum.h"
#include <rex/logging.h>

#include <windows.h>

#include <wrl/client.h>
#include <algorithm>
#include <filesystem>
#include <mutex>

#include <dxcapi.h>
#include <rex/filesystem.h>

#include "spirv_to_dxil.h"

namespace rex::graphics {

namespace {
void SpirvToDxilLog(void* priv, const char* message) {
  REXGPU_ERROR("spirv_to_dxil: {}", message);
}

dxil_spirv_shader_stage ToDxilStage(SpirvToDxilCompiler::Stage stage_in, const char** stage_name) {
  using Stage = SpirvToDxilCompiler::Stage;
  switch (stage_in) {
    case Stage::kVertex:
      *stage_name = "vertex";
      return DXIL_SPIRV_SHADER_VERTEX;
    case Stage::kTessellationControl:
      *stage_name = "tessellation control";
      return DXIL_SPIRV_SHADER_TESS_CTRL;
    case Stage::kTessellationEvaluation:
      *stage_name = "tessellation evaluation";
      return DXIL_SPIRV_SHADER_TESS_EVAL;
    case Stage::kGeometry:
      *stage_name = "geometry";
      return DXIL_SPIRV_SHADER_GEOMETRY;
    case Stage::kCompute:
      *stage_name = "compute";
      return DXIL_SPIRV_SHADER_COMPUTE;
    default:
      *stage_name = "pixel";
      return DXIL_SPIRV_SHADER_FRAGMENT;
  }
}

dxil_spirv_runtime_conf MakeRuntimeConf(bool lower_to_bindless, bool keep_io_vars,
                                        uint32_t input_clip_size) {
  dxil_spirv_runtime_conf conf = {};
  conf.runtime_data_cbv.register_space = 31;
  conf.runtime_data_cbv.base_shader_register = 0;
  conf.push_constant_cbv.register_space = SpirvToDxilCompiler::kPushConstantRegisterSpace;
  conf.push_constant_cbv.base_shader_register = SpirvToDxilCompiler::kPushConstantShaderRegister;
  conf.first_vertex_and_base_instance_mode = DXIL_SPIRV_SYSVAL_TYPE_ZERO;
  conf.workgroup_id_mode = DXIL_SPIRV_SYSVAL_TYPE_ZERO;

  conf.yz_flip.mode = DXIL_SPIRV_YZ_FLIP_NONE;

  conf.disable_math_refactoring = true;
  conf.shader_model_max = SHADER_MODEL_6_6;
  conf.lower_to_bindless = lower_to_bindless;

  conf.bindless_descriptor_set_count = 4;

  conf.keep_io_vars = keep_io_vars;

  conf.input_clip_size = input_clip_size;
  return conf;
}

std::mutex dxil_validator_mutex;

IDxcValidator* dxil_validator_singleton = nullptr;
dxil_validator_version validator_version_value = NO_DXIL_VALIDATION;

class InPlaceBlob : public IDxcBlob {
 public:
  InPlaceBlob(void* data, size_t size) : data_(data), size_(size) {}
  LPVOID STDMETHODCALLTYPE GetBufferPointer() override { return data_; }
  SIZE_T STDMETHODCALLTYPE GetBufferSize() override { return size_; }
  HRESULT STDMETHODCALLTYPE QueryInterface(REFIID, void**) override { return E_NOINTERFACE; }
  ULONG STDMETHODCALLTYPE AddRef() override { return 1; }
  ULONG STDMETHODCALLTYPE Release() override { return 0; }

 private:
  void* data_;
  size_t size_;
};

DxcCreateInstanceProc LoadDxilCreateInstance() {
  std::filesystem::path dxil_path =
      rex::filesystem::GetExecutablePath().parent_path() / "D3D12" / "dxil.dll";
  HMODULE dxil = LoadLibraryW(dxil_path.wstring().c_str());
  if (!dxil) {
    dxil = LoadLibraryW(L"DXIL.dll");
  }
  if (!dxil) {
    return nullptr;
  }
  return reinterpret_cast<DxcCreateInstanceProc>(GetProcAddress(dxil, "DxcCreateInstance"));
}

dxil_validator_version QueryValidatorVersion(IDxcValidator* validator) {
  Microsoft::WRL::ComPtr<IDxcVersionInfo> version_info;
  if (FAILED(validator->QueryInterface(version_info.ReleaseAndGetAddressOf()))) {
    return NO_DXIL_VALIDATION;
  }
  UINT32 major = 0, minor = 0;
  if (FAILED(version_info->GetVersion(&major, &minor))) {
    return NO_DXIL_VALIDATION;
  }
  if (major == 1) {
    return dxil_validator_version(DXIL_VALIDATOR_1_0 + std::min(minor, 8u));
  }
  if (major > 1) {
    return DXIL_VALIDATOR_1_8;
  }
  return NO_DXIL_VALIDATION;
}

bool EnsureValidatorLocked() {
  if (!dxil_validator_singleton) {
    DxcCreateInstanceProc create = LoadDxilCreateInstance();
    if (!create) {
      REXGPU_ERROR(
          "spirv_to_dxil: could not load DxcCreateInstance from DXIL.dll; "
          "cannot sign DXIL");
      return false;
    }
    IDxcValidator* validator = nullptr;
    if (FAILED(create(CLSID_DxcValidator, IID_PPV_ARGS(&validator))) || !validator) {
      REXGPU_ERROR(
          "spirv_to_dxil: could not create the DXIL validator (is DXIL.dll "
          "present in D3D12/?); cannot sign DXIL");
      return false;
    }
    dxil_validator_singleton = validator;
    validator_version_value = QueryValidatorVersion(validator);
  }
  return true;
}

bool AcquireValidatorVersion(enum dxil_validator_version* out_version) {
  std::lock_guard<std::mutex> lock(dxil_validator_mutex);
  if (!EnsureValidatorLocked()) {
    return false;
  }
  *out_version = validator_version_value;
  return true;
}

bool SignDxil(std::vector<uint8_t>& dxil, const char* stage) {
  std::lock_guard<std::mutex> lock(dxil_validator_mutex);
  InPlaceBlob blob(dxil.data(), dxil.size());
  Microsoft::WRL::ComPtr<IDxcOperationResult> result;
  HRESULT hr = dxil_validator_singleton->Validate(&blob, DxcValidatorFlags_InPlaceEdit, &result);
  if (SUCCEEDED(hr) && result) {
    result->GetStatus(&hr);
  }
  if (FAILED(hr)) {
    std::string message;
    Microsoft::WRL::ComPtr<IDxcBlobEncoding> error_blob;
    if (result && SUCCEEDED(result->GetErrorBuffer(&error_blob)) && error_blob &&
        error_blob->GetBufferSize()) {
      message.assign(reinterpret_cast<const char*>(error_blob->GetBufferPointer()),
                     error_blob->GetBufferSize());
    }
    REXGPU_ERROR("spirv_to_dxil: DXIL validation/signing failed for {} shader: {}", stage,
                 message.empty() ? "(no message)" : message.c_str());
    return false;
  }
  return true;
}

}

uint64_t SpirvToDxilCompiler::version() {
  return spirv_to_dxil_get_version();
}

bool SpirvToDxilCompiler::IsSignerAvailable() {
  enum dxil_validator_version validator_version;
  return AcquireValidatorVersion(&validator_version);
}

std::vector<uint8_t> SpirvToDxilCompiler::Translate(const uint32_t* spirv_words,
                                                    size_t spirv_word_count, Stage stage_in,
                                                    bool lower_to_bindless,
                                                    uint32_t input_clip_size) {
  const char* stage_name;
  dxil_spirv_shader_stage stage = ToDxilStage(stage_in, &stage_name);

  dxil_spirv_runtime_conf conf = MakeRuntimeConf(lower_to_bindless, true, input_clip_size);

  dxil_spirv_debug_options debug_options = {};
  dxil_spirv_logger logger = {};
  logger.log = SpirvToDxilLog;

  enum dxil_validator_version validator_version;
  if (!AcquireValidatorVersion(&validator_version)) {
    return {};
  }

  dxil_spirv_object object = {};
  if (!spirv_to_dxil(spirv_words, spirv_word_count, nullptr, 0, stage, "main", validator_version,
                     &debug_options, &conf, &logger, &object)) {
    REXGPU_ERROR("spirv_to_dxil: translation failed for {} shader", stage_name);
    return {};
  }

  const uint8_t* bytes = reinterpret_cast<const uint8_t*>(object.binary.buffer);
  std::vector<uint8_t> dxil(bytes, bytes + object.binary.size);
  spirv_to_dxil_free(&object);

  if (!SignDxil(dxil, stage_name)) {
    return {};
  }
  return dxil;
}

std::vector<std::vector<uint8_t>> SpirvToDxilCompiler::TranslateLinked(
    const std::vector<LinkedStage>& stages, bool lower_to_bindless) {
  if (stages.empty()) {
    return {};
  }

  std::vector<dxil_spirv_link_stage> link_stages(stages.size());
  std::vector<const char*> stage_names(stages.size());
  for (size_t i = 0; i < stages.size(); ++i) {
    link_stages[i].words = stages[i].spirv_words;
    link_stages[i].word_count = stages[i].spirv_word_count;
    link_stages[i].stage = ToDxilStage(stages[i].stage, &stage_names[i]);
    link_stages[i].entry_point_name = "main";
  }

  dxil_spirv_runtime_conf conf = MakeRuntimeConf(lower_to_bindless, false, 0);
  dxil_spirv_debug_options debug_options = {};
  dxil_spirv_logger logger = {};
  logger.log = SpirvToDxilLog;

  enum dxil_validator_version validator_version;
  if (!AcquireValidatorVersion(&validator_version)) {
    return {};
  }

  std::vector<dxil_spirv_object> objects(stages.size());
  if (!spirv_to_dxil_link(link_stages.data(), link_stages.size(), validator_version, &debug_options,
                          &conf, &logger, objects.data())) {
    REXGPU_ERROR("spirv_to_dxil: linked translation failed ({} stages)", stages.size());
    return {};
  }

  std::vector<std::vector<uint8_t>> result(stages.size());
  for (size_t i = 0; i < stages.size(); ++i) {
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(objects[i].binary.buffer);
    result[i].assign(bytes, bytes + objects[i].binary.size);
    spirv_to_dxil_free(&objects[i]);
  }
  for (size_t i = 0; i < stages.size(); ++i) {
    if (!SignDxil(result[i], stage_names[i])) {
      return {};
    }
  }
  return result;
}

}
