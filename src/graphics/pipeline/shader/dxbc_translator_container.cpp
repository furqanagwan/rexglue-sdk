/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2018 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include "thirdparty/dxbc/DXBCChecksum.h"
#include <algorithm>
#include <atomic>
#include <cstring>
#include <memory>
#include <rex/assert.h>
#include <rex/cvar.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/pipeline/shader/dxbc.h>
#include <rex/graphics/pipeline/shader/dxbc_translator.h>
#include <rex/graphics/xenos.h>
#include <rex/math.h>
#include <rex/ui/graphics_provider.h>

namespace rex::graphics {

void DxbcShaderTranslator::WriteResourceDefinition() {
  uint32_t blob_position_dwords = uint32_t(shader_object_.size());
  uint32_t name_ptr;

  const Shader::ConstantRegisterMap& constant_register_map =
      current_shader().constant_register_map();

  shader_object_.resize(shader_object_.size() + sizeof(dxbc::RdefHeader) / sizeof(uint32_t));

  dxbc::AppendAlignedString(shader_object_, "Xenia");

  name_ptr = (uint32_t(shader_object_.size()) - blob_position_dwords) * sizeof(uint32_t);
  uint32_t type_name_ptrs[size_t(ShaderRdefTypeIndex::kCount)];
  for (uint32_t i = 0; i < uint32_t(ShaderRdefTypeIndex::kCount); ++i) {
    const ShaderRdefType& type = rdef_types_[i];
    if (type.name == nullptr) {
      assert_true(uint32_t(type.array_element_type) < i);
      type_name_ptrs[i] = type_name_ptrs[uint32_t(type.array_element_type)];
      continue;
    }
    type_name_ptrs[i] = name_ptr;
    name_ptr += dxbc::AppendAlignedString(shader_object_, type.name);
  }

  uint32_t types_position_dwords = uint32_t(shader_object_.size());
  uint32_t types_ptr = (types_position_dwords - blob_position_dwords) * sizeof(uint32_t);
  shader_object_.resize(types_position_dwords + sizeof(dxbc::RdefType) / sizeof(uint32_t) *
                                                    uint32_t(ShaderRdefTypeIndex::kCount));
  {
    auto types = reinterpret_cast<dxbc::RdefType*>(shader_object_.data() + types_position_dwords);
    for (uint32_t i = 0; i < uint32_t(ShaderRdefTypeIndex::kCount); ++i) {
      dxbc::RdefType& type = types[i];
      const ShaderRdefType& translator_type = rdef_types_[i];
      type.variable_class = translator_type.variable_class;
      type.variable_type = translator_type.variable_type;
      type.row_count = translator_type.row_count;
      type.column_count = translator_type.column_count;
      switch (ShaderRdefTypeIndex(i)) {
        case ShaderRdefTypeIndex::kFloat4ConstantArray:

          type.element_count = std::max(uint16_t(constant_register_map.float_count), uint16_t(1));
          break;
        case ShaderRdefTypeIndex::kUint4DescriptorIndexArray:
          type.element_count =
              std::max(uint16_t((GetBindlessResourceCount() + 3) >> 2), uint16_t(1));
          break;
        default:
          type.element_count = translator_type.element_count;
      }
      type.name_ptr = type_name_ptrs[i];
    }
  }

  name_ptr = (uint32_t(shader_object_.size()) - blob_position_dwords) * sizeof(uint32_t);
  uint32_t constant_name_ptrs_system[size_t(SystemConstants::Index::kCount)];
  if (cbuffer_index_system_constants_ != kBindingIndexUnallocated) {
    for (size_t i = 0; i < size_t(SystemConstants::Index::kCount); ++i) {
      constant_name_ptrs_system[i] = name_ptr;
      name_ptr += dxbc::AppendAlignedString(shader_object_, system_constant_rdef_[i].name);
    }
  }
  uint32_t constant_name_ptr_float = name_ptr;
  if (cbuffer_index_float_constants_ != kBindingIndexUnallocated) {
    name_ptr += dxbc::AppendAlignedString(shader_object_, "xe_float_constants");
  }
  uint32_t constant_name_ptr_bool = name_ptr;
  uint32_t constant_name_ptr_loop = name_ptr;
  if (cbuffer_index_bool_loop_constants_ != kBindingIndexUnallocated) {
    name_ptr += dxbc::AppendAlignedString(shader_object_, "xe_bool_constants");
    constant_name_ptr_loop = name_ptr;
    name_ptr += dxbc::AppendAlignedString(shader_object_, "xe_loop_constants");
  }
  uint32_t constant_name_ptr_fetch = name_ptr;
  if (cbuffer_index_fetch_constants_ != kBindingIndexUnallocated) {
    name_ptr += dxbc::AppendAlignedString(shader_object_, "xe_fetch_constants");
  }
  uint32_t constant_name_ptr_descriptor_indices = name_ptr;
  if (cbuffer_index_descriptor_indices_ != kBindingIndexUnallocated) {
    name_ptr += dxbc::AppendAlignedString(shader_object_, "xe_descriptor_indices");
  }

  uint32_t constant_position_dwords_system = uint32_t(shader_object_.size());
  if (cbuffer_index_system_constants_ != kBindingIndexUnallocated) {
    shader_object_.resize(constant_position_dwords_system +
                          sizeof(dxbc::RdefVariable) / sizeof(uint32_t) *
                              size_t(SystemConstants::Index::kCount));
    auto constants_system = reinterpret_cast<dxbc::RdefVariable*>(shader_object_.data() +
                                                                  constant_position_dwords_system);
    uint32_t constant_offset_system = 0;
    for (size_t i = 0; i < size_t(SystemConstants::Index::kCount); ++i) {
      dxbc::RdefVariable& constant_system = constants_system[i];
      const SystemConstantRdef& translator_constant_system = system_constant_rdef_[i];
      constant_system.name_ptr = constant_name_ptrs_system[i];
      constant_system.start_offset_bytes = constant_offset_system;
      constant_system.size_bytes = translator_constant_system.size;
      constant_system.flags =
          (system_constants_used_ & (uint64_t(1) << i)) ? dxbc::kRdefVariableFlagUsed : 0;
      constant_system.type_ptr =
          types_ptr + sizeof(dxbc::RdefType) * uint32_t(translator_constant_system.type);
      constant_system.start_texture = UINT32_MAX;
      constant_system.start_sampler = UINT32_MAX;
      constant_offset_system +=
          translator_constant_system.size + translator_constant_system.padding_after;
    }
  }

  uint32_t constant_position_dwords_float = uint32_t(shader_object_.size());
  if (cbuffer_index_float_constants_ != kBindingIndexUnallocated) {
    assert_not_zero(constant_register_map.float_count);
    shader_object_.resize(constant_position_dwords_float +
                          sizeof(dxbc::RdefVariable) / sizeof(uint32_t));
    auto& constant_float = *reinterpret_cast<dxbc::RdefVariable*>(shader_object_.data() +
                                                                  constant_position_dwords_float);
    constant_float.name_ptr = constant_name_ptr_float;
    constant_float.size_bytes = sizeof(float) * 4 * constant_register_map.float_count;
    constant_float.flags = dxbc::kRdefVariableFlagUsed;
    constant_float.type_ptr =
        types_ptr + sizeof(dxbc::RdefType) * uint32_t(ShaderRdefTypeIndex::kFloat4ConstantArray);
    constant_float.start_texture = UINT32_MAX;
    constant_float.start_sampler = UINT32_MAX;
  }

  uint32_t constant_position_dwords_bool_loop = uint32_t(shader_object_.size());
  if (cbuffer_index_bool_loop_constants_ != kBindingIndexUnallocated) {
    shader_object_.resize(constant_position_dwords_bool_loop +
                          sizeof(dxbc::RdefVariable) / sizeof(uint32_t) * 2);
    auto constants_bool_loop = reinterpret_cast<dxbc::RdefVariable*>(
        shader_object_.data() + constant_position_dwords_bool_loop);

    constants_bool_loop[0].name_ptr = constant_name_ptr_bool;
    constants_bool_loop[0].size_bytes = sizeof(uint32_t) * 4 * 2;
    for (size_t i = 0; i < rex::countof(constant_register_map.bool_bitmap); ++i) {
      if (constant_register_map.bool_bitmap[i]) {
        constants_bool_loop[0].flags |= dxbc::kRdefVariableFlagUsed;
        break;
      }
    }
    constants_bool_loop[0].type_ptr =
        types_ptr + sizeof(dxbc::RdefType) * uint32_t(ShaderRdefTypeIndex::kUint4Array2);
    constants_bool_loop[0].start_texture = UINT32_MAX;
    constants_bool_loop[0].start_sampler = UINT32_MAX;

    constants_bool_loop[1].name_ptr = constant_name_ptr_loop;
    constants_bool_loop[1].start_offset_bytes = sizeof(uint32_t) * 4 * 2;
    constants_bool_loop[1].size_bytes = sizeof(uint32_t) * 4 * 8;
    constants_bool_loop[1].flags =
        constant_register_map.loop_bitmap ? dxbc::kRdefVariableFlagUsed : 0;
    constants_bool_loop[1].type_ptr =
        types_ptr + sizeof(dxbc::RdefType) * uint32_t(ShaderRdefTypeIndex::kUint4Array8);
    constants_bool_loop[1].start_texture = UINT32_MAX;
    constants_bool_loop[1].start_sampler = UINT32_MAX;
  }

  uint32_t constant_position_dwords_fetch = uint32_t(shader_object_.size());
  if (cbuffer_index_fetch_constants_ != kBindingIndexUnallocated) {
    shader_object_.resize(constant_position_dwords_fetch +
                          sizeof(dxbc::RdefVariable) / sizeof(uint32_t));
    auto& constant_fetch = *reinterpret_cast<dxbc::RdefVariable*>(shader_object_.data() +
                                                                  constant_position_dwords_fetch);
    constant_fetch.name_ptr = constant_name_ptr_fetch;
    constant_fetch.size_bytes = sizeof(uint32_t) * 6 * 32;
    constant_fetch.flags = dxbc::kRdefVariableFlagUsed;
    constant_fetch.type_ptr =
        types_ptr + sizeof(dxbc::RdefType) * uint32_t(ShaderRdefTypeIndex::kUint4Array48);
    constant_fetch.start_texture = UINT32_MAX;
    constant_fetch.start_sampler = UINT32_MAX;
  }

  uint32_t constant_position_dwords_descriptor_indices = uint32_t(shader_object_.size());
  if (cbuffer_index_descriptor_indices_ != kBindingIndexUnallocated) {
    assert_not_zero(GetBindlessResourceCount());
    shader_object_.resize(constant_position_dwords_descriptor_indices +
                          sizeof(dxbc::RdefVariable) / sizeof(uint32_t));
    auto& constant_descriptor_indices = *reinterpret_cast<dxbc::RdefVariable*>(
        shader_object_.data() + constant_position_dwords_descriptor_indices);
    constant_descriptor_indices.name_ptr = constant_name_ptr_descriptor_indices;
    constant_descriptor_indices.size_bytes =
        sizeof(uint32_t) * rex::align(GetBindlessResourceCount(), uint32_t(4));
    constant_descriptor_indices.flags = dxbc::kRdefVariableFlagUsed;
    constant_descriptor_indices.type_ptr =
        types_ptr +
        sizeof(dxbc::RdefType) * uint32_t(ShaderRdefTypeIndex::kUint4DescriptorIndexArray);
    constant_descriptor_indices.start_texture = UINT32_MAX;
    constant_descriptor_indices.start_sampler = UINT32_MAX;
  }

  name_ptr = (uint32_t(shader_object_.size()) - blob_position_dwords) * sizeof(uint32_t);
  uint32_t cbuffer_name_ptr_system = name_ptr;
  if (cbuffer_index_system_constants_ != kBindingIndexUnallocated) {
    name_ptr += dxbc::AppendAlignedString(shader_object_, "xe_system_cbuffer");
  }
  uint32_t cbuffer_name_ptr_float = name_ptr;
  if (cbuffer_index_float_constants_ != kBindingIndexUnallocated) {
    name_ptr += dxbc::AppendAlignedString(shader_object_, "xe_float_cbuffer");
  }
  uint32_t cbuffer_name_ptr_bool_loop = name_ptr;
  if (cbuffer_index_bool_loop_constants_ != kBindingIndexUnallocated) {
    name_ptr += dxbc::AppendAlignedString(shader_object_, "xe_bool_loop_cbuffer");
  }
  uint32_t cbuffer_name_ptr_fetch = name_ptr;
  if (cbuffer_index_fetch_constants_ != kBindingIndexUnallocated) {
    name_ptr += dxbc::AppendAlignedString(shader_object_, "xe_fetch_cbuffer");
  }
  uint32_t cbuffer_name_ptr_descriptor_indices = name_ptr;
  if (cbuffer_index_descriptor_indices_ != kBindingIndexUnallocated) {
    name_ptr += dxbc::AppendAlignedString(shader_object_, "xe_descriptor_indices_cbuffer");
  }

  uint32_t cbuffers_position_dwords = uint32_t(shader_object_.size());
  shader_object_.resize(cbuffers_position_dwords +
                        sizeof(dxbc::RdefCbuffer) / sizeof(uint32_t) * cbuffer_count_);
  {
    auto cbuffers =
        reinterpret_cast<dxbc::RdefCbuffer*>(shader_object_.data() + cbuffers_position_dwords);
    for (uint32_t i = 0; i < cbuffer_count_; ++i) {
      dxbc::RdefCbuffer& cbuffer = cbuffers[i];
      cbuffer.type = dxbc::RdefCbufferType::kCbuffer;
      if (i == cbuffer_index_system_constants_) {
        cbuffer.name_ptr = cbuffer_name_ptr_system;
        cbuffer.variable_count = uint32_t(SystemConstants::Index::kCount);
        cbuffer.variables_ptr =
            (constant_position_dwords_system - blob_position_dwords) * sizeof(uint32_t);
        cbuffer.size_vector_aligned_bytes =
            uint32_t(rex::align(sizeof(SystemConstants), sizeof(uint32_t) * 4));
      } else if (i == cbuffer_index_float_constants_) {
        assert_not_zero(constant_register_map.float_count);
        cbuffer.name_ptr = cbuffer_name_ptr_float;
        cbuffer.variable_count = 1;
        cbuffer.variables_ptr =
            (constant_position_dwords_float - blob_position_dwords) * sizeof(uint32_t);
        cbuffer.size_vector_aligned_bytes = sizeof(float) * 4 * constant_register_map.float_count;
      } else if (i == cbuffer_index_bool_loop_constants_) {
        cbuffer.name_ptr = cbuffer_name_ptr_bool_loop;
        cbuffer.variable_count = 2;
        cbuffer.variables_ptr =
            (constant_position_dwords_bool_loop - blob_position_dwords) * sizeof(uint32_t);
        cbuffer.size_vector_aligned_bytes = sizeof(uint32_t) * 4 * (2 + 8);
      } else if (i == cbuffer_index_fetch_constants_) {
        cbuffer.name_ptr = cbuffer_name_ptr_fetch;
        cbuffer.variable_count = 1;
        cbuffer.variables_ptr =
            (constant_position_dwords_fetch - blob_position_dwords) * sizeof(uint32_t);
        cbuffer.size_vector_aligned_bytes = sizeof(uint32_t) * 6 * 32;
      } else if (i == cbuffer_index_descriptor_indices_) {
        assert_not_zero(GetBindlessResourceCount());
        cbuffer.name_ptr = cbuffer_name_ptr_descriptor_indices;
        cbuffer.variable_count = 1;
        cbuffer.variables_ptr =
            (constant_position_dwords_descriptor_indices - blob_position_dwords) * sizeof(uint32_t);
        cbuffer.size_vector_aligned_bytes =
            sizeof(uint32_t) * rex::align(GetBindlessResourceCount(), uint32_t(4));
      } else {
        assert_unhandled_case(i);
      }
    }
  }

  name_ptr = (uint32_t(shader_object_.size()) - blob_position_dwords) * sizeof(uint32_t);
  uint32_t sampler_name_ptr = name_ptr;
  if (!sampler_bindings_.empty()) {
    if (bindless_resources_used_) {
      name_ptr += dxbc::AppendAlignedString(shader_object_, "xe_samplers");
    } else {
      for (uint32_t i = 0; i < uint32_t(sampler_bindings_.size()); ++i) {
        name_ptr +=
            dxbc::AppendAlignedString(shader_object_, sampler_bindings_[i].bindful_name.c_str());
      }
    }
  }
  uint32_t shared_memory_srv_name_ptr = name_ptr;
  if (srv_index_shared_memory_ != kBindingIndexUnallocated) {
    name_ptr += dxbc::AppendAlignedString(shader_object_, "xe_shared_memory_srv");
  }
  uint32_t bindless_textures_2d_name_ptr = name_ptr;
  uint32_t bindless_textures_3d_name_ptr = name_ptr;
  uint32_t bindless_textures_cube_name_ptr = name_ptr;
  if (bindless_resources_used_) {
    if (srv_index_bindless_textures_2d_ != kBindingIndexUnallocated) {
      bindless_textures_2d_name_ptr = name_ptr;
      name_ptr += dxbc::AppendAlignedString(shader_object_, "xe_textures_2d");
    }
    if (srv_index_bindless_textures_3d_ != kBindingIndexUnallocated) {
      bindless_textures_3d_name_ptr = name_ptr;
      name_ptr += dxbc::AppendAlignedString(shader_object_, "xe_textures_3d");
    }
    if (srv_index_bindless_textures_cube_ != kBindingIndexUnallocated) {
      bindless_textures_cube_name_ptr = name_ptr;
      name_ptr += dxbc::AppendAlignedString(shader_object_, "xe_textures_cube");
    }
  } else {
    for (TextureBinding& texture_binding : texture_bindings_) {
      texture_binding.bindful_srv_rdef_name_ptr = name_ptr;
      name_ptr += dxbc::AppendAlignedString(shader_object_, texture_binding.bindful_name.c_str());
    }
  }
  uint32_t shared_memory_uav_name_ptr = name_ptr;
  if (uav_index_shared_memory_ != kBindingIndexUnallocated) {
    name_ptr += dxbc::AppendAlignedString(shader_object_, "xe_shared_memory_uav");
  }
  uint32_t edram_name_ptr = name_ptr;
  if (uav_index_edram_ != kBindingIndexUnallocated) {
    name_ptr += dxbc::AppendAlignedString(shader_object_, "xe_edram");
  }
  uint32_t zpd_counter_name_ptr = name_ptr;
  if (uav_index_zpd_counter_ != kBindingIndexUnallocated) {
    name_ptr += dxbc::AppendAlignedString(shader_object_, "xe_zpd_counter_uav");
  }

  uint32_t bindings_position_dwords = uint32_t(shader_object_.size());

  if (!sampler_bindings_.empty()) {
    uint32_t samplers_position_dwords = uint32_t(shader_object_.size());
    shader_object_.resize(samplers_position_dwords +
                          sizeof(dxbc::RdefInputBind) / sizeof(uint32_t) *
                              (bindless_resources_used_ ? 1 : sampler_bindings_.size()));
    auto samplers =
        reinterpret_cast<dxbc::RdefInputBind*>(shader_object_.data() + samplers_position_dwords);
    if (bindless_resources_used_) {
      samplers[0].name_ptr = sampler_name_ptr;
      samplers[0].type = dxbc::RdefInputType::kSampler;
    } else {
      uint32_t sampler_current_name_ptr = sampler_name_ptr;
      for (size_t i = 0; i < sampler_bindings_.size(); ++i) {
        dxbc::RdefInputBind& sampler = samplers[i];
        sampler.name_ptr = sampler_current_name_ptr;
        sampler.type = dxbc::RdefInputType::kSampler;
        sampler.bind_point = uint32_t(i);
        sampler.bind_count = 1;
        sampler.id = uint32_t(i);
        sampler_current_name_ptr +=
            dxbc::GetAlignedStringLength(sampler_bindings_[i].bindful_name.c_str());
      }
    }
  }

  uint32_t srvs_position_dwords = uint32_t(shader_object_.size());
  shader_object_.resize(srvs_position_dwords +
                        sizeof(dxbc::RdefInputBind) / sizeof(uint32_t) * srv_count_);
  {
    auto srvs =
        reinterpret_cast<dxbc::RdefInputBind*>(shader_object_.data() + srvs_position_dwords);
    for (uint32_t i = 0; i < srv_count_; ++i) {
      dxbc::RdefInputBind& srv = srvs[i];
      srv.id = i;
      if (i == srv_index_shared_memory_) {
        srv.name_ptr = shared_memory_srv_name_ptr;
        srv.type = dxbc::RdefInputType::kByteAddress;
        srv.return_type = dxbc::ResourceReturnType::kMixed;
        srv.dimension = dxbc::RdefDimension::kSRVBuffer;
        srv.bind_point = uint32_t(SRVMainRegister::kSharedMemory);
        srv.bind_count = 1;
        srv.bind_point_space = uint32_t(SRVSpace::kMain);
      } else {
        srv.type = dxbc::RdefInputType::kTexture;
        srv.return_type = dxbc::ResourceReturnType::kFloat;
        srv.sample_count = UINT32_MAX;
        srv.flags = dxbc::kRdefInputFlags4Component;
        if (bindless_resources_used_) {
          if (i == srv_index_bindless_textures_3d_) {
            srv.name_ptr = bindless_textures_3d_name_ptr;
            srv.dimension = dxbc::RdefDimension::kSRVTexture3D;
            srv.bind_point_space = uint32_t(SRVSpace::kBindlessTextures3D);
          } else if (i == srv_index_bindless_textures_cube_) {
            srv.name_ptr = bindless_textures_cube_name_ptr;
            srv.dimension = dxbc::RdefDimension::kSRVTextureCube;
            srv.bind_point_space = uint32_t(SRVSpace::kBindlessTexturesCube);
          } else {
            assert_true(i == srv_index_bindless_textures_2d_);
            srv.name_ptr = bindless_textures_2d_name_ptr;
            srv.dimension = dxbc::RdefDimension::kSRVTexture2DArray;
            srv.bind_point_space = uint32_t(SRVSpace::kBindlessTextures2DArray);
          }
        } else {
          auto it = texture_bindings_for_bindful_srv_indices_.find(i);
          assert_true(it != texture_bindings_for_bindful_srv_indices_.end());
          uint32_t texture_binding_index = it->second;
          const TextureBinding& texture_binding = texture_bindings_[texture_binding_index];
          srv.name_ptr = texture_binding.bindful_srv_rdef_name_ptr;
          switch (texture_binding.dimension) {
            case xenos::FetchOpDimension::k3DOrStacked:
              srv.dimension = dxbc::RdefDimension::kSRVTexture3D;
              break;
            case xenos::FetchOpDimension::kCube:
              srv.dimension = dxbc::RdefDimension::kSRVTextureCube;
              break;
            default:
              assert_true(texture_binding.dimension == xenos::FetchOpDimension::k2D);
              srv.dimension = dxbc::RdefDimension::kSRVTexture2DArray;
          }
          srv.bind_point = uint32_t(SRVMainRegister::kBindfulTexturesStart) + texture_binding_index;
          srv.bind_count = 1;
          srv.bind_point_space = uint32_t(SRVSpace::kMain);
        }
      }
    }
  }

  uint32_t uavs_position_dwords = uint32_t(shader_object_.size());
  shader_object_.resize(uavs_position_dwords +
                        sizeof(dxbc::RdefInputBind) / sizeof(uint32_t) * uav_count_);
  {
    auto uavs =
        reinterpret_cast<dxbc::RdefInputBind*>(shader_object_.data() + uavs_position_dwords);
    for (uint32_t i = 0; i < uav_count_; ++i) {
      dxbc::RdefInputBind& uav = uavs[i];
      uav.bind_count = 1;
      uav.id = i;
      if (i == uav_index_shared_memory_) {
        uav.name_ptr = shared_memory_uav_name_ptr;
        uav.type = dxbc::RdefInputType::kUAVRWByteAddress;
        uav.return_type = dxbc::ResourceReturnType::kMixed;
        uav.dimension = dxbc::RdefDimension::kUAVBuffer;
        uav.bind_point = uint32_t(UAVRegister::kSharedMemory);
      } else if (i == uav_index_edram_) {
        uav.name_ptr = edram_name_ptr;
        uav.type = dxbc::RdefInputType::kUAVRWTyped;
        uav.return_type = dxbc::ResourceReturnType::kUInt;
        uav.dimension = dxbc::RdefDimension::kUAVBuffer;
        uav.sample_count = UINT32_MAX;
        uav.bind_point = uint32_t(UAVRegister::kEdram);
      } else if (i == uav_index_zpd_counter_) {
        uav.name_ptr = zpd_counter_name_ptr;
        uav.type = dxbc::RdefInputType::kUAVRWByteAddress;
        uav.return_type = dxbc::ResourceReturnType::kMixed;
        uav.dimension = dxbc::RdefDimension::kUAVBuffer;
        uav.bind_point = uint32_t(UAVRegister::kZpdCounter);
      } else {
        assert_unhandled_case(i);
      }
    }
  }

  uint32_t cbuffer_binding_position_dwords = uint32_t(shader_object_.size());
  shader_object_.resize(cbuffer_binding_position_dwords +
                        sizeof(dxbc::RdefInputBind) / sizeof(uint32_t) * cbuffer_count_);
  {
    auto cbuffers = reinterpret_cast<dxbc::RdefInputBind*>(shader_object_.data() +
                                                           cbuffer_binding_position_dwords);
    for (uint32_t i = 0; i < cbuffer_count_; ++i) {
      dxbc::RdefInputBind& cbuffer = cbuffers[i];
      cbuffer.type = dxbc::RdefInputType::kCbuffer;
      cbuffer.bind_count = 1;

      cbuffer.flags = dxbc::kRdefInputFlagUserPacked;
      cbuffer.id = i;
      if (i == cbuffer_index_system_constants_) {
        cbuffer.name_ptr = cbuffer_name_ptr_system;
        cbuffer.bind_point = uint32_t(CbufferRegister::kSystemConstants);
      } else if (i == cbuffer_index_float_constants_) {
        cbuffer.name_ptr = cbuffer_name_ptr_float;
        cbuffer.bind_point = uint32_t(CbufferRegister::kFloatConstants);
      } else if (i == cbuffer_index_bool_loop_constants_) {
        cbuffer.name_ptr = cbuffer_name_ptr_bool_loop;
        cbuffer.bind_point = uint32_t(CbufferRegister::kBoolLoopConstants);
      } else if (i == cbuffer_index_fetch_constants_) {
        cbuffer.name_ptr = cbuffer_name_ptr_fetch;
        cbuffer.bind_point = uint32_t(CbufferRegister::kFetchConstants);
      } else if (i == cbuffer_index_descriptor_indices_) {
        cbuffer.name_ptr = cbuffer_name_ptr_descriptor_indices;
        cbuffer.bind_point = uint32_t(CbufferRegister::kDescriptorIndices);
      } else {
        assert_unhandled_case(i);
      }
    }
  }

  uint32_t bindings_end_position_dwords = uint32_t(shader_object_.size());

  {
    auto& header =
        *reinterpret_cast<dxbc::RdefHeader*>(shader_object_.data() + blob_position_dwords);
    header.cbuffer_count = cbuffer_count_;
    header.cbuffers_ptr = (cbuffers_position_dwords - blob_position_dwords) * sizeof(uint32_t);
    header.input_bind_count = (bindings_end_position_dwords - bindings_position_dwords) *
                              sizeof(uint32_t) / sizeof(dxbc::RdefInputBind);
    header.input_binds_ptr = (bindings_position_dwords - blob_position_dwords) * sizeof(uint32_t);
    if (IsDxbcVertexShader()) {
      header.shader_model = dxbc::RdefShaderModel::kVertexShader5_1;
    } else if (IsDxbcDomainShader()) {
      header.shader_model = dxbc::RdefShaderModel::kDomainShader5_1;
    } else {
      assert_true(is_pixel_shader());
      header.shader_model = dxbc::RdefShaderModel::kPixelShader5_1;
    }
    header.compile_flags = dxbc::kCompileFlagNoPreshader | dxbc::kCompileFlagPreferFlowControl |
                           dxbc::kCompileFlagIeeeStrictness;
    if (bindless_resources_used_) {
      header.compile_flags |= dxbc::kCompileFlagEnableUnboundedDescriptorTables;
    }

    header.generator_name_ptr = sizeof(dxbc::RdefHeader);
    header.fourcc = dxbc::RdefHeader::FourCC::k5_1;
    header.InitializeSizes();
  }
}

void DxbcShaderTranslator::WriteInputSignature() {
  uint32_t blob_position = uint32_t(shader_object_.size());

  shader_object_.resize(shader_object_.size() + sizeof(dxbc::Signature) / sizeof(uint32_t));
  uint32_t parameter_count = 0;
  constexpr size_t kParameterDwords = sizeof(dxbc::SignatureParameter) / sizeof(uint32_t);

  if (IsDxbcVertexShader()) {
    size_t vertex_id_position = shader_object_.size();
    shader_object_.resize(shader_object_.size() + kParameterDwords);
    ++parameter_count;
    {
      auto& vertex_id =
          *reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() + vertex_id_position);
      vertex_id.system_value = dxbc::Name::kVertexID;
      vertex_id.component_type = dxbc::SignatureRegisterComponentType::kUInt32;
      vertex_id.register_index = kInRegisterVSVertexIndex;
      vertex_id.mask = 0b0001;
      vertex_id.always_reads_mask = (register_count() >= 1) ? 0b0001 : 0b0000;
    }

    uint32_t semantic_offset = uint32_t((shader_object_.size() - blob_position) * sizeof(uint32_t));
    {
      auto& vertex_id =
          *reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() + vertex_id_position);
      vertex_id.semantic_name_ptr = semantic_offset;
    }
    semantic_offset += dxbc::AppendAlignedString(shader_object_, "SV_VertexID");
  } else if (IsDxbcDomainShader()) {
    size_t control_point_index_position = shader_object_.size();
    shader_object_.resize(shader_object_.size() + kParameterDwords);
    ++parameter_count;
    {
      auto& control_point_index = *reinterpret_cast<dxbc::SignatureParameter*>(
          shader_object_.data() + control_point_index_position);
      control_point_index.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
      control_point_index.register_index = kInRegisterDSControlPointIndex;
      control_point_index.mask = 0b0001;
      control_point_index.always_reads_mask = in_control_point_index_used_ ? 0b0001 : 0b0000;
    }

    uint32_t semantic_offset = uint32_t((shader_object_.size() - blob_position) * sizeof(uint32_t));
    {
      auto& control_point_index = *reinterpret_cast<dxbc::SignatureParameter*>(
          shader_object_.data() + control_point_index_position);
      control_point_index.semantic_name_ptr = semantic_offset;
    }
    semantic_offset += dxbc::AppendAlignedString(shader_object_, "XEVERTEXID");
  } else if (is_pixel_shader()) {
    size_t interpolator_position = shader_object_.size();
    uint32_t interpolator_mask = GetModificationInterpolatorMask();
    uint32_t interpolator_count = rex::bit_count(interpolator_mask);
    shader_object_.resize(shader_object_.size() + interpolator_count * kParameterDwords);
    parameter_count += interpolator_count;
    {
      auto interpolators = reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() +
                                                                       interpolator_position);
      uint32_t used_interpolator_index = 0;
      uint32_t interpolators_remaining = interpolator_mask;
      uint32_t interpolator_index;
      while (rex::bit_scan_forward(interpolators_remaining, &interpolator_index)) {
        interpolators_remaining &= ~(UINT32_C(1) << interpolator_index);
        dxbc::SignatureParameter& interpolator = interpolators[used_interpolator_index];
        interpolator.semantic_index = used_interpolator_index;
        interpolator.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
        interpolator.register_index = in_reg_ps_interpolators_ + used_interpolator_index;
        interpolator.mask = 0b1111;
        interpolator.always_reads_mask = interpolator_index < register_count() ? 0b1111 : 0b0000;
        ++used_interpolator_index;
      }
    }

    size_t point_coordinates_position = shader_object_.size();
    if (in_reg_ps_point_coordinates_ != UINT32_MAX) {
      shader_object_.resize(shader_object_.size() + kParameterDwords);
      ++parameter_count;
      {
        auto& point_coordinates = *reinterpret_cast<dxbc::SignatureParameter*>(
            shader_object_.data() + point_coordinates_position);
        point_coordinates.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
        point_coordinates.register_index = in_reg_ps_point_coordinates_;
        point_coordinates.mask = 0b0011;
        point_coordinates.always_reads_mask = 0b0011;
      }
    }

    size_t position_position = shader_object_.size();
    shader_object_.resize(shader_object_.size() + kParameterDwords);
    ++parameter_count;
    {
      auto& position =
          *reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() + position_position);
      position.system_value = dxbc::Name::kPosition;
      position.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
      position.register_index = in_reg_ps_position_;
      position.mask = 0b1111;
      position.always_reads_mask = in_position_used_;
    }

    size_t is_front_face_position = shader_object_.size();
    shader_object_.resize(shader_object_.size() + kParameterDwords);
    ++parameter_count;
    {
      auto& is_front_face = *reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() +
                                                                         is_front_face_position);
      is_front_face.system_value = dxbc::Name::kIsFrontFace;
      is_front_face.component_type = dxbc::SignatureRegisterComponentType::kUInt32;
      is_front_face.register_index = in_reg_ps_front_face_sample_index_;
      is_front_face.mask = 0b0001;
      is_front_face.always_reads_mask = in_front_face_used_ ? 0b0001 : 0b0000;
    }

    size_t sample_index_position = SIZE_MAX;
    if ((current_shader().memexport_eM_written() || GetDxbcShaderModification().pixel.zpd_total) &&
        IsSampleRate()) {
      sample_index_position = shader_object_.size();
      shader_object_.resize(shader_object_.size() + kParameterDwords);
      ++parameter_count;
      {
        auto& sample_index = *reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() +
                                                                          sample_index_position);
        sample_index.system_value = dxbc::Name::kSampleIndex;
        sample_index.component_type = dxbc::SignatureRegisterComponentType::kUInt32;
        sample_index.register_index = in_reg_ps_front_face_sample_index_;
        sample_index.mask = 0b0010;
        sample_index.always_reads_mask = 0b0010;
      }
    }

    uint32_t semantic_offset = uint32_t((shader_object_.size() - blob_position) * sizeof(uint32_t));
    if (interpolator_count) {
      auto interpolators = reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() +
                                                                       interpolator_position);
      for (uint32_t i = 0; i < interpolator_count; ++i) {
        interpolators[i].semantic_name_ptr = semantic_offset;
      }
      semantic_offset += dxbc::AppendAlignedString(shader_object_, "TEXCOORD");
    }
    if (in_reg_ps_point_coordinates_ != UINT32_MAX) {
      auto& point_coordinates = *reinterpret_cast<dxbc::SignatureParameter*>(
          shader_object_.data() + point_coordinates_position);
      point_coordinates.semantic_name_ptr = semantic_offset;
      semantic_offset += dxbc::AppendAlignedString(shader_object_, "XESPRITETEXCOORD");
    }
    {
      auto& position =
          *reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() + position_position);
      position.semantic_name_ptr = semantic_offset;
    }
    semantic_offset += dxbc::AppendAlignedString(shader_object_, "SV_Position");
    {
      auto& is_front_face = *reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() +
                                                                         is_front_face_position);
      is_front_face.semantic_name_ptr = semantic_offset;
    }
    semantic_offset += dxbc::AppendAlignedString(shader_object_, "SV_IsFrontFace");
    if (sample_index_position != SIZE_MAX) {
      {
        auto& sample_index = *reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() +
                                                                          sample_index_position);
        sample_index.semantic_name_ptr = semantic_offset;
      }
      semantic_offset += dxbc::AppendAlignedString(shader_object_, "SV_SampleIndex");
    }
  }

  {
    auto& header = *reinterpret_cast<dxbc::Signature*>(shader_object_.data() + blob_position);
    header.parameter_count = parameter_count;
    header.parameter_info_ptr = sizeof(dxbc::Signature);
  }
}

void DxbcShaderTranslator::WritePatchConstantSignature() {
  assert_true(IsDxbcDomainShader());

  uint32_t blob_position = uint32_t(shader_object_.size());

  shader_object_.resize(shader_object_.size() + sizeof(dxbc::Signature) / sizeof(uint32_t));
  uint32_t parameter_count = 0;
  constexpr size_t kParameterDwords = sizeof(dxbc::SignatureParameter) / sizeof(uint32_t);

  uint32_t tess_factor_edge_count = 0;
  dxbc::Name tess_factor_edge_system_value = dxbc::Name::kUndefined;
  uint32_t tess_factor_inside_count = 0;
  dxbc::Name tess_factor_inside_system_value = dxbc::Name::kUndefined;
  Shader::HostVertexShaderType host_vertex_shader_type =
      GetDxbcShaderModification().vertex.host_vertex_shader_type;
  switch (host_vertex_shader_type) {
    case Shader::HostVertexShaderType::kTriangleDomainCPIndexed:
    case Shader::HostVertexShaderType::kTriangleDomainPatchIndexed:
      tess_factor_edge_count = 3;
      tess_factor_edge_system_value = dxbc::Name::kFinalTriEdgeTessFactor;
      tess_factor_inside_count = 1;
      tess_factor_inside_system_value = dxbc::Name::kFinalTriInsideTessFactor;
      break;
    case Shader::HostVertexShaderType::kQuadDomainCPIndexed:
    case Shader::HostVertexShaderType::kQuadDomainPatchIndexed:
      tess_factor_edge_count = 4;
      tess_factor_edge_system_value = dxbc::Name::kFinalQuadEdgeTessFactor;
      tess_factor_inside_count = 2;
      tess_factor_inside_system_value = dxbc::Name::kFinalQuadInsideTessFactor;
      break;
    default:

      assert_unhandled_case(host_vertex_shader_type);
      EmitTranslationError("Unsupported host vertex shader type in WritePatchConstantSignature");
  }

  size_t tess_factor_edge_position = shader_object_.size();
  shader_object_.resize(shader_object_.size() + tess_factor_edge_count * kParameterDwords);
  parameter_count += tess_factor_edge_count;
  {
    auto tess_factors_edge = reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() +
                                                                         tess_factor_edge_position);
    for (uint32_t i = 0; i < tess_factor_edge_count; ++i) {
      dxbc::SignatureParameter& tess_factor_edge = tess_factors_edge[i];
      tess_factor_edge.semantic_index = i;
      tess_factor_edge.system_value = tess_factor_edge_system_value;
      tess_factor_edge.component_type = dxbc::SignatureRegisterComponentType::kFloat32;

      tess_factor_edge.register_index = i;
      tess_factor_edge.mask = 0b0001;
    }
  }

  size_t tess_factor_inside_position = shader_object_.size();
  shader_object_.resize(shader_object_.size() + tess_factor_inside_count * kParameterDwords);
  parameter_count += tess_factor_inside_count;
  {
    auto tess_factors_inside = reinterpret_cast<dxbc::SignatureParameter*>(
        shader_object_.data() + tess_factor_inside_position);
    for (uint32_t i = 0; i < tess_factor_inside_count; ++i) {
      dxbc::SignatureParameter& tess_factor_inside = tess_factors_inside[i];
      tess_factor_inside.semantic_index = i;
      tess_factor_inside.system_value = tess_factor_inside_system_value;
      tess_factor_inside.component_type = dxbc::SignatureRegisterComponentType::kFloat32;

      tess_factor_inside.register_index = tess_factor_edge_count + i;
      tess_factor_inside.mask = 0b0001;
    }
  }

  uint32_t semantic_offset = uint32_t((shader_object_.size() - blob_position) * sizeof(uint32_t));
  {
    auto tess_factors_edge = reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() +
                                                                         tess_factor_edge_position);
    for (uint32_t i = 0; i < tess_factor_edge_count; ++i) {
      tess_factors_edge[i].semantic_name_ptr = semantic_offset;
    }
  }
  semantic_offset += dxbc::AppendAlignedString(shader_object_, "SV_TessFactor");
  {
    auto tess_factors_inside = reinterpret_cast<dxbc::SignatureParameter*>(
        shader_object_.data() + tess_factor_inside_position);
    for (uint32_t i = 0; i < tess_factor_inside_count; ++i) {
      tess_factors_inside[i].semantic_name_ptr = semantic_offset;
    }
  }
  semantic_offset += dxbc::AppendAlignedString(shader_object_, "SV_InsideTessFactor");

  {
    auto& header = *reinterpret_cast<dxbc::Signature*>(shader_object_.data() + blob_position);
    header.parameter_count = parameter_count;
    header.parameter_info_ptr = sizeof(dxbc::Signature);
  }
}

void DxbcShaderTranslator::WriteOutputSignature() {
  uint32_t blob_position = uint32_t(shader_object_.size());

  shader_object_.resize(shader_object_.size() + sizeof(dxbc::Signature) / sizeof(uint32_t));
  uint32_t parameter_count = 0;
  constexpr size_t kParameterDwords = sizeof(dxbc::SignatureParameter) / sizeof(uint32_t);

  Modification shader_modification = GetDxbcShaderModification();

  if (is_vertex_shader()) {
    size_t interpolator_position = shader_object_.size();
    uint32_t interpolator_count = rex::bit_count(GetModificationInterpolatorMask());
    shader_object_.resize(shader_object_.size() + interpolator_count * kParameterDwords);
    parameter_count += interpolator_count;
    {
      auto interpolators = reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() +
                                                                       interpolator_position);
      for (uint32_t i = 0; i < interpolator_count; ++i) {
        dxbc::SignatureParameter& interpolator = interpolators[i];
        interpolator.semantic_index = i;
        interpolator.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
        interpolator.register_index = out_reg_vs_interpolators_ + i;
        interpolator.mask = 0b1111;
      }
    }

    size_t position_position = shader_object_.size();
    shader_object_.resize(shader_object_.size() + kParameterDwords);
    ++parameter_count;
    {
      auto& position =
          *reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() + position_position);
      position.system_value = dxbc::Name::kPosition;
      position.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
      position.register_index = out_reg_vs_position_;
      position.mask = 0b1111;
    }

    size_t clip_and_cull_distance_position = shader_object_.size();
    uint32_t clip_distance_count = shader_modification.GetVertexClipDistanceCount();
    uint32_t cull_distance_count = shader_modification.GetVertexCullDistanceCount();
    uint32_t clip_and_cull_distance_count = clip_distance_count + cull_distance_count;
    uint32_t clip_distance_parameter_count = 0;
    uint32_t cull_distance_parameter_count = 0;
    for (uint32_t i = 0; i < clip_and_cull_distance_count; i += 4) {
      uint32_t clip_cull_distance_register = out_reg_vs_clip_cull_distances_ + (i >> 2);
      if (i < clip_distance_count) {
        shader_object_.resize(shader_object_.size() + kParameterDwords);
        ++parameter_count;
        {
          auto& clip_distance = *reinterpret_cast<dxbc::SignatureParameter*>(
              shader_object_.data() + (shader_object_.size() - kParameterDwords));
          clip_distance.semantic_index = clip_distance_parameter_count;
          clip_distance.system_value = dxbc::Name::kClipDistance;
          clip_distance.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
          clip_distance.register_index = clip_cull_distance_register;
          uint8_t clip_distance_mask =
              (UINT8_C(1) << std::min(clip_distance_count - i, UINT32_C(4))) - 1;
          clip_distance.mask = clip_distance_mask;
          clip_distance.never_writes_mask = clip_distance_mask ^ 0b1111;
        }
        ++clip_distance_parameter_count;
      }
      if (cull_distance_count && i + 4 > clip_distance_count) {
        shader_object_.resize(shader_object_.size() + kParameterDwords);
        ++parameter_count;
        {
          auto& cull_distance = *reinterpret_cast<dxbc::SignatureParameter*>(
              shader_object_.data() + (shader_object_.size() - kParameterDwords));
          cull_distance.semantic_index = cull_distance_parameter_count;
          cull_distance.system_value = dxbc::Name::kCullDistance;
          cull_distance.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
          cull_distance.register_index = clip_cull_distance_register;
          uint8_t cull_distance_mask =
              (UINT8_C(1) << std::min(cull_distance_count - i, UINT32_C(4))) - 1;
          if (i < clip_distance_count) {
            cull_distance_mask &= ~((UINT8_C(1) << (clip_distance_count - i)) - 1);
          }
          cull_distance.mask = cull_distance_mask;
          cull_distance.never_writes_mask = cull_distance_mask ^ 0b1111;
        }
        ++cull_distance_parameter_count;
      }
    }

    size_t point_size_position = shader_object_.size();
    if (out_reg_vs_point_size_ != UINT32_MAX) {
      shader_object_.resize(shader_object_.size() + kParameterDwords);
      ++parameter_count;
      {
        auto& point_size = *reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() +
                                                                        point_size_position);
        point_size.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
        point_size.register_index = out_reg_vs_point_size_;
        point_size.mask = 0b0001;
        point_size.never_writes_mask = 0b1110;
      }
    }

    uint32_t semantic_offset = uint32_t((shader_object_.size() - blob_position) * sizeof(uint32_t));
    if (interpolator_count) {
      {
        auto interpolators = reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() +
                                                                         interpolator_position);
        for (uint32_t i = 0; i < interpolator_count; ++i) {
          interpolators[i].semantic_name_ptr = semantic_offset;
        }
      }
      semantic_offset += dxbc::AppendAlignedString(shader_object_, "TEXCOORD");
    }
    {
      auto& position =
          *reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() + position_position);
      position.semantic_name_ptr = semantic_offset;
    }
    semantic_offset += dxbc::AppendAlignedString(shader_object_, "SV_Position");
    if (clip_distance_parameter_count) {
      {
        auto clip_distances = reinterpret_cast<dxbc::SignatureParameter*>(
            shader_object_.data() + clip_and_cull_distance_position);
        for (uint32_t i = 0; i < clip_distance_parameter_count; ++i) {
          clip_distances[i].semantic_name_ptr = semantic_offset;
        }
      }
      semantic_offset += dxbc::AppendAlignedString(shader_object_, "SV_ClipDistance");
    }
    if (cull_distance_parameter_count) {
      {
        auto cull_distances = reinterpret_cast<dxbc::SignatureParameter*>(
                                  shader_object_.data() + clip_and_cull_distance_position) +
                              clip_distance_parameter_count;
        for (uint32_t i = 0; i < cull_distance_parameter_count; ++i) {
          cull_distances[i].semantic_name_ptr = semantic_offset;
        }
      }
      semantic_offset += dxbc::AppendAlignedString(shader_object_, "SV_CullDistance");
    }
    if (out_reg_vs_point_size_ != UINT32_MAX) {
      {
        auto& point_size = *reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() +
                                                                        point_size_position);
        point_size.semantic_name_ptr = semantic_offset;
      }
      semantic_offset += dxbc::AppendAlignedString(shader_object_, "XEPSIZE");
    }
  } else if (is_pixel_shader()) {
    if (!edram_rov_used_) {
      uint32_t color_targets_written = current_shader().writes_color_targets();

      size_t target_position = SIZE_MAX;
      uint32_t color_targets_written_count = rex::bit_count(color_targets_written);
      if (color_targets_written) {
        target_position = shader_object_.size();
        shader_object_.resize(shader_object_.size() +
                              color_targets_written_count * kParameterDwords);
        parameter_count += color_targets_written_count;
        auto targets =
            reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() + target_position);
        uint32_t target_index = 0;
        for (uint32_t i = 0; i < xenos::kMaxColorRenderTargets; ++i) {
          if (!(color_targets_written & (uint32_t(1) << i))) {
            continue;
          }
          dxbc::SignatureParameter& target = targets[target_index++];
          target.semantic_index = i;
          target.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
          target.register_index = i;
          target.mask = 0b1111;
        }
      }

      size_t coverage_position = SIZE_MAX;
      if ((color_targets_written & 0b1) && !IsForceEarlyDepthStencilGlobalFlagEnabled()) {
        coverage_position = shader_object_.size();
        shader_object_.resize(shader_object_.size() + kParameterDwords);
        ++parameter_count;
        auto& coverage =
            *reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() + coverage_position);
        coverage.component_type = dxbc::SignatureRegisterComponentType::kUInt32;
        coverage.register_index = UINT32_MAX;
        coverage.mask = 0b0001;
        coverage.never_writes_mask = 0b1110;
      }

      size_t depth_position = SIZE_MAX;
      if (current_shader().writes_depth() || DSV_IsWritingFloat24Depth()) {
        depth_position = shader_object_.size();
        shader_object_.resize(shader_object_.size() + kParameterDwords);
        ++parameter_count;
        auto& depth =
            *reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() + depth_position);
        depth.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
        depth.register_index = UINT32_MAX;
        depth.mask = 0b0001;
        depth.never_writes_mask = 0b1110;
      }

      uint32_t semantic_offset =
          uint32_t((shader_object_.size() - blob_position) * sizeof(uint32_t));
      if (target_position != SIZE_MAX) {
        {
          auto targets =
              reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() + target_position);
          for (uint32_t i = 0; i < color_targets_written_count; ++i) {
            targets[i].semantic_name_ptr = semantic_offset;
          }
        }
        semantic_offset += dxbc::AppendAlignedString(shader_object_, "SV_Target");
      }
      if (coverage_position != SIZE_MAX) {
        {
          auto& coverage = *reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() +
                                                                        coverage_position);
          coverage.semantic_name_ptr = semantic_offset;
        }
        semantic_offset += dxbc::AppendAlignedString(shader_object_, "SV_Coverage");
      }
      if (depth_position != SIZE_MAX) {
        {
          auto& depth =
              *reinterpret_cast<dxbc::SignatureParameter*>(shader_object_.data() + depth_position);
          depth.semantic_name_ptr = semantic_offset;
        }
        const char* depth_semantic_name;
        if (!current_shader().writes_depth() &&
            shader_modification.pixel.depth_stencil_mode ==
                Modification::DepthStencilMode::kFloat24Truncating) {
          depth_semantic_name = "SV_DepthLessEqual";
        } else {
          depth_semantic_name = "SV_Depth";
        }
        semantic_offset += dxbc::AppendAlignedString(shader_object_, depth_semantic_name);
      }
    }
  }

  {
    auto& header = *reinterpret_cast<dxbc::Signature*>(shader_object_.data() + blob_position);
    header.parameter_count = parameter_count;
    header.parameter_info_ptr = sizeof(dxbc::Signature);
  }
}

void DxbcShaderTranslator::WriteShaderCode() {
  uint32_t blob_position_dwords = uint32_t(shader_object_.size());

  dxbc::ProgramType program_type;
  if (IsDxbcVertexShader()) {
    program_type = dxbc::ProgramType::kVertexShader;
  } else if (IsDxbcDomainShader()) {
    program_type = dxbc::ProgramType::kDomainShader;
  } else {
    assert_true(is_pixel_shader());
    program_type = dxbc::ProgramType::kPixelShader;
  }
  shader_object_.push_back(dxbc::VersionToken(program_type, 5, 1));

  shader_object_.push_back(0);

  Modification shader_modification = GetDxbcShaderModification();

  uint32_t control_point_count = 1;
  if (IsDxbcDomainShader()) {
    dxbc::TessellatorDomain tessellator_domain = dxbc::TessellatorDomain::kTriangle;
    switch (shader_modification.vertex.host_vertex_shader_type) {
      case Shader::HostVertexShaderType::kTriangleDomainCPIndexed:
        control_point_count = 3;
        tessellator_domain = dxbc::TessellatorDomain::kTriangle;
        break;
      case Shader::HostVertexShaderType::kTriangleDomainPatchIndexed:
        control_point_count = 1;
        tessellator_domain = dxbc::TessellatorDomain::kTriangle;
        break;
      case Shader::HostVertexShaderType::kQuadDomainCPIndexed:
        control_point_count = 4;
        tessellator_domain = dxbc::TessellatorDomain::kQuad;
        break;
      case Shader::HostVertexShaderType::kQuadDomainPatchIndexed:
        control_point_count = 1;
        tessellator_domain = dxbc::TessellatorDomain::kQuad;
        break;
      default:

        assert_unhandled_case(shader_modification.vertex.host_vertex_shader_type);
        EmitTranslationError("Unsupported host vertex shader type in WriteShaderCode");
    }
    ao_.OpDclInputControlPointCount(control_point_count);
    ao_.OpDclTessDomain(tessellator_domain);
  }

  bool global_flag_force_early_depth_stencil = IsForceEarlyDepthStencilGlobalFlagEnabled();
  ao_.OpDclGlobalFlags(
      global_flag_force_early_depth_stencil ? dxbc::kGlobalFlagForceEarlyDepthStencil : 0);

  if (cbuffer_index_float_constants_ != kBindingIndexUnallocated) {
    const Shader::ConstantRegisterMap& constant_register_map =
        current_shader().constant_register_map();
    assert_not_zero(constant_register_map.float_count);
    ao_.OpDclConstantBuffer(dxbc::Src::CB(dxbc::Src::Dcl, cbuffer_index_float_constants_,
                                          uint32_t(CbufferRegister::kFloatConstants),
                                          uint32_t(CbufferRegister::kFloatConstants)),
                            constant_register_map.float_count,
                            constant_register_map.float_dynamic_addressing
                                ? dxbc::ConstantBufferAccessPattern::kDynamicIndexed
                                : dxbc::ConstantBufferAccessPattern::kImmediateIndexed);
  }
  if (cbuffer_index_system_constants_ != kBindingIndexUnallocated) {
    ao_.OpDclConstantBuffer(dxbc::Src::CB(dxbc::Src::Dcl, cbuffer_index_system_constants_,
                                          uint32_t(CbufferRegister::kSystemConstants),
                                          uint32_t(CbufferRegister::kSystemConstants)),
                            (sizeof(SystemConstants) + 15) >> 4);
  }
  if (cbuffer_index_fetch_constants_ != kBindingIndexUnallocated) {
    ao_.OpDclConstantBuffer(dxbc::Src::CB(dxbc::Src::Dcl, cbuffer_index_fetch_constants_,
                                          uint32_t(CbufferRegister::kFetchConstants),
                                          uint32_t(CbufferRegister::kFetchConstants)),
                            48);
  }
  if (cbuffer_index_descriptor_indices_ != kBindingIndexUnallocated) {
    assert_not_zero(GetBindlessResourceCount());
    ao_.OpDclConstantBuffer(dxbc::Src::CB(dxbc::Src::Dcl, cbuffer_index_descriptor_indices_,
                                          uint32_t(CbufferRegister::kDescriptorIndices),
                                          uint32_t(CbufferRegister::kDescriptorIndices)),
                            (GetBindlessResourceCount() + 3) >> 2);
  }
  if (cbuffer_index_bool_loop_constants_ != kBindingIndexUnallocated) {
    ao_.OpDclConstantBuffer(dxbc::Src::CB(dxbc::Src::Dcl, cbuffer_index_bool_loop_constants_,
                                          uint32_t(CbufferRegister::kBoolLoopConstants),
                                          uint32_t(CbufferRegister::kBoolLoopConstants)),
                            2 + 8);
  }

  if (!sampler_bindings_.empty()) {
    if (bindless_resources_used_) {
      ao_.OpDclSampler(dxbc::Src::S(dxbc::Src::Dcl, 0, 0, UINT32_MAX));
    } else {
      for (uint32_t i = 0; i < uint32_t(sampler_bindings_.size()); ++i) {
        const SamplerBinding& sampler_binding = sampler_bindings_[i];
        ao_.OpDclSampler(dxbc::Src::S(dxbc::Src::Dcl, i, i, i));
      }
    }
  }

  for (uint32_t i = 0; i < srv_count_; ++i) {
    if (i == srv_index_shared_memory_) {
      ao_.OpDclResourceRaw(dxbc::Src::T(dxbc::Src::Dcl, srv_index_shared_memory_,
                                        uint32_t(SRVMainRegister::kSharedMemory),
                                        uint32_t(SRVMainRegister::kSharedMemory)),
                           uint32_t(SRVSpace::kMain));
    } else {
      dxbc::ResourceDimension texture_dimension;
      uint32_t texture_register_lower_bound, texture_register_upper_bound;
      SRVSpace texture_register_space;
      if (bindless_resources_used_) {
        texture_register_lower_bound = 0;
        texture_register_upper_bound = UINT32_MAX;
        if (i == srv_index_bindless_textures_3d_) {
          texture_dimension = dxbc::ResourceDimension::kTexture3D;
          texture_register_space = SRVSpace::kBindlessTextures3D;
        } else if (i == srv_index_bindless_textures_cube_) {
          texture_dimension = dxbc::ResourceDimension::kTextureCube;
          texture_register_space = SRVSpace::kBindlessTexturesCube;
        } else {
          assert_true(i == srv_index_bindless_textures_2d_);
          texture_dimension = dxbc::ResourceDimension::kTexture2DArray;
          texture_register_space = SRVSpace::kBindlessTextures2DArray;
        }
      } else {
        auto it = texture_bindings_for_bindful_srv_indices_.find(i);
        assert_true(it != texture_bindings_for_bindful_srv_indices_.end());
        uint32_t texture_binding_index = it->second;
        const TextureBinding& texture_binding = texture_bindings_[texture_binding_index];
        switch (texture_binding.dimension) {
          case xenos::FetchOpDimension::k3DOrStacked:
            texture_dimension = dxbc::ResourceDimension::kTexture3D;
            break;
          case xenos::FetchOpDimension::kCube:
            texture_dimension = dxbc::ResourceDimension::kTextureCube;
            break;
          default:
            assert_true(texture_binding.dimension == xenos::FetchOpDimension::k2D);
            texture_dimension = dxbc::ResourceDimension::kTexture2DArray;
        }
        texture_register_lower_bound =
            uint32_t(SRVMainRegister::kBindfulTexturesStart) + texture_binding_index;
        texture_register_upper_bound = texture_register_lower_bound;
        texture_register_space = SRVSpace::kMain;
      }
      ao_.OpDclResource(texture_dimension,
                        dxbc::ResourceReturnTypeX4Token(dxbc::ResourceReturnType::kFloat),
                        dxbc::Src::T(dxbc::Src::Dcl, i, texture_register_lower_bound,
                                     texture_register_upper_bound),
                        uint32_t(texture_register_space));
    }
  }

  for (uint32_t i = 0; i < uav_count_; ++i) {
    if (i == uav_index_shared_memory_) {
      if (!is_pixel_shader()) {
        shader_feature_info_.feature_flags[0] |= dxbc::kShaderFeature0_UAVsAtEveryStage;
      }
      ao_.OpDclUnorderedAccessViewRaw(0, dxbc::Src::U(dxbc::Src::Dcl, uav_index_shared_memory_,
                                                      uint32_t(UAVRegister::kSharedMemory),
                                                      uint32_t(UAVRegister::kSharedMemory)));
    } else if (i == uav_index_edram_) {
      shader_feature_info_.feature_flags[0] |= dxbc::kShaderFeature0_ROVs;
      ao_.OpDclUnorderedAccessViewTyped(
          dxbc::ResourceDimension::kBuffer, dxbc::kUAVFlagRasterizerOrderedAccess,
          dxbc::ResourceReturnTypeX4Token(dxbc::ResourceReturnType::kUInt),
          dxbc::Src::U(dxbc::Src::Dcl, uav_index_edram_, uint32_t(UAVRegister::kEdram),
                       uint32_t(UAVRegister::kEdram)));
    } else if (i == uav_index_zpd_counter_) {
      ao_.OpDclUnorderedAccessViewRaw(
          0, dxbc::Src::U(dxbc::Src::Dcl, uav_index_zpd_counter_,
                          uint32_t(UAVRegister::kZpdCounter), uint32_t(UAVRegister::kZpdCounter)));
    } else {
      assert_unhandled_case(i);
    }
  }

  if (is_vertex_shader()) {
    if (IsDxbcDomainShader()) {
      if (in_domain_location_used_) {
        ao_.OpDclInput(dxbc::Dest::VDomain(in_domain_location_used_));
      }
      if (in_control_point_index_used_) {
        ao_.OpDclInput(
            dxbc::Dest::VICP(control_point_count, kInRegisterDSControlPointIndex, 0b0001));
      }
    } else {
      if (register_count()) {
        ao_.OpDclInputSGV(dxbc::Dest::V1D(kInRegisterVSVertexIndex, 0b0001), dxbc::Name::kVertexID);
      }
    }

    uint32_t interpolator_count = rex::bit_count(GetModificationInterpolatorMask());
    for (uint32_t i = 0; i < interpolator_count; ++i) {
      ao_.OpDclOutput(dxbc::Dest::O(out_reg_vs_interpolators_ + i));
    }

    ao_.OpDclOutputSIV(dxbc::Dest::O(out_reg_vs_position_), dxbc::Name::kPosition);

    uint32_t clip_distance_count = shader_modification.GetVertexClipDistanceCount();
    uint32_t cull_distance_count = shader_modification.GetVertexCullDistanceCount();
    uint32_t clip_and_cull_distance_count = clip_distance_count + cull_distance_count;
    for (uint32_t i = 0; i < clip_and_cull_distance_count; i += 4) {
      if (i < clip_distance_count) {
        ao_.OpDclOutputSIV(
            dxbc::Dest::O(out_reg_vs_clip_cull_distances_ + (i >> 2),
                          (UINT32_C(1) << std::min(clip_distance_count - i, UINT32_C(4))) - 1),
            dxbc::Name::kClipDistance);
      }
      if (cull_distance_count && i + 4 > clip_distance_count) {
        uint32_t cull_distance_mask =
            (UINT32_C(1) << std::min(clip_and_cull_distance_count - i, UINT32_C(4))) - 1;
        if (i < clip_distance_count) {
          cull_distance_mask &= ~((UINT32_C(1) << (clip_distance_count - i)) - 1);
        }
        ao_.OpDclOutputSIV(
            dxbc::Dest::O(out_reg_vs_clip_cull_distances_ + (i >> 2), cull_distance_mask),
            dxbc::Name::kCullDistance);
      }
    }

    if (out_reg_vs_point_size_ != UINT32_MAX) {
      ao_.OpDclOutput(dxbc::Dest::O(out_reg_vs_point_size_, 0b0001));
    }
  } else if (is_pixel_shader()) {
    bool is_writing_float24_depth = DSV_IsWritingFloat24Depth();
    bool shader_writes_depth = current_shader().writes_depth();

    uint32_t interpolator_register_index = in_reg_ps_interpolators_;
    uint32_t interpolators_remaining = GetModificationInterpolatorMask();
    uint32_t interpolator_index;
    while (rex::bit_scan_forward(interpolators_remaining, &interpolator_index)) {
      interpolators_remaining &= ~(UINT32_C(1) << interpolator_index);
      if (interpolator_index >= register_count()) {
        break;
      }
      ao_.OpDclInputPS(
          (shader_modification.pixel.interpolators_centroid & (UINT32_C(1) << interpolator_index))
              ? dxbc::InterpolationMode::kLinearCentroid
              : dxbc::InterpolationMode::kLinear,
          dxbc::Dest::V1D(interpolator_register_index));
      ++interpolator_register_index;
    }
    if (in_reg_ps_point_coordinates_ != UINT32_MAX) {
      ao_.OpDclInputPS(dxbc::InterpolationMode::kLinear,
                       dxbc::Dest::V1D(in_reg_ps_point_coordinates_, 0b0011));
    }
    if (in_position_used_) {
      ao_.OpDclInputPSSIV((is_writing_float24_depth && !shader_writes_depth)
                              ? dxbc::InterpolationMode::kLinearNoPerspectiveSample
                              : dxbc::InterpolationMode::kLinearNoPerspective,
                          dxbc::Dest::V1D(in_reg_ps_position_, in_position_used_),
                          dxbc::Name::kPosition);
    }
    bool zpd_total = GetDxbcShaderModification().pixel.zpd_total;
    bool sample_rate_sample_index =
        (current_shader().memexport_eM_written() || zpd_total) && IsSampleRate();

    assert_false(sample_rate_sample_index && edram_rov_used_);
    uint32_t front_face_and_sample_index_mask =
        uint32_t(in_front_face_used_) | (uint32_t(sample_rate_sample_index) << 1);
    if (front_face_and_sample_index_mask) {
      ao_.OpDclInputPSSGV(
          dxbc::Dest::V1D(in_reg_ps_front_face_sample_index_, front_face_and_sample_index_mask),
          dxbc::Name::kIsFrontFace);
    }
    if (edram_rov_used_ || sample_rate_sample_index || zpd_total) {
      ao_.OpDclInput(dxbc::Dest::VCoverage());
    }
    if (!edram_rov_used_) {
      uint32_t color_targets_written = current_shader().writes_color_targets();
      for (uint32_t i = 0; i < xenos::kMaxColorRenderTargets; ++i) {
        if (color_targets_written & (uint32_t(1) << i)) {
          ao_.OpDclOutput(dxbc::Dest::O(i));
        }
      }

      if ((color_targets_written & 0b1) && !global_flag_force_early_depth_stencil) {
        ao_.OpDclOutput(dxbc::Dest::OMask());
      }

      if (is_writing_float24_depth || shader_writes_depth) {
        if (!shader_writes_depth && GetDxbcShaderModification().pixel.depth_stencil_mode ==
                                        Modification::DepthStencilMode::kFloat24Truncating) {
          ao_.OpDclOutput(dxbc::Dest::ODepthLE());
        } else {
          ao_.OpDclOutput(dxbc::Dest::ODepth());
        }
      }
    }
  }

  uint32_t temp_register_count = system_temp_count_max_;
  if (!is_depth_only_pixel_shader_ && !current_shader().uses_register_dynamic_addressing()) {
    temp_register_count += register_count();
  }
  if (temp_register_count) {
    ao_.OpDclTemps(temp_register_count);
  }

  if (!is_depth_only_pixel_shader_ && current_shader().uses_register_dynamic_addressing()) {
    assert_not_zero(register_count());
    ao_.OpDclIndexableTemp(0, register_count(), 4);
  }

  size_t code_size_dwords = shader_code_.size();
  if (code_size_dwords) {
    shader_object_.resize(shader_object_.size() + code_size_dwords);
    std::memcpy(shader_object_.data() + (shader_object_.size() - code_size_dwords),
                shader_code_.data(), code_size_dwords * sizeof(uint32_t));
  }

  shader_object_[blob_position_dwords + 1] = uint32_t(shader_object_.size()) - blob_position_dwords;
}

}
