/**
 * @file        dxil_smoke_test.cpp
 * @brief       The opt-in DXIL toolchain end to end (RG-GDK-032 stage 1)
 *
 * SPIR-V through Mesa spirv_to_dxil, signed by DXC's dxil.dll, accepted by
 * D3D12 through the pinned Agility SDK, as the future guest shader path will
 * use them. Built only with REXGLUE_SHADER_DXIL.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <windows.h>

#include <d3d12.h>
#include <wrl/client.h>

#include <cstdint>
#include <cstring>
#include <filesystem>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <dxcapi.h>

#include "spirv_to_dxil.h"

// The Agility SDK the build deploys to .\D3D12\ (rexglue_deploy_d3d12_redist).
extern "C" {
__declspec(dllexport) extern const UINT D3D12SDKVersion = REXGLUE_D3D12_SDK_VERSION;
__declspec(dllexport) extern const char* D3D12SDKPath = ".\\D3D12\\";
}

namespace {

using Microsoft::WRL::ComPtr;

// An empty compute shader, hand-assembled:
//   OpCapability Shader
//   OpMemoryModel Logical GLSL450
//   OpEntryPoint GLCompute %1 "main"
//   OpExecutionMode %1 LocalSize 1 1 1
//   %2 = OpTypeVoid
//   %3 = OpTypeFunction %2
//   %1 = OpFunction %2 None %3
//   %4 = OpLabel
//   OpReturn
//   OpFunctionEnd
constexpr uint32_t kEmptyCompute[] = {
    0x07230203, 0x00010000, 0,  5,          0,     // header, bound 5
    0x00020011, 1,                                 // OpCapability Shader
    0x0003000E, 0,          1,                     // OpMemoryModel
    0x0005000F, 5,          1,  0x6E69616D, 0,     // OpEntryPoint "main"
    0x00060010, 1,          17, 1,          1, 1,  // OpExecutionMode LocalSize
    0x00020013, 2,                                 // OpTypeVoid
    0x00030021, 3,          2,                     // OpTypeFunction
    0x00050036, 2,          1,  0,          3,     // OpFunction
    0x000200F8, 4,                                 // OpLabel
    0x000100FD,                                    // OpReturn
    0x00010038,                                    // OpFunctionEnd
};

std::filesystem::path ExeDir() {
  wchar_t path[MAX_PATH];
  GetModuleFileNameW(nullptr, path, MAX_PATH);
  return std::filesystem::path(path).parent_path();
}

// A blob over caller memory, for the validator's in-place signing.
class InPlaceBlob : public IDxcBlob {
 public:
  InPlaceBlob(void* data, size_t size) : data_(data), size_(size) {}
  HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** out) override {
    if (riid == __uuidof(IUnknown) || riid == __uuidof(IDxcBlob)) {
      *out = static_cast<IDxcBlob*>(this);
      return S_OK;
    }
    *out = nullptr;
    return E_NOINTERFACE;
  }
  ULONG STDMETHODCALLTYPE AddRef() override { return 2; }
  ULONG STDMETHODCALLTYPE Release() override { return 1; }
  LPVOID STDMETHODCALLTYPE GetBufferPointer() override { return data_; }
  SIZE_T STDMETHODCALLTYPE GetBufferSize() override { return size_; }

 private:
  void* data_;
  size_t size_;
};

struct Validator {
  ComPtr<IDxcValidator> validator;
  dxil_validator_version version = NO_DXIL_VALIDATION;
  std::string error;
};

Validator LoadValidator() {
  Validator v;
  HMODULE dxil = LoadLibraryW((ExeDir() / L"D3D12" / L"dxil.dll").c_str());
  if (!dxil) {
    v.error = "dxil.dll not deployed";
    return v;
  }
  auto create = reinterpret_cast<DxcCreateInstanceProc>(GetProcAddress(dxil, "DxcCreateInstance"));
  if (!create || FAILED(create(CLSID_DxcValidator, IID_PPV_ARGS(&v.validator)))) {
    v.error = "no IDxcValidator";
    return v;
  }
  ComPtr<IDxcVersionInfo> info;
  UINT32 major = 0, minor = 0;
  if (SUCCEEDED(v.validator.As(&info)) && SUCCEEDED(info->GetVersion(&major, &minor)) &&
      major == 1) {
    v.version = dxil_validator_version(DXIL_VALIDATOR_1_0 + (minor < 8 ? minor : 8));
  }
  return v;
}

// SPIR-V to signed DXIL, or empty.
std::vector<uint8_t> Translate(Validator& v, std::string& error) {
  dxil_spirv_runtime_conf conf = {};
  conf.runtime_data_cbv.register_space = 31;
  conf.push_constant_cbv.register_space = 30;
  conf.first_vertex_and_base_instance_mode = DXIL_SPIRV_SYSVAL_TYPE_ZERO;
  conf.workgroup_id_mode = DXIL_SPIRV_SYSVAL_TYPE_ZERO;
  conf.shader_model_max = SHADER_MODEL_6_6;
  dxil_spirv_debug_options debug = {};
  dxil_spirv_logger logger = {};
  dxil_spirv_object object = {};
  if (!spirv_to_dxil(kEmptyCompute, sizeof(kEmptyCompute) / sizeof(uint32_t), nullptr, 0,
                     DXIL_SPIRV_SHADER_COMPUTE, "main", v.version, &debug, &conf, &logger,
                     &object)) {
    error = "spirv_to_dxil failed";
    return {};
  }
  const auto* bytes = static_cast<const uint8_t*>(object.binary.buffer);
  std::vector<uint8_t> dxil(bytes, bytes + object.binary.size);
  spirv_to_dxil_free(&object);

  InPlaceBlob blob(dxil.data(), dxil.size());
  ComPtr<IDxcOperationResult> result;
  HRESULT hr = v.validator->Validate(&blob, DxcValidatorFlags_InPlaceEdit, &result);
  if (SUCCEEDED(hr) && result) {
    result->GetStatus(&hr);
  }
  if (FAILED(hr)) {
    error = "dxil.dll rejected the DXIL";
    return {};
  }
  return dxil;
}

}  // namespace

TEST_CASE("Mesa spirv_to_dxil output is signed by the pinned dxil.dll", "[dxil]") {
  Validator v = LoadValidator();
  REQUIRE(v.validator);
  INFO("validator version enum " << int(v.version));
  CHECK(v.version >= DXIL_VALIDATOR_1_8);
  std::string error;
  std::vector<uint8_t> dxil = Translate(v, error);
  INFO(error);
  REQUIRE(dxil.size() > 32);
  CHECK(std::memcmp(dxil.data(), "DXBC", 4) == 0);
  // Signing writes the container digest after the magic.
  uint8_t zero[16] = {};
  CHECK(std::memcmp(dxil.data() + 4, zero, 16) != 0);
}

TEST_CASE("The Agility SDK runtime creates a pipeline from it", "[dxil]") {
  ComPtr<ID3D12Device> device;
  if (FAILED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device)))) {
    SKIP("no D3D12 device");
  }
  // The Agility SDK, not the OS runtime, is the one loaded.
  HMODULE core = GetModuleHandleW(L"D3D12Core.dll");
  REQUIRE(core);
  wchar_t core_path[MAX_PATH];
  GetModuleFileNameW(core, core_path, MAX_PATH);
  INFO("D3D12Core: " << std::filesystem::path(core_path).string());
  CHECK(std::filesystem::equivalent(std::filesystem::path(core_path).parent_path(),
                                    ExeDir() / L"D3D12"));

  D3D12_FEATURE_DATA_SHADER_MODEL model = {D3D_SHADER_MODEL_6_6};
  REQUIRE(
      SUCCEEDED(device->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &model, sizeof(model))));
  if (model.HighestShaderModel < D3D_SHADER_MODEL_6_6) {
    SKIP("adapter below Shader Model 6.6");
  }

  Validator v = LoadValidator();
  REQUIRE(v.validator);
  std::string error;
  std::vector<uint8_t> dxil = Translate(v, error);
  INFO(error);
  REQUIRE(!dxil.empty());

  D3D12_ROOT_SIGNATURE_DESC root_desc = {};
  ComPtr<ID3DBlob> root_blob, root_error;
  REQUIRE(SUCCEEDED(D3D12SerializeRootSignature(&root_desc, D3D_ROOT_SIGNATURE_VERSION_1,
                                                &root_blob, &root_error)));
  ComPtr<ID3D12RootSignature> root;
  REQUIRE(SUCCEEDED(device->CreateRootSignature(0, root_blob->GetBufferPointer(),
                                                root_blob->GetBufferSize(), IID_PPV_ARGS(&root))));
  D3D12_COMPUTE_PIPELINE_STATE_DESC desc = {};
  desc.pRootSignature = root.Get();
  desc.CS = {dxil.data(), dxil.size()};
  ComPtr<ID3D12PipelineState> pipeline;
  CHECK(SUCCEEDED(device->CreateComputePipelineState(&desc, IID_PPV_ARGS(&pipeline))));
}
