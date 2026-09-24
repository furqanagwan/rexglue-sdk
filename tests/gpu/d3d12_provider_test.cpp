/**
 * @file        d3d12_provider_test.cpp
 * @brief       D3D12 provider capability metadata (RG-GDK-006)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <cstdio>

#include <catch2/catch_test_macros.hpp>

#include <rex/cvar.h>
#include <rex/logging.h>
#include <rex/ui/d3d12/d3d12_provider.h>

REXCVAR_DECLARE(int32_t, d3d12_adapter);
REXCVAR_DECLARE(bool, d3d12_dred);

namespace {

using rex::ui::d3d12::D3D12Provider;

// Adapter selection is read once at creation, so each case sets it and
// restores the default afterwards.
std::unique_ptr<D3D12Provider> CreateProvider(int32_t adapter, bool dred = false) {
  static bool logging_initialized = [] {
    rex::InitLogging();
    return true;
  }();
  (void)logging_initialized;
  REXCVAR_SET(d3d12_adapter, adapter);
  REXCVAR_SET(d3d12_dred, dred);
  auto provider = D3D12Provider::Create();
  REXCVAR_SET(d3d12_adapter, -1);
  REXCVAR_SET(d3d12_dred, false);
  return provider;
}

void PrintMetadata(const char* label, const D3D12Provider& provider) {
  std::printf("%s: vendor 0x%04X, driver %s, feature level 0x%X, shader model 0x%X\n", label,
              uint32_t(provider.GetAdapterVendorID()), provider.GetDriverVersion().c_str(),
              uint32_t(provider.GetMaxFeatureLevel()), uint32_t(provider.GetHighestShaderModel()));
}

}  // namespace

TEST_CASE("WARP adapter records capability metadata", "[gpu][d3d12]") {
  if (!D3D12Provider::IsD3D12APIAvailable()) {
    SKIP("Direct3D 12 is not available");
  }
  auto provider = CreateProvider(-2);
  REQUIRE(provider);
  PrintMetadata("WARP", *provider);
  CHECK(provider->IsAdapterSoftware());
  CHECK(provider->GetDriverVersion() != "unknown");
  CHECK(provider->GetMaxFeatureLevel() >= D3D_FEATURE_LEVEL_11_0);
  CHECK(provider->GetHighestShaderModel() >= D3D_SHADER_MODEL_5_1);
  CHECK_FALSE(provider->IsDredEnabled());
}

TEST_CASE("d3d12_dred enables DRED without the debug layer", "[gpu][d3d12]") {
  if (!D3D12Provider::IsD3D12APIAvailable()) {
    SKIP("Direct3D 12 is not available");
  }
  auto provider = CreateProvider(-2, true);
  REQUIRE(provider);
  CHECK(provider->IsDredEnabled());
}

TEST_CASE("Hardware adapter records capability metadata", "[gpu][d3d12]") {
  if (!D3D12Provider::IsD3D12APIAvailable()) {
    SKIP("Direct3D 12 is not available");
  }
  auto provider = CreateProvider(-1);
  if (!provider) {
    SKIP("No hardware Direct3D 12 adapter");
  }
  PrintMetadata("Hardware", *provider);
  CHECK_FALSE(provider->IsAdapterSoftware());
  CHECK(provider->GetDriverVersion() != "unknown");
  CHECK(provider->GetMaxFeatureLevel() >= D3D_FEATURE_LEVEL_11_0);
}
