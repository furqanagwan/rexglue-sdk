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

#include <algorithm>
#include <cmath>
#include <memory>
#include <sstream>

#include <fmt/format.h>

#include <rex/assert.h>
#include <rex/cvar.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/pipeline/render_target/cache.h>
#include <rex/graphics/pipeline/shader/dxbc_translator.h>
#include <rex/math.h>
#include <rex/string.h>

REXCVAR_DEFINE_BOOL(draw_resolution_scaled_texture_offsets, true, "GPU/Shader",
                    "Scale texture offsets with draw resolution");

namespace rex::graphics {
using namespace ucode;

uint32_t DxbcShaderTranslator::FindOrAddTextureBinding(uint32_t fetch_constant,
                                                       xenos::FetchOpDimension dimension,
                                                       bool is_signed) {
  if (dimension == xenos::FetchOpDimension::k1D) {
    dimension = xenos::FetchOpDimension::k2D;
  }
  uint32_t srv_index = UINT32_MAX;
  for (uint32_t i = 0; i < uint32_t(texture_bindings_.size()); ++i) {
    const TextureBinding& texture_binding = texture_bindings_[i];
    if (texture_binding.fetch_constant == fetch_constant &&
        texture_binding.dimension == dimension && texture_binding.is_signed == is_signed) {
      return i;
    }
  }
  if (texture_bindings_.size() >= kMaxTextureBindings) {
    assert_always();
    return kMaxTextureBindings - 1;
  }
  uint32_t texture_binding_index = uint32_t(texture_bindings_.size());
  TextureBinding& new_texture_binding = texture_bindings_.emplace_back();
  if (!bindless_resources_used_) {
    new_texture_binding.bindful_srv_index = srv_count_++;
    texture_bindings_for_bindful_srv_indices_.insert(
        {new_texture_binding.bindful_srv_index, texture_binding_index});
    const char* dimension_name;
    switch (dimension) {
      case xenos::FetchOpDimension::k3DOrStacked:
        dimension_name = "3d";
        break;
      case xenos::FetchOpDimension::kCube:
        dimension_name = "cube";
        break;
      default:
        dimension_name = "2d";
    }
    new_texture_binding.bindful_name =
        fmt::format("xe_texture{}_{}_{}", fetch_constant, dimension_name, is_signed ? 's' : 'u');
  } else {
    new_texture_binding.bindful_srv_index = kBindingIndexUnallocated;
  }
  new_texture_binding.bindful_srv_rdef_name_ptr = 0;

  new_texture_binding.bindless_descriptor_index =
      bindless_resources_used_ ? GetBindlessResourceCount() : 0;
  new_texture_binding.fetch_constant = fetch_constant;
  new_texture_binding.dimension = dimension;
  new_texture_binding.is_signed = is_signed;
  return texture_binding_index;
}

uint32_t DxbcShaderTranslator::FindOrAddSamplerBinding(
    uint32_t fetch_constant, xenos::TextureFilter mag_filter, xenos::TextureFilter min_filter,
    xenos::TextureFilter mip_filter, xenos::AnisoFilter aniso_filter,
    std::optional<xenos::BorderColor> forced_border_color) {
  if (aniso_filter != xenos::AnisoFilter::kDisabled &&
      aniso_filter != xenos::AnisoFilter::kUseFetchConst) {
    mag_filter = xenos::TextureFilter::kLinear;
    min_filter = xenos::TextureFilter::kLinear;
    mip_filter = xenos::TextureFilter::kLinear;
    aniso_filter = std::min(aniso_filter, xenos::AnisoFilter::kMax_16_1);
  }
  uint32_t sampler_index = UINT32_MAX;
  for (uint32_t i = 0; i < uint32_t(sampler_bindings_.size()); ++i) {
    const SamplerBinding& sampler_binding = sampler_bindings_[i];
    if (sampler_binding.fetch_constant == fetch_constant &&
        sampler_binding.mag_filter == mag_filter && sampler_binding.min_filter == min_filter &&
        sampler_binding.mip_filter == mip_filter && sampler_binding.aniso_filter == aniso_filter &&
        sampler_binding.border_color_forced == forced_border_color.has_value() &&
        (!forced_border_color || sampler_binding.forced_border_color == *forced_border_color)) {
      return i;
    }
  }
  if (sampler_bindings_.size() >= kMaxSamplerBindings) {
    assert_always();
    return kMaxSamplerBindings - 1;
  }
  SamplerBinding& new_sampler_binding = sampler_bindings_.emplace_back();

  new_sampler_binding.bindless_descriptor_index =
      bindless_resources_used_ ? GetBindlessResourceCount() : 0;
  new_sampler_binding.fetch_constant = fetch_constant;
  new_sampler_binding.mag_filter = mag_filter;
  new_sampler_binding.min_filter = min_filter;
  new_sampler_binding.mip_filter = mip_filter;
  new_sampler_binding.aniso_filter = aniso_filter;
  new_sampler_binding.border_color_forced = forced_border_color.has_value();
  new_sampler_binding.forced_border_color =
      forced_border_color.value_or(xenos::BorderColor::k_ABGR_Black);
  if (!bindless_resources_used_) {
    std::ostringstream name;
    name << "xe_sampler" << fetch_constant;
    if (aniso_filter == xenos::AnisoFilter::kDisabled ||
        aniso_filter == xenos::AnisoFilter::kUseFetchConst) {
      static const char kFilterSuffixes[] = {'p', 'l', 'b', 'f'};
      name << '_' << kFilterSuffixes[uint32_t(mag_filter)] << kFilterSuffixes[uint32_t(min_filter)]
           << kFilterSuffixes[uint32_t(mip_filter)];
    }
    if (aniso_filter != xenos::AnisoFilter::kUseFetchConst) {
      if (aniso_filter == xenos::AnisoFilter::kDisabled) {
        name << "_a0";
      } else {
        name << "_a" << (UINT32_C(1) << (uint32_t(aniso_filter) - 1));
      }
    }
    if (forced_border_color) {
      name << (*forced_border_color == xenos::BorderColor::k_ABGR_White ? "_border_white"
                                                                        : "_border_black");
    }
    new_sampler_binding.bindful_name = name.str();
  }
  return uint32_t(sampler_bindings_.size() - 1);
}

void DxbcShaderTranslator::EmitWide1DTextureCoordinates(
    const ParsedTextureFetchInstruction& instr, const dxbc::Src& coord_operand, float offset_x,
    uint32_t tfetch_index, uint32_t coord_temp, uint32_t width_minus_1_temp, bool promoted_1d) {
  const float row_width = float(xenos::kTexture2DCubeMaxWidthHeight);
  const uint32_t padding_mask = promoted_1d ? 0b0100 : 0b0110;
  a_.OpUBFE(dxbc::Dest::R(coord_temp, 0b1000), dxbc::Src::LU(2), dxbc::Src::LU(9),
            RequestTextureFetchConstantWord(tfetch_index, 5));
  a_.OpIEq(dxbc::Dest::R(coord_temp, 0b1000), dxbc::Src::R(coord_temp, dxbc::Src::kWWWW),
           dxbc::Src::LU(uint32_t(xenos::DataDimension::k1D)));
  a_.OpIf(true, dxbc::Src::R(coord_temp, dxbc::Src::kWWWW));
  a_.OpUGE(dxbc::Dest::R(coord_temp, 0b1000), dxbc::Src::R(width_minus_1_temp, dxbc::Src::kXXXX),
           dxbc::Src::LU(xenos::kTexture2DCubeMaxWidthHeight));
  a_.OpIf(true, dxbc::Src::R(coord_temp, dxbc::Src::kWWWW));
  a_.OpIAdd(dxbc::Dest::R(coord_temp, 0b1000), dxbc::Src::R(width_minus_1_temp, dxbc::Src::kXXXX),
            dxbc::Src::LI(1));
  a_.OpUToF(dxbc::Dest::R(coord_temp, 0b1000), dxbc::Src::R(coord_temp, dxbc::Src::kWWWW));
  if (instr.attributes.unnormalized_coordinates) {
    a_.OpAdd(dxbc::Dest::R(coord_temp, 0b0010), coord_operand.SelectFromSwizzled(0),
             dxbc::Src::LF(offset_x));
  } else {
    a_.OpMAd(dxbc::Dest::R(coord_temp, 0b0010), coord_operand.SelectFromSwizzled(0),
             dxbc::Src::R(coord_temp, dxbc::Src::kWWWW), dxbc::Src::LF(offset_x));
  }
  a_.OpDiv(dxbc::Dest::R(coord_temp, 0b0100), dxbc::Src::R(coord_temp, dxbc::Src::kYYYY),
           dxbc::Src::LF(row_width));
  a_.OpRoundNI(dxbc::Dest::R(coord_temp, 0b1000), dxbc::Src::R(coord_temp, dxbc::Src::kZZZZ));
  a_.OpFrc(dxbc::Dest::R(coord_temp, 0b0001), dxbc::Src::R(coord_temp, dxbc::Src::kZZZZ));
  a_.OpIAdd(dxbc::Dest::R(coord_temp, 0b0100), dxbc::Src::R(width_minus_1_temp, dxbc::Src::kXXXX),
            dxbc::Src::LI(1));
  a_.OpUToF(dxbc::Dest::R(coord_temp, 0b0100), dxbc::Src::R(coord_temp, dxbc::Src::kZZZZ));
  a_.OpDiv(dxbc::Dest::R(coord_temp, 0b0100), dxbc::Src::R(coord_temp, dxbc::Src::kZZZZ),
           dxbc::Src::LF(row_width));
  a_.OpRoundPI(dxbc::Dest::R(coord_temp, 0b0100), dxbc::Src::R(coord_temp, dxbc::Src::kZZZZ));
  a_.OpMin(dxbc::Dest::R(coord_temp, 0b0100), dxbc::Src::R(coord_temp, dxbc::Src::kZZZZ),
           dxbc::Src::LF(float(xenos::kTexture1DWideMaxRows)));
  a_.OpAdd(dxbc::Dest::R(coord_temp, 0b1000), dxbc::Src::R(coord_temp, dxbc::Src::kWWWW),
           dxbc::Src::LF(0.5f));
  a_.OpDiv(dxbc::Dest::R(coord_temp, 0b0010), dxbc::Src::R(coord_temp, dxbc::Src::kWWWW),
           dxbc::Src::R(coord_temp, dxbc::Src::kZZZZ));
  a_.OpMov(dxbc::Dest::R(coord_temp, 0b0100), dxbc::Src::LF(0.0f));
  a_.OpElse();
  a_.OpMov(dxbc::Dest::R(coord_temp, padding_mask), dxbc::Src::LF(0.0f));
  a_.OpEndIf();
  a_.OpElse();
  a_.OpMov(dxbc::Dest::R(coord_temp, padding_mask), dxbc::Src::LF(0.0f));
  a_.OpEndIf();
}

void DxbcShaderTranslator::ProcessTextureFetchInstruction(
    const ParsedTextureFetchInstruction& original_instr) {
  ParsedTextureFetchInstruction instr = original_instr;
  const bool fetch_1d = original_instr.dimension == xenos::FetchOpDimension::k1D;
  if (fetch_1d && instr.operands[0].component_count > 1) {
    instr.dimension = xenos::FetchOpDimension::k2D;
  }
  const bool promoted_1d = fetch_1d && instr.dimension == xenos::FetchOpDimension::k2D;
  if (emit_source_map_) {
    instruction_disassembly_buffer_.Reset();
    instr.Disassemble(&instruction_disassembly_buffer_);
  }
  UpdateInstructionPredicationAndEmitDisassembly(instr.is_predicated, instr.predicate_condition);

  switch (instr.opcode) {
    case FetchOpcode::kSetTextureLod: {
      bool lod_operand_temp_pushed = false;
      a_.OpMov(
          dxbc::Dest::R(system_temp_grad_h_lod_, 0b1000),
          LoadOperand(instr.operands[0], 0b0001, lod_operand_temp_pushed).SelectFromSwizzled(0));
      if (lod_operand_temp_pushed) {
        PopSystemTemp();
      }
      return;
    }
    case FetchOpcode::kSetTextureGradientsHorz: {
      bool grad_operand_temp_pushed = false;
      a_.OpMov(dxbc::Dest::R(system_temp_grad_h_lod_, 0b0111),
               LoadOperand(instr.operands[0], 0b0111, grad_operand_temp_pushed));
      if (grad_operand_temp_pushed) {
        PopSystemTemp();
      }
      return;
    }
    case FetchOpcode::kSetTextureGradientsVert: {
      bool grad_operand_temp_pushed = false;
      a_.OpMov(dxbc::Dest::R(system_temp_grad_v_vfetch_address_, 0b0111),
               LoadOperand(instr.operands[0], 0b0111, grad_operand_temp_pushed));
      if (grad_operand_temp_pushed) {
        PopSystemTemp();
      }
      return;
    }
    default:
      break;
  }

  uint32_t used_result_components = instr.result.GetUsedResultComponents();
  uint32_t used_result_nonzero_components = instr.GetNonZeroResultComponents();

  if (instr.opcode == FetchOpcode::kGetTextureWeights) {
    used_result_nonzero_components &= ~uint32_t(0b1000);
  }
  if (!used_result_nonzero_components) {
    StoreResult(instr.result, dxbc::Src::LF(0.0f));
    return;
  }

  if (instr.opcode == FetchOpcode::kGetTextureGradients) {
    bool grad_operand_temp_pushed = false;
    dxbc::Src grad_operand =
        LoadOperand(instr.operands[0],
                    ((used_result_nonzero_components & 0b0011) ? 0b0001 : 0) |
                        ((used_result_nonzero_components & 0b1100) ? 0b0010 : 0),
                    grad_operand_temp_pushed);
    if (used_result_nonzero_components & 0b0101) {
      a_.OpDerivRTXCoarse(
          dxbc::Dest::R(system_temp_result_, used_result_nonzero_components & 0b0101),
          grad_operand.SwizzleSwizzled(0b010000));
    }
    if (used_result_nonzero_components & 0b1010) {
      a_.OpDerivRTYCoarse(
          dxbc::Dest::R(system_temp_result_, used_result_nonzero_components & 0b1010),
          grad_operand.SwizzleSwizzled(0b01000000));
    }
    if (grad_operand_temp_pushed) {
      PopSystemTemp();
    }
    StoreResult(instr.result, dxbc::Src::R(system_temp_result_));
    return;
  }

  const bool get_border_color_frac = instr.opcode == FetchOpcode::kGetTextureBorderColorFrac;
  if (get_border_color_frac && instr.dimension == xenos::FetchOpDimension::kCube) {
    StoreResult(instr.result, dxbc::Src::LF(0.0f));
    return;
  }
  if (get_border_color_frac) {
    used_result_nonzero_components = 0b1111;
  }

  if (instr.opcode != FetchOpcode::kTextureFetch &&
      instr.opcode != FetchOpcode::kGetTextureBorderColorFrac &&
      instr.opcode != FetchOpcode::kGetTextureComputedLod &&
      instr.opcode != FetchOpcode::kGetTextureWeights) {
    assert_unhandled_case(instr.opcode);
    EmitTranslationError("Unknown texture fetch operation");
    StoreResult(instr.result, dxbc::Src::LF(0.0f));
    return;
  }

  uint32_t tfetch_index = instr.operands[1].storage_index;

  bool use_computed_lod = instr.attributes.use_computed_lod &&
                          (is_pixel_shader() || instr.attributes.use_register_gradients);
  if (instr.opcode == FetchOpcode::kGetTextureComputedLod &&
      (!use_computed_lod || instr.attributes.use_register_gradients)) {
    assert_always();
    EmitTranslationError("getCompTexLOD used with explicit LOD or gradients - contradicts MSDN",
                         false);
    StoreResult(instr.result, dxbc::Src::LF(0.0f));
    return;
  }

  bool point_snap = original_instr.CanSnapToTexelCenter(use_computed_lod);

  float offsets[3] = {};

  if (instr.opcode != FetchOpcode::kGetTextureComputedLod) {
    const float rounding_offset = point_snap ? 0.0f : kTextureCoordEpsilon;
    switch (instr.dimension) {
      case xenos::FetchOpDimension::k1D:
        offsets[0] = instr.attributes.offset_x + rounding_offset;
        if (instr.opcode == FetchOpcode::kGetTextureWeights) {
          offsets[0] -= 0.5f;
        }
        break;
      case xenos::FetchOpDimension::k2D:
        offsets[0] = instr.attributes.offset_x + rounding_offset;
        offsets[1] = instr.attributes.offset_y + rounding_offset;
        if (instr.opcode == FetchOpcode::kGetTextureWeights) {
          offsets[0] -= 0.5f;
          offsets[1] -= 0.5f;
        }
        break;
      case xenos::FetchOpDimension::k3DOrStacked:
        offsets[0] = instr.attributes.offset_x + rounding_offset;
        offsets[1] = instr.attributes.offset_y + rounding_offset;
        offsets[2] = instr.attributes.offset_z + rounding_offset;
        if (instr.opcode == FetchOpcode::kGetTextureWeights) {
          offsets[0] -= 0.5f;
          offsets[1] -= 0.5f;
          offsets[2] -= 0.5f;
        }
        break;
      case xenos::FetchOpDimension::kCube:

        offsets[0] = instr.attributes.offset_x + rounding_offset;
        offsets[1] = instr.attributes.offset_y + rounding_offset;
        if (instr.opcode == FetchOpcode::kGetTextureWeights) {
          offsets[0] -= 0.5f;
          offsets[1] -= 0.5f;

        } else {
          offsets[2] = instr.attributes.offset_z;
        }
        break;
    }
  }
  uint32_t offsets_not_zero = 0b000;
  for (uint32_t i = 0; i < 3; ++i) {
    if (offsets[i]) {
      offsets_not_zero |= 1 << i;
    }
  }
  dxbc::Src offsets_src(dxbc::Src::LF(offsets[0], offsets[1], offsets[2], 0.0f));

  uint32_t size_needed_components = 0b0000;
  if (instr.opcode == FetchOpcode::kGetTextureWeights) {
    if (!instr.attributes.unnormalized_coordinates) {
      switch (instr.dimension) {
        case xenos::FetchOpDimension::k1D:

          size_needed_components |= 0b0001;
          break;
        case xenos::FetchOpDimension::k2D:
        case xenos::FetchOpDimension::kCube:
          size_needed_components |= used_result_nonzero_components & 0b0011;
          break;
        case xenos::FetchOpDimension::k3DOrStacked:
          size_needed_components |= used_result_nonzero_components & 0b0111;
          break;
      }
    }
  } else {
    size_needed_components |= offsets_not_zero | (point_snap ? 0b0011 : 0);
    switch (instr.dimension) {
      case xenos::FetchOpDimension::k1D:
        size_needed_components |= 0b0001;
        break;
      case xenos::FetchOpDimension::k2D:
        if (promoted_1d || instr.attributes.unnormalized_coordinates) {
          size_needed_components |= 0b0011;
        }
        break;
      case xenos::FetchOpDimension::k3DOrStacked:

        size_needed_components |= 0b1000;
        if (instr.attributes.unnormalized_coordinates) {
          size_needed_components |= 0b0111;
        } else {
          size_needed_components |= 0b0100;
        }
        break;
      case xenos::FetchOpDimension::kCube:
        if (instr.attributes.unnormalized_coordinates) {
          size_needed_components |= 0b0011;
        }

        size_needed_components &= 0b0011;
        break;
    }
  }
  if (instr.dimension == xenos::FetchOpDimension::k3DOrStacked && size_needed_components) {
    size_needed_components |= 0b1000;
  }
  if (promoted_1d && size_needed_components) {
    size_needed_components |= 0b0011;
  }
  uint32_t size_and_is_3d_temp = size_needed_components ? PushSystemTemp() : UINT32_MAX;
  uint32_t size_1d_width_minus_1_temp = UINT32_MAX;
  if (size_needed_components) {
    switch (instr.dimension) {
      case xenos::FetchOpDimension::k1D:
        a_.OpUBFE(dxbc::Dest::R(size_and_is_3d_temp, 0b0001),
                  dxbc::Src::LU(xenos::kTexture1DMaxWidthLog2), dxbc::Src::LU(0),
                  RequestTextureFetchConstantWord(tfetch_index, 2));
        size_1d_width_minus_1_temp = PushSystemTemp();
        a_.OpMov(dxbc::Dest::R(size_1d_width_minus_1_temp, 0b0001),
                 dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kXXXX));
        break;
      case xenos::FetchOpDimension::k2D:
      case xenos::FetchOpDimension::kCube:
        a_.OpUBFE(dxbc::Dest::R(size_and_is_3d_temp, size_needed_components),
                  dxbc::Src::LU(13, 13, 0, 0), dxbc::Src::LU(0, 13, 0, 0),
                  RequestTextureFetchConstantWord(tfetch_index, 2));
        if (promoted_1d) {
          size_1d_width_minus_1_temp = PushSystemTemp();
          a_.OpUBFE(dxbc::Dest::R(size_1d_width_minus_1_temp, 0b0001),
                    dxbc::Src::LU(xenos::kTexture1DMaxWidthLog2), dxbc::Src::LU(0),
                    RequestTextureFetchConstantWord(tfetch_index, 2));
          a_.OpMov(dxbc::Dest::R(size_1d_width_minus_1_temp, 0b0010), dxbc::Src::LU(0));
          a_.OpUBFE(dxbc::Dest::R(size_and_is_3d_temp, 0b1000), dxbc::Src::LU(2), dxbc::Src::LU(9),
                    RequestTextureFetchConstantWord(tfetch_index, 5));
          a_.OpIEq(dxbc::Dest::R(size_and_is_3d_temp, 0b1000),
                   dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kWWWW),
                   dxbc::Src::LU(uint32_t(xenos::DataDimension::k1D)));
          a_.OpMovC(dxbc::Dest::R(size_and_is_3d_temp, 0b0011),
                    dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kWWWW),
                    dxbc::Src::R(size_1d_width_minus_1_temp), dxbc::Src::R(size_and_is_3d_temp));
        }
        break;
      case xenos::FetchOpDimension::k3DOrStacked:

        a_.OpUBFE(dxbc::Dest::R(size_and_is_3d_temp, 0b1000), dxbc::Src::LU(2), dxbc::Src::LU(9),
                  RequestTextureFetchConstantWord(tfetch_index, 5));
        a_.OpIEq(dxbc::Dest::R(size_and_is_3d_temp, 0b1000),
                 dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kWWWW),
                 dxbc::Src::LU(uint32_t(xenos::DataDimension::k3D)));
        if (size_needed_components & 0b0111) {
          a_.OpIf(true, dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kWWWW));

          a_.OpUBFE(dxbc::Dest::R(size_and_is_3d_temp, size_needed_components & 0b0111),
                    dxbc::Src::LU(11, 11, 10, 0), dxbc::Src::LU(0, 11, 22, 0),
                    RequestTextureFetchConstantWord(tfetch_index, 2));
          a_.OpElse();

          a_.OpUBFE(dxbc::Dest::R(size_and_is_3d_temp, size_needed_components & 0b0111),
                    dxbc::Src::LU(13, 13, 6, 0), dxbc::Src::LU(0, 13, 26, 0),
                    RequestTextureFetchConstantWord(tfetch_index, 2));
          a_.OpEndIf();
        }
        break;
    }
    if (size_needed_components & 0b0111) {
      a_.OpIAdd(dxbc::Dest::R(size_and_is_3d_temp, size_needed_components & 0b0111),
                dxbc::Src::R(size_and_is_3d_temp), dxbc::Src::LU(1));

      a_.OpUToF(dxbc::Dest::R(size_and_is_3d_temp, size_needed_components & 0b0111),
                dxbc::Src::R(size_and_is_3d_temp));
    }
  }
  uint32_t revert_resolution_scale_axes =
      REXCVAR_GET(draw_resolution_scaled_texture_offsets)
          ? uint32_t(draw_resolution_scale_x_ > 1) | (uint32_t(draw_resolution_scale_y_ > 1) << 1)
          : 0;

  if (instr.opcode == FetchOpcode::kGetTextureWeights) {
    assert_zero(used_result_nonzero_components & 0b1000);

    bool coord_operand_temp_pushed = false;
    dxbc::Src coord_operand =
        LoadOperand(instr.operands[0], used_result_nonzero_components, coord_operand_temp_pushed);
    dxbc::Src coord_src(coord_operand);

    uint32_t resolution_scaled_result_components =
        used_result_nonzero_components & revert_resolution_scale_axes;
    uint32_t resolution_scaled_coord_components =
        instr.attributes.unnormalized_coordinates ? resolution_scaled_result_components : 0b0000;
    uint32_t resolution_scaled_size_components =
        size_needed_components & resolution_scaled_result_components;
    if (resolution_scaled_coord_components || resolution_scaled_size_components) {
      if (resolution_scaled_coord_components &&
          (coord_src.type_ != dxbc::OperandType::kTemp ||
           coord_src.index_1d_.index_ != system_temp_result_)) {
        a_.OpMov(dxbc::Dest::R(system_temp_result_, used_result_nonzero_components), coord_src);
        coord_src = dxbc::Src::R(system_temp_result_);
      }

      assert_zero(used_result_nonzero_components & 0b1000);
      a_.OpAnd(dxbc::Dest::R(system_temp_result_, 0b1000),
               LoadSystemConstant(SystemConstants::Index::kTexturesResolutionScaled,
                                  offsetof(SystemConstants, textures_resolution_scaled),
                                  dxbc::Src::kXXXX),
               dxbc::Src::LU(uint32_t(1) << tfetch_index));
      a_.OpIf(true, dxbc::Src::R(system_temp_result_, dxbc::Src::kWWWW));

      dxbc::Src resolution_scale_src(dxbc::Src::LF(float(draw_resolution_scale_x_),
                                                   float(draw_resolution_scale_y_), 1.0f, 1.0f));
      if (resolution_scaled_coord_components) {
        a_.OpMul(dxbc::Dest::R(system_temp_result_, resolution_scaled_coord_components), coord_src,
                 resolution_scale_src);
      }
      if (resolution_scaled_size_components) {
        a_.OpMul(dxbc::Dest::R(size_and_is_3d_temp, resolution_scaled_size_components),
                 dxbc::Src::R(size_and_is_3d_temp), resolution_scale_src);
      }
      a_.OpEndIf();
    }
    uint32_t offsets_needed = offsets_not_zero & used_result_nonzero_components;
    if (!instr.attributes.unnormalized_coordinates || offsets_needed) {
      coord_src = dxbc::Src::R(system_temp_result_);
      dxbc::Dest coord_dest(dxbc::Dest::R(system_temp_result_, used_result_nonzero_components));
      if (instr.attributes.unnormalized_coordinates) {
        if (offsets_needed) {
          a_.OpAdd(coord_dest, coord_operand, offsets_src);
        }
      } else {
        assert_true((size_needed_components & used_result_nonzero_components) ==
                    used_result_nonzero_components);
        if (offsets_needed) {
          a_.OpMAd(coord_dest, coord_operand, dxbc::Src::R(size_and_is_3d_temp), offsets_src);
        } else {
          a_.OpMul(coord_dest, coord_operand, dxbc::Src::R(size_and_is_3d_temp));
        }
      }
    }

    a_.OpFrc(dxbc::Dest::R(system_temp_result_, used_result_nonzero_components), coord_src);
    if (coord_operand_temp_pushed) {
      PopSystemTemp();
    }
  } else {
    dxbc::Src signs_uint_src(GetSystemConstantSrc(
        offsetof(SystemConstants, texture_swizzled_signs) + sizeof(uint32_t) * (tfetch_index >> 2),
        dxbc::Src::kXXXX));
    uint32_t signs_shift = (tfetch_index & 3) * 8;
    uint32_t signs_temp = UINT32_MAX;
    if (instr.opcode == FetchOpcode::kTextureFetch || get_border_color_frac) {
      signs_temp = PushSystemTemp();
      MarkSystemConstantUsed(SystemConstants::Index::kTextureSwizzledSigns);
      a_.OpUBFE(dxbc::Dest::R(signs_temp, used_result_nonzero_components), dxbc::Src::LU(2),
                dxbc::Src::LU(signs_shift, signs_shift + 2, signs_shift + 4, signs_shift + 6),
                signs_uint_src);
    }

    uint32_t coord_and_sampler_temp = PushSystemTemp();

    bool coord_operand_temp_pushed = false;
    dxbc::Src coord_operand = LoadOperand(
        instr.operands[0], (1 << xenos::GetFetchOpDimensionComponentCount(instr.dimension)) - 1,
        coord_operand_temp_pushed);
    uint32_t normalized_components = 0b0000;
    switch (instr.dimension) {
      case xenos::FetchOpDimension::k1D:
        normalized_components = 0b0001;
        break;
      case xenos::FetchOpDimension::k2D:
      case xenos::FetchOpDimension::kCube:
        normalized_components = 0b0011;
        break;
      case xenos::FetchOpDimension::k3DOrStacked:
        normalized_components = 0b0111;
        break;
    }
    uint32_t normalized_components_with_offsets = normalized_components & offsets_not_zero;
    uint32_t normalized_components_with_scaled_offsets =
        normalized_components_with_offsets & revert_resolution_scale_axes;
    uint32_t normalized_components_with_unscaled_offsets =
        normalized_components_with_offsets & ~normalized_components_with_scaled_offsets;
    uint32_t normalized_components_without_offsets =
        normalized_components & ~normalized_components_with_offsets;

    if (instr.attributes.unnormalized_coordinates) {
      assert_not_zero(normalized_components);
      assert_true((size_needed_components & normalized_components) == normalized_components);
      if (normalized_components_with_offsets) {
        if (normalized_components_with_scaled_offsets) {
          a_.OpAnd(dxbc::Dest::R(coord_and_sampler_temp, 0b1000),
                   LoadSystemConstant(SystemConstants::Index::kTexturesResolutionScaled,
                                      offsetof(SystemConstants, textures_resolution_scaled),
                                      dxbc::Src::kXXXX),
                   dxbc::Src::LU(uint32_t(1) << tfetch_index));
          a_.OpIf(true, dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kWWWW));
          a_.OpAdd(dxbc::Dest::R(coord_and_sampler_temp, normalized_components_with_scaled_offsets),
                   coord_operand,
                   dxbc::Src::LF(offsets[0] / draw_resolution_scale_x_,
                                 offsets[1] / draw_resolution_scale_y_, 0.0f, 0.0f));
          a_.OpElse();
          a_.OpAdd(dxbc::Dest::R(coord_and_sampler_temp, normalized_components_with_scaled_offsets),
                   coord_operand, offsets_src);
          a_.OpEndIf();
        }
        if (normalized_components_with_unscaled_offsets) {
          a_.OpAdd(
              dxbc::Dest::R(coord_and_sampler_temp, normalized_components_with_unscaled_offsets),
              coord_operand, offsets_src);
        }
        if (normalized_components_without_offsets) {
          a_.OpMov(dxbc::Dest::R(coord_and_sampler_temp, normalized_components_without_offsets),
                   coord_operand);
        }
        assert_not_zero(normalized_components & 0b011);
        a_.OpDiv(dxbc::Dest::R(coord_and_sampler_temp, normalized_components & 0b011),
                 dxbc::Src::R(coord_and_sampler_temp), dxbc::Src::R(size_and_is_3d_temp));
        if (instr.dimension == xenos::FetchOpDimension::k3DOrStacked) {
          assert_true((size_needed_components & 0b1100) == 0b1100);
          a_.OpIf(true, dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kWWWW));
          a_.OpDiv(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                   dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ),
                   dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kZZZZ));
          a_.OpElse();
          {
            uint32_t layer_clamp_temp = PushSystemTemp();
            a_.OpMax(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                     dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ), dxbc::Src::LF(0.5f));
            a_.OpAdd(dxbc::Dest::R(layer_clamp_temp, 0b0001),
                     dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kZZZZ), dxbc::Src::LF(-0.5f));
            a_.OpMin(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                     dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ),
                     dxbc::Src::R(layer_clamp_temp, dxbc::Src::kXXXX));
            PopSystemTemp();
          }
          a_.OpEndIf();
        }
      } else {
        a_.OpDiv(dxbc::Dest::R(coord_and_sampler_temp, normalized_components), coord_operand,
                 dxbc::Src::R(size_and_is_3d_temp));
        if (instr.dimension == xenos::FetchOpDimension::k3DOrStacked) {
          assert_true((size_needed_components & 0b1100) == 0b1100);
          a_.OpIf(false, dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kWWWW));
          a_.OpMov(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                   coord_operand.SelectFromSwizzled(2));
          {
            uint32_t layer_clamp_temp = PushSystemTemp();
            a_.OpMax(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                     dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ), dxbc::Src::LF(0.5f));
            a_.OpAdd(dxbc::Dest::R(layer_clamp_temp, 0b0001),
                     dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kZZZZ), dxbc::Src::LF(-0.5f));
            a_.OpMin(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                     dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ),
                     dxbc::Src::R(layer_clamp_temp, dxbc::Src::kXXXX));
            PopSystemTemp();
          }
          a_.OpEndIf();
        }
      }
    } else {
      if (normalized_components_with_offsets) {
        assert_true((size_needed_components & normalized_components_with_offsets) ==
                    normalized_components_with_offsets);
        a_.OpDiv(dxbc::Dest::R(coord_and_sampler_temp, normalized_components_with_offsets),
                 offsets_src, dxbc::Src::R(size_and_is_3d_temp));
        if (normalized_components_with_scaled_offsets) {
          a_.OpAnd(dxbc::Dest::R(coord_and_sampler_temp, 0b1000),
                   LoadSystemConstant(SystemConstants::Index::kTexturesResolutionScaled,
                                      offsetof(SystemConstants, textures_resolution_scaled),
                                      dxbc::Src::kXXXX),
                   dxbc::Src::LU(uint32_t(1) << tfetch_index));
          a_.OpIf(true, dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kWWWW));
          a_.OpMAd(dxbc::Dest::R(coord_and_sampler_temp, normalized_components_with_scaled_offsets),
                   dxbc::Src::R(coord_and_sampler_temp),
                   dxbc::Src::LF(1.0f / draw_resolution_scale_x_, 1.0f / draw_resolution_scale_y_,
                                 1.0f, 1.0f),
                   coord_operand);
          a_.OpElse();
          a_.OpAdd(dxbc::Dest::R(coord_and_sampler_temp, normalized_components_with_scaled_offsets),
                   coord_operand, dxbc::Src::R(coord_and_sampler_temp));
          a_.OpEndIf();
        }
        if (normalized_components_with_unscaled_offsets) {
          a_.OpAdd(
              dxbc::Dest::R(coord_and_sampler_temp, normalized_components_with_unscaled_offsets),
              coord_operand, dxbc::Src::R(coord_and_sampler_temp));
        }
      }

      if (normalized_components_without_offsets & 0b011) {
        a_.OpMov(
            dxbc::Dest::R(coord_and_sampler_temp, normalized_components_without_offsets & 0b011),
            coord_operand);
      }
      if (instr.dimension == xenos::FetchOpDimension::k3DOrStacked) {
        assert_true((size_needed_components & 0b1100) == 0b1100);
        if (normalized_components_with_offsets & 0b100) {
          a_.OpIf(false, dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kWWWW));
          a_.OpMAd(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                   coord_operand.SelectFromSwizzled(2),
                   dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kZZZZ), dxbc::Src::LF(offsets[2]));
          {
            uint32_t layer_clamp_temp = PushSystemTemp();
            a_.OpMax(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                     dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ), dxbc::Src::LF(0.5f));
            a_.OpAdd(dxbc::Dest::R(layer_clamp_temp, 0b0001),
                     dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kZZZZ), dxbc::Src::LF(-0.5f));
            a_.OpMin(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                     dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ),
                     dxbc::Src::R(layer_clamp_temp, dxbc::Src::kXXXX));
            PopSystemTemp();
          }
          a_.OpEndIf();
        } else {
          a_.OpMul(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                   coord_operand.SelectFromSwizzled(2),
                   dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kZZZZ));
          a_.OpIf(true, dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kWWWW));
          a_.OpMov(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                   coord_operand.SelectFromSwizzled(2));
          a_.OpElse();
          {
            uint32_t layer_clamp_temp = PushSystemTemp();
            a_.OpMax(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                     dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ), dxbc::Src::LF(0.5f));
            a_.OpAdd(dxbc::Dest::R(layer_clamp_temp, 0b0001),
                     dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kZZZZ), dxbc::Src::LF(-0.5f));
            a_.OpMin(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                     dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ),
                     dxbc::Src::R(layer_clamp_temp, dxbc::Src::kXXXX));
            PopSystemTemp();
          }
          a_.OpEndIf();
        }
      }
    }
    switch (instr.dimension) {
      case xenos::FetchOpDimension::k1D:
      case xenos::FetchOpDimension::k2D:
        if (size_1d_width_minus_1_temp != UINT32_MAX) {
          EmitWide1DTextureCoordinates(instr, coord_operand, offsets[0], tfetch_index,
                                       coord_and_sampler_temp, size_1d_width_minus_1_temp,
                                       promoted_1d);
        } else {
          a_.OpMov(
              dxbc::Dest::R(coord_and_sampler_temp, fetch_1d && !promoted_1d ? 0b0110 : 0b0100),
              dxbc::Src::LF(0.0f));
        }
        break;
      case xenos::FetchOpDimension::kCube: {
        a_.OpMAd(dxbc::Dest::R(coord_and_sampler_temp, 0b0011),
                 dxbc::Src::R(coord_and_sampler_temp), dxbc::Src::LF(2.0f), dxbc::Src::LF(-3.0f));

        if (offsets[2]) {
          a_.OpAdd(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                   coord_operand.SelectFromSwizzled(2), dxbc::Src::LF(offsets[2]));
          a_.OpFToU(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                    dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ));
        } else {
          a_.OpFToU(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                    coord_operand.SelectFromSwizzled(2));
        }
        a_.OpUMin(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                  dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ), dxbc::Src::LU(5));

        a_.OpUBFE(dxbc::Dest::R(coord_and_sampler_temp, 0b1100), dxbc::Src::LU(0, 0, 2, 1),
                  dxbc::Src::LU(0, 0, 1, 0),
                  dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ));

        a_.OpSwitch(dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ));
        a_.OpCase(dxbc::Src::LU(0));
        {
          a_.OpMov(dxbc::Dest::R(coord_and_sampler_temp, 0b0010),
                   -dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kYYYY));

          a_.OpMovC(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                    dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kWWWW),
                    dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kXXXX),
                    -dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kXXXX));

          a_.OpMovC(dxbc::Dest::R(coord_and_sampler_temp, 0b0001),
                    dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kWWWW), dxbc::Src::LF(-1.0f),
                    dxbc::Src::LF(1.0f));
        }
        a_.OpBreak();
        a_.OpCase(dxbc::Src::LU(1));
        {
          a_.OpMovC(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                    dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kWWWW),
                    -dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kYYYY),
                    dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kYYYY));

          a_.OpMovC(dxbc::Dest::R(coord_and_sampler_temp, 0b0010),
                    dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kWWWW), dxbc::Src::LF(-1.0f),
                    dxbc::Src::LF(1.0f));
        }
        a_.OpBreak();
        a_.OpDefault();
        {
          a_.OpMovC(dxbc::Dest::R(coord_and_sampler_temp, 0b0001),
                    dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kWWWW),
                    -dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kXXXX),
                    dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kXXXX));

          a_.OpMov(dxbc::Dest::R(coord_and_sampler_temp, 0b0010),
                   -dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kYYYY));

          a_.OpMovC(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                    dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kWWWW), dxbc::Src::LF(-1.0f),
                    dxbc::Src::LF(1.0f));
        }
        a_.OpBreak();
        a_.OpEndSwitch();
      } break;
      default:
        break;
    }
    if (coord_operand_temp_pushed) {
      PopSystemTemp();
    }

    if (instr.opcode == FetchOpcode::kGetTextureComputedLod) {
      uint32_t sampler_binding_index = FindOrAddSamplerBinding(
          tfetch_index, instr.attributes.mag_filter, instr.attributes.min_filter,
          xenos::TextureFilter::kLinear, instr.attributes.aniso_filter);
      dxbc::Src sampler(dxbc::Src::S(sampler_binding_index, sampler_binding_index));
      if (bindless_resources_used_) {
        if (cbuffer_index_descriptor_indices_ == kBindingIndexUnallocated) {
          cbuffer_index_descriptor_indices_ = cbuffer_count_++;
        }
        uint32_t sampler_bindless_descriptor_index =
            sampler_bindings_[sampler_binding_index].bindless_descriptor_index;
        a_.OpMov(dxbc::Dest::R(coord_and_sampler_temp, 0b1000),
                 dxbc::Src::CB(cbuffer_index_descriptor_indices_,
                               uint32_t(CbufferRegister::kDescriptorIndices),
                               sampler_bindless_descriptor_index >> 2)
                     .Select(sampler_bindless_descriptor_index & 3));
        sampler = dxbc::Src::S(0, dxbc::Index(coord_and_sampler_temp, 3));
      }

      uint32_t is_unsigned_temp = PushSystemTemp();
      MarkSystemConstantUsed(SystemConstants::Index::kTextureSwizzledSigns);
      a_.OpUBFE(dxbc::Dest::R(is_unsigned_temp, 0b0001), dxbc::Src::LU(8),
                dxbc::Src::LU(signs_shift), signs_uint_src);
      a_.OpINE(dxbc::Dest::R(is_unsigned_temp, 0b0001),
               dxbc::Src::R(is_unsigned_temp, dxbc::Src::kXXXX),
               dxbc::Src::LU(uint32_t(xenos::TextureSign::kSigned) * 0b01010101));
      if (bindless_resources_used_) {
        if (instr.dimension == xenos::FetchOpDimension::k3DOrStacked) {
          assert_true((size_needed_components & 0b1000) == 0b1000);
          a_.OpIf(true, dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kWWWW));
        }
        for (uint32_t is_stacked = 0;
             is_stacked < (instr.dimension == xenos::FetchOpDimension::k3DOrStacked ? 2u : 1u);
             ++is_stacked) {
          xenos::FetchOpDimension srv_dimension = instr.dimension;
          if (is_stacked) {
            srv_dimension = xenos::FetchOpDimension::k2D;
            a_.OpElse();
          }
          uint32_t texture_binding_index_unsigned =
              FindOrAddTextureBinding(tfetch_index, srv_dimension, false);
          uint32_t texture_binding_index_signed =
              FindOrAddTextureBinding(tfetch_index, srv_dimension, true);
          uint32_t texture_bindless_descriptor_index_unsigned =
              texture_bindings_[texture_binding_index_unsigned].bindless_descriptor_index;
          uint32_t texture_bindless_descriptor_index_signed =
              texture_bindings_[texture_binding_index_signed].bindless_descriptor_index;
          if (cbuffer_index_descriptor_indices_ == kBindingIndexUnallocated) {
            cbuffer_index_descriptor_indices_ = cbuffer_count_++;
          }
          a_.OpMovC(dxbc::Dest::R(is_unsigned_temp, 0b0001),
                    dxbc::Src::R(is_unsigned_temp, dxbc::Src::kXXXX),
                    dxbc::Src::CB(cbuffer_index_descriptor_indices_,
                                  uint32_t(CbufferRegister::kDescriptorIndices),
                                  texture_bindless_descriptor_index_unsigned >> 2)
                        .Select(texture_bindless_descriptor_index_unsigned & 3),
                    dxbc::Src::CB(cbuffer_index_descriptor_indices_,
                                  uint32_t(CbufferRegister::kDescriptorIndices),
                                  texture_bindless_descriptor_index_signed >> 2)
                        .Select(texture_bindless_descriptor_index_signed & 3));

          assert_true(used_result_nonzero_components == 0b0001);
          uint32_t* bindless_srv_index = nullptr;
          switch (srv_dimension) {
            case xenos::FetchOpDimension::k1D:
            case xenos::FetchOpDimension::k2D:
              bindless_srv_index = &srv_index_bindless_textures_2d_;
              break;
            case xenos::FetchOpDimension::k3DOrStacked:
              bindless_srv_index = &srv_index_bindless_textures_3d_;
              break;
            case xenos::FetchOpDimension::kCube:
              bindless_srv_index = &srv_index_bindless_textures_cube_;
              break;
          }
          assert_not_null(bindless_srv_index);
          if (*bindless_srv_index == kBindingIndexUnallocated) {
            *bindless_srv_index = srv_count_++;
          }
          a_.OpLOD(
              dxbc::Dest::R(system_temp_result_, 0b0001), dxbc::Src::R(coord_and_sampler_temp), 3,
              dxbc::Src::T(*bindless_srv_index, dxbc::Index(is_unsigned_temp, 0), dxbc::Src::kYYYY),
              sampler);
        }
        if (instr.dimension == xenos::FetchOpDimension::k3DOrStacked) {
          a_.OpEndIf();
        }
      } else {
        a_.OpIf(true, dxbc::Src::R(is_unsigned_temp, dxbc::Src::kXXXX));
        for (uint32_t is_signed = 0; is_signed < 2; ++is_signed) {
          if (is_signed) {
            a_.OpElse();
          }
          if (instr.dimension == xenos::FetchOpDimension::k3DOrStacked) {
            assert_true((size_needed_components & 0b1000) == 0b1000);
            a_.OpIf(true, dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kWWWW));
          }
          for (uint32_t is_stacked = 0;
               is_stacked < (instr.dimension == xenos::FetchOpDimension::k3DOrStacked ? 2u : 1u);
               ++is_stacked) {
            if (is_stacked) {
              a_.OpElse();
            }
            assert_true(used_result_nonzero_components == 0b0001);
            uint32_t texture_binding_index = FindOrAddTextureBinding(
                tfetch_index, is_stacked ? xenos::FetchOpDimension::k2D : instr.dimension,
                is_signed != 0);
            a_.OpLOD(dxbc::Dest::R(system_temp_result_, 0b0001),
                     dxbc::Src::R(coord_and_sampler_temp), 3,
                     dxbc::Src::T(
                         texture_bindings_[texture_binding_index].bindful_srv_index,
                         uint32_t(SRVMainRegister::kBindfulTexturesStart) + texture_binding_index,
                         dxbc::Src::kYYYY),
                     sampler);
          }
          if (instr.dimension == xenos::FetchOpDimension::k3DOrStacked) {
            a_.OpEndIf();
          }
        }

        a_.OpEndIf();
      }

      PopSystemTemp();
    } else {
      dxbc::Src lod_src(dxbc::Src::LF(0.0f));
      uint32_t grad_component_count = 0;

      uint32_t grad_h_lod_temp = UINT32_MAX;

      uint32_t grad_v_temp = UINT32_MAX;
      if (instr.attributes.mip_filter != xenos::TextureFilter::kBaseMap) {
        grad_h_lod_temp = PushSystemTemp();
        lod_src = dxbc::Src::R(grad_h_lod_temp, dxbc::Src::kWWWW);

        dxbc::Dest lod_dest(dxbc::Dest::R(grad_h_lod_temp, 0b1000));

        a_.OpIBFE(lod_dest, dxbc::Src::LU(10), dxbc::Src::LU(12),
                  RequestTextureFetchConstantWord(tfetch_index, 4));
        a_.OpIToF(lod_dest, lod_src);
        if (instr.attributes.use_register_lod) {
          a_.OpMAd(lod_dest, lod_src, dxbc::Src::LF(1.0f / 32.0f),
                   dxbc::Src::R(system_temp_grad_h_lod_, dxbc::Src::kWWWW));
          if (instr.attributes.lod_bias) {
            a_.OpAdd(lod_dest, lod_src, dxbc::Src::LF(instr.attributes.lod_bias));
          }
        } else {
          if (instr.attributes.lod_bias) {
            a_.OpMAd(lod_dest, lod_src, dxbc::Src::LF(1.0f / 32.0f),
                     dxbc::Src::LF(instr.attributes.lod_bias));
          } else {
            a_.OpMul(lod_dest, lod_src, dxbc::Src::LF(1.0f / 32.0f));
          }
        }
        if (use_computed_lod) {
          grad_v_temp = PushSystemTemp();
          switch (instr.dimension) {
            case xenos::FetchOpDimension::k1D:
              grad_component_count = 1;
              break;
            case xenos::FetchOpDimension::k2D:
              grad_component_count = 2;
              break;
            case xenos::FetchOpDimension::k3DOrStacked:
            case xenos::FetchOpDimension::kCube:
              grad_component_count = 3;
              break;
          }
          assert_not_zero(grad_component_count);
          uint32_t grad_mask = (1 << grad_component_count) - 1;

          a_.OpExp(lod_dest, lod_src);

#if 0

          a_.OpIBFE(dxbc::Dest::R(grad_h_lod_temp, 0b0011), dxbc::Src::LU(5),
                    dxbc::Src::LU(22, 27, 0, 0),
                    RequestTextureFetchConstantWord(tfetch_index, 4));
          a_.OpIMAd(dxbc::Dest::R(grad_h_lod_temp, 0b0011),
                    dxbc::Src::R(grad_h_lod_temp),
                    dxbc::Src::LI(int32_t(1) << 23), dxbc::Src::LF(1.0f));
          a_.OpMul(dxbc::Dest::R(grad_v_temp, 0b1000), lod_src,
                   dxbc::Src::R(grad_h_lod_temp, dxbc::Src::kYYYY));
          a_.OpMul(lod_dest, lod_src,
                   dxbc::Src::R(grad_h_lod_temp, dxbc::Src::kXXXX));
#endif

          if (instr.attributes.use_register_gradients) {
            a_.OpMul(dxbc::Dest::R(grad_h_lod_temp, grad_mask),
                     dxbc::Src::R(system_temp_grad_h_lod_), lod_src);

#if 0
            a_.OpMul(dxbc::Dest::R(grad_v_temp, grad_mask),
                     dxbc::Src::R(system_temp_grad_v_vfetch_address_),
                     dxbc::Src::R(grad_v_temp, dxbc::Src::kWWWW));
#else
            a_.OpMul(dxbc::Dest::R(grad_v_temp, grad_mask),
                     dxbc::Src::R(system_temp_grad_v_vfetch_address_), lod_src);
#endif

            if (instr.attributes.unnormalized_coordinates &&
                instr.dimension != xenos::FetchOpDimension::kCube) {
              uint32_t grad_norm_mask = grad_mask;
              if (instr.dimension == xenos::FetchOpDimension::k3DOrStacked) {
                grad_norm_mask &= 0b0011;
              }
              assert_true((size_needed_components & grad_norm_mask) == grad_norm_mask);
              a_.OpDiv(dxbc::Dest::R(grad_h_lod_temp, grad_norm_mask),
                       dxbc::Src::R(grad_h_lod_temp), dxbc::Src::R(size_and_is_3d_temp));
              a_.OpDiv(dxbc::Dest::R(grad_v_temp, grad_norm_mask), dxbc::Src::R(grad_v_temp),
                       dxbc::Src::R(size_and_is_3d_temp));

              assert_true((size_needed_components & 0b1100) == 0b1100);
              a_.OpIf(true, dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kWWWW));
              a_.OpDiv(dxbc::Dest::R(grad_h_lod_temp, 0b0100),
                       dxbc::Src::R(grad_h_lod_temp, dxbc::Src::kZZZZ),
                       dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kZZZZ));
              a_.OpDiv(dxbc::Dest::R(grad_v_temp, 0b0100),
                       dxbc::Src::R(grad_v_temp, dxbc::Src::kZZZZ),
                       dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kZZZZ));
              a_.OpEndIf();
            }
          } else {
            a_.OpDerivRTXCoarse(dxbc::Dest::R(grad_h_lod_temp, grad_mask),
                                dxbc::Src::R(coord_and_sampler_temp));
            a_.OpMul(dxbc::Dest::R(grad_h_lod_temp, grad_mask), dxbc::Src::R(grad_h_lod_temp),
                     lod_src);
            a_.OpDerivRTYCoarse(dxbc::Dest::R(grad_v_temp, grad_mask),
                                dxbc::Src::R(coord_and_sampler_temp));

#if 0
            a_.OpMul(dxbc::Dest::R(grad_v_temp, grad_mask),
                     dxbc::Src::R(grad_v_temp),
                     dxbc::Src::R(grad_v_temp, dxbc::Src::kWWWW));
#else
            a_.OpMul(dxbc::Dest::R(grad_v_temp, grad_mask), dxbc::Src::R(grad_v_temp), lod_src);
#endif
          }
          if (instr.dimension == xenos::FetchOpDimension::k1D) {
            a_.OpMov(dxbc::Dest::R(grad_h_lod_temp, 0b0010), dxbc::Src::LF(0.0f));
            a_.OpMov(dxbc::Dest::R(grad_v_temp, 0b0010), dxbc::Src::LF(0.0f));
            grad_component_count = 2;
          }
        }
      }

      uint32_t sampler_binding_index = FindOrAddSamplerBinding(
          tfetch_index, instr.attributes.mag_filter, instr.attributes.min_filter,
          instr.attributes.mip_filter,
          use_computed_lod ? instr.attributes.aniso_filter : xenos::AnisoFilter::kDisabled,
          get_border_color_frac ? std::optional(xenos::BorderColor::k_ABGR_Black) : std::nullopt);
      const uint32_t sampler_binding_index_white =
          get_border_color_frac
              ? FindOrAddSamplerBinding(tfetch_index, instr.attributes.mag_filter,
                                        instr.attributes.min_filter, instr.attributes.mip_filter,
                                        use_computed_lod ? instr.attributes.aniso_filter
                                                         : xenos::AnisoFilter::kDisabled,
                                        xenos::BorderColor::k_ABGR_White)
              : sampler_binding_index;
      dxbc::Src sampler_white(
          dxbc::Src::S(sampler_binding_index_white, sampler_binding_index_white));
      dxbc::Src sampler(dxbc::Src::S(sampler_binding_index, sampler_binding_index));
      if (bindless_resources_used_) {
        if (cbuffer_index_descriptor_indices_ == kBindingIndexUnallocated) {
          cbuffer_index_descriptor_indices_ = cbuffer_count_++;
        }
        uint32_t sampler_bindless_descriptor_index =
            sampler_bindings_[sampler_binding_index].bindless_descriptor_index;
        a_.OpMov(dxbc::Dest::R(coord_and_sampler_temp, 0b1000),
                 dxbc::Src::CB(cbuffer_index_descriptor_indices_,
                               uint32_t(CbufferRegister::kDescriptorIndices),
                               sampler_bindless_descriptor_index >> 2)
                     .Select(sampler_bindless_descriptor_index & 3));
        sampler = dxbc::Src::S(0, dxbc::Index(coord_and_sampler_temp, 3));
        sampler_white = sampler;
      }

      if (point_snap) {
        dxbc::Src snap_size(dxbc::Src::R(size_and_is_3d_temp));
        a_.OpAnd(dxbc::Dest::R(system_temp_result_, 0b0001),
                 LoadSystemConstant(SystemConstants::Index::kTextureIntegerScaleBits,
                                    offsetof(SystemConstants, texture_integer_scale_bits) +
                                        sizeof(uint32_t) * tfetch_index,
                                    dxbc::Src::kXXXX),
                 dxbc::Src::LU(UINT32_C(1) << 26));
        a_.OpIf(true, dxbc::Src::R(system_temp_result_, dxbc::Src::kXXXX));
        if (draw_resolution_scale_x_ > 1 || draw_resolution_scale_y_ > 1) {
          a_.OpAnd(dxbc::Dest::R(system_temp_result_, 0b0100),
                   LoadSystemConstant(SystemConstants::Index::kTexturesResolutionScaled,
                                      offsetof(SystemConstants, textures_resolution_scaled),
                                      dxbc::Src::kXXXX),
                   dxbc::Src::LU(UINT32_C(1) << tfetch_index));
          a_.OpMovC(dxbc::Dest::R(system_temp_result_, 0b1100),
                    dxbc::Src::R(system_temp_result_, dxbc::Src::kZZZZ),
                    dxbc::Src::LF(0.0f, 0.0f, float(draw_resolution_scale_x_),
                                  float(draw_resolution_scale_y_)),
                    dxbc::Src::LF(1.0f));
          a_.OpMul(dxbc::Dest::R(system_temp_result_, 0b1100), dxbc::Src::R(system_temp_result_),
                   dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kXYXY));
          snap_size = dxbc::Src::R(system_temp_result_, 0b11101110);
        }
        a_.OpMul(dxbc::Dest::R(system_temp_result_, 0b0011), dxbc::Src::R(coord_and_sampler_temp),
                 snap_size);
        a_.OpRoundNI(dxbc::Dest::R(system_temp_result_, 0b0011), dxbc::Src::R(system_temp_result_));
        a_.OpAdd(dxbc::Dest::R(system_temp_result_, 0b0011), dxbc::Src::R(system_temp_result_),
                 dxbc::Src::LF(0.5f));
        a_.OpDiv(dxbc::Dest::R(coord_and_sampler_temp, 0b0011), dxbc::Src::R(system_temp_result_),
                 snap_size);
        a_.OpElse();
        a_.OpDiv(dxbc::Dest::R(system_temp_result_, 0b0011), dxbc::Src::LF(kTextureCoordEpsilon),
                 dxbc::Src::R(size_and_is_3d_temp));
        a_.OpAdd(dxbc::Dest::R(coord_and_sampler_temp, 0b0011),
                 dxbc::Src::R(coord_and_sampler_temp), dxbc::Src::R(system_temp_result_));
        a_.OpEndIf();
      }

      a_.OpMov(dxbc::Dest::R(system_temp_result_, used_result_nonzero_components),
               dxbc::Src::LF(0.0f));

      uint32_t is_signed_temp = PushSystemTemp();
      a_.OpIEq(dxbc::Dest::R(is_signed_temp, used_result_nonzero_components),
               dxbc::Src::R(signs_temp), dxbc::Src::LU(uint32_t(xenos::TextureSign::kSigned)));

      dxbc::Src layer_lerp_factor_src(dxbc::Src::LF(0.0f));

      uint32_t srv_selection_temp = bindless_resources_used_ ? PushSystemTemp() : UINT32_MAX;
      if (instr.dimension == xenos::FetchOpDimension::k3DOrStacked) {
        bool vol_mag_filter_is_fetch_const =
            instr.attributes.vol_mag_filter == xenos::TextureFilter::kUseFetchConst;
        bool vol_min_filter_is_fetch_const =
            instr.attributes.vol_min_filter == xenos::TextureFilter::kUseFetchConst;
        bool vol_mag_filter_is_linear =
            instr.attributes.vol_mag_filter == xenos::TextureFilter::kLinear;
        bool vol_min_filter_is_linear =
            instr.attributes.vol_min_filter == xenos::TextureFilter::kLinear;
        if (grad_v_temp != UINT32_MAX &&
            (vol_mag_filter_is_fetch_const || vol_min_filter_is_fetch_const ||
             vol_mag_filter_is_linear != vol_min_filter_is_linear)) {
          if (srv_selection_temp == UINT32_MAX) {
            srv_selection_temp = PushSystemTemp();
          }
          layer_lerp_factor_src = dxbc::Src::R(srv_selection_temp, dxbc::Src::kZZZZ);

          a_.OpMov(dxbc::Dest::R(srv_selection_temp, 0b0100), dxbc::Src::LF(0.0f));
          assert_true((size_needed_components & 0b1000) == 0b1000);
          a_.OpIf(false, dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kWWWW));

          a_.OpMax(dxbc::Dest::R(srv_selection_temp, 0b1000),
                   dxbc::Src::R(grad_h_lod_temp, dxbc::Src::kZZZZ),
                   dxbc::Src::R(grad_v_temp, dxbc::Src::kZZZZ));
          if (!instr.attributes.unnormalized_coordinates) {
            assert_true((size_needed_components & 0b0100) == 0b0100);
            a_.OpMul(dxbc::Dest::R(srv_selection_temp, 0b1000),
                     dxbc::Src::R(srv_selection_temp, dxbc::Src::kWWWW),
                     dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kZZZZ));
          }

          a_.OpLT(dxbc::Dest::R(srv_selection_temp, 0b1000), dxbc::Src::LF(1.0f),
                  dxbc::Src::R(srv_selection_temp, dxbc::Src::kWWWW));
          if (vol_mag_filter_is_fetch_const || vol_min_filter_is_fetch_const) {
            a_.OpIf(false, dxbc::Src::R(srv_selection_temp, dxbc::Src::kWWWW));

            if (vol_mag_filter_is_fetch_const) {
              a_.OpAnd(dxbc::Dest::R(srv_selection_temp, 0b1000),
                       RequestTextureFetchConstantWord(tfetch_index, 4), dxbc::Src::LU(1));
            } else {
              a_.OpMov(dxbc::Dest::R(srv_selection_temp, 0b1000),
                       dxbc::Src::LU(uint32_t(vol_mag_filter_is_linear)));
            }
            a_.OpElse();

            if (vol_min_filter_is_fetch_const) {
              a_.OpUBFE(dxbc::Dest::R(srv_selection_temp, 0b1000), dxbc::Src::LU(1),
                        dxbc::Src::LU(1), RequestTextureFetchConstantWord(tfetch_index, 4));
            } else {
              a_.OpMov(dxbc::Dest::R(srv_selection_temp, 0b1000),
                       dxbc::Src::LU(uint32_t(vol_min_filter_is_linear)));
            }

            a_.OpEndIf();

            a_.OpIf(true, dxbc::Src::R(srv_selection_temp, dxbc::Src::kWWWW));
          } else if (vol_mag_filter_is_linear) {
            assert_false(vol_min_filter_is_linear);

            a_.OpIf(false, dxbc::Src::R(srv_selection_temp, dxbc::Src::kWWWW));
          } else {
            assert_true(vol_min_filter_is_linear);
            assert_false(vol_mag_filter_is_linear);

            a_.OpIf(true, dxbc::Src::R(srv_selection_temp, dxbc::Src::kWWWW));
          }

          a_.OpAdd(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                   dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ), dxbc::Src::LF(-0.5f));
          a_.OpFrc(dxbc::Dest::R(srv_selection_temp, 0b0100),
                   dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ));

          a_.OpEndIf();

          a_.OpEndIf();
        } else {
          if (vol_mag_filter_is_fetch_const || vol_mag_filter_is_linear) {
            if (srv_selection_temp == UINT32_MAX) {
              srv_selection_temp = PushSystemTemp();
            }
            layer_lerp_factor_src = dxbc::Src::R(srv_selection_temp, dxbc::Src::kZZZZ);

            a_.OpMov(dxbc::Dest::R(srv_selection_temp, 0b0100), dxbc::Src::LF(0.0f));
            assert_true((size_needed_components & 0b1000) == 0b1000);
            a_.OpIf(false, dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kWWWW));
            if (vol_mag_filter_is_fetch_const) {
              a_.OpAnd(dxbc::Dest::R(srv_selection_temp, 0b1000),
                       RequestTextureFetchConstantWord(tfetch_index, 4), dxbc::Src::LU(1));

              a_.OpIf(true, dxbc::Src::R(srv_selection_temp, dxbc::Src::kWWWW));
            }

            a_.OpAdd(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                     dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ), dxbc::Src::LF(-0.5f));
            a_.OpFrc(dxbc::Dest::R(srv_selection_temp, 0b0100),
                     dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ));
            if (vol_mag_filter_is_fetch_const) {
              a_.OpEndIf();
            }

            a_.OpEndIf();
          }
        }
      }

      uint32_t result_first_component;
      rex::bit_scan_forward(used_result_nonzero_components, &result_first_component);
      dxbc::Src is_all_signed_src(dxbc::Src::R(is_signed_temp).Select(result_first_component));
      dxbc::Src is_any_signed_src(dxbc::Src::R(is_signed_temp).Select(result_first_component));
      if (used_result_nonzero_components != (1 << result_first_component)) {
        if (srv_selection_temp == UINT32_MAX) {
          srv_selection_temp = PushSystemTemp();
        }
        dxbc::Dest is_all_signed_dest(dxbc::Dest::R(srv_selection_temp, 0b0001));
        dxbc::Dest is_any_signed_dest(dxbc::Dest::R(srv_selection_temp, 0b0010));
        uint32_t result_remaining_components =
            used_result_nonzero_components & ~(uint32_t(1) << result_first_component);
        uint32_t result_component;
        while (rex::bit_scan_forward(result_remaining_components, &result_component)) {
          result_remaining_components &= ~(uint32_t(1) << result_component);
          a_.OpAnd(is_all_signed_dest, is_all_signed_src,
                   dxbc::Src::R(is_signed_temp).Select(result_component));
          a_.OpOr(is_any_signed_dest, is_any_signed_src,
                  dxbc::Src::R(is_signed_temp).Select(result_component));

          is_all_signed_src = dxbc::Src::R(srv_selection_temp, dxbc::Src::kXXXX);
          is_any_signed_src = dxbc::Src::R(srv_selection_temp, dxbc::Src::kYYYY);
        }
      }

      if (get_border_color_frac) {
        is_all_signed_src = dxbc::Src::LU(0);
        is_any_signed_src = dxbc::Src::LU(UINT32_MAX);
      }
      auto load_border_sampler = [&](uint32_t binding_index) {
        if (get_border_color_frac && bindless_resources_used_) {
          const uint32_t descriptor = sampler_bindings_[binding_index].bindless_descriptor_index;
          a_.OpMov(dxbc::Dest::R(coord_and_sampler_temp, 0b1000),
                   dxbc::Src::CB(cbuffer_index_descriptor_indices_,
                                 uint32_t(CbufferRegister::kDescriptorIndices), descriptor >> 2)
                       .Select(descriptor & 3));
        }
      };

      if (instr.dimension == xenos::FetchOpDimension::k3DOrStacked) {
        assert_true((size_needed_components & 0b1000) == 0b1000);

        a_.OpIf(true, dxbc::Src::R(size_and_is_3d_temp, dxbc::Src::kWWWW));
      }
      for (uint32_t is_stacked = 0;
           is_stacked < (instr.dimension == xenos::FetchOpDimension::k3DOrStacked ? 2u : 1u);
           ++is_stacked) {
        xenos::FetchOpDimension srv_dimension = instr.dimension;
        uint32_t srv_grad_component_count = grad_component_count;
        bool layer_lerp_needed = false;
        if (is_stacked) {
          srv_dimension = xenos::FetchOpDimension::k2D;
          srv_grad_component_count = 2;
          layer_lerp_needed = layer_lerp_factor_src.type_ != dxbc::OperandType::kImmediate32;
          a_.OpElse();

          a_.OpRoundNI(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                       dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ));
        }
        uint32_t texture_binding_index_unsigned =
            FindOrAddTextureBinding(tfetch_index, srv_dimension, false);
        uint32_t texture_binding_index_signed =
            get_border_color_frac ? texture_binding_index_unsigned
                                  : FindOrAddTextureBinding(tfetch_index, srv_dimension, true);
        const TextureBinding& texture_binding_unsigned =
            texture_bindings_[texture_binding_index_unsigned];
        const TextureBinding& texture_binding_signed =
            texture_bindings_[texture_binding_index_signed];
        dxbc::Src srv_unsigned(dxbc::Src::LF(0.0f)), srv_signed(dxbc::Src::LF(0.0f));
        if (bindless_resources_used_) {
          uint32_t* bindless_srv_index = nullptr;
          switch (srv_dimension) {
            case xenos::FetchOpDimension::k1D:
            case xenos::FetchOpDimension::k2D:
              bindless_srv_index = &srv_index_bindless_textures_2d_;
              break;
            case xenos::FetchOpDimension::k3DOrStacked:
              bindless_srv_index = &srv_index_bindless_textures_3d_;
              break;
            case xenos::FetchOpDimension::kCube:
              bindless_srv_index = &srv_index_bindless_textures_cube_;
              break;
          }
          assert_not_null(bindless_srv_index);
          if (*bindless_srv_index == kBindingIndexUnallocated) {
            *bindless_srv_index = srv_count_++;
          }
          assert_true(srv_selection_temp != UINT32_MAX);
          srv_unsigned = dxbc::Src::T(*bindless_srv_index, dxbc::Index(srv_selection_temp, 3));
          srv_signed = srv_unsigned;
        } else {
          srv_unsigned = dxbc::Src::T(
              texture_binding_unsigned.bindful_srv_index,
              uint32_t(SRVMainRegister::kBindfulTexturesStart) + texture_binding_index_unsigned);
          srv_signed = dxbc::Src::T(
              texture_binding_signed.bindful_srv_index,
              uint32_t(SRVMainRegister::kBindfulTexturesStart) + texture_binding_index_signed);
        }
        for (uint32_t layer = 0; layer < (layer_lerp_needed ? 2u : 1u); ++layer) {
          uint32_t layer_value_temp = system_temp_result_;
          if (layer) {
            layer_value_temp = PushSystemTemp();

            a_.OpNE(dxbc::Dest::R(layer_value_temp, 0b0001), layer_lerp_factor_src,
                    dxbc::Src::LF(0.0f));

            a_.OpIf(true, dxbc::Src::R(layer_value_temp, dxbc::Src::kXXXX));

            a_.OpAdd(dxbc::Dest::R(coord_and_sampler_temp, 0b0100),
                     dxbc::Src::R(coord_and_sampler_temp, dxbc::Src::kZZZZ), dxbc::Src::LF(1.0f));
          }

          a_.OpIf(false, is_all_signed_src);
          {
            load_border_sampler(sampler_binding_index);
            if (bindless_resources_used_) {
              assert_true(srv_selection_temp != UINT32_MAX);
              if (cbuffer_index_descriptor_indices_ == kBindingIndexUnallocated) {
                cbuffer_index_descriptor_indices_ = cbuffer_count_++;
              }
              uint32_t texture_bindless_descriptor_index =
                  texture_binding_unsigned.bindless_descriptor_index;
              a_.OpMov(dxbc::Dest::R(srv_selection_temp, 0b1000),
                       dxbc::Src::CB(cbuffer_index_descriptor_indices_,
                                     uint32_t(CbufferRegister::kDescriptorIndices),
                                     texture_bindless_descriptor_index >> 2)
                           .Select(texture_bindless_descriptor_index & 3));
            }
            if (grad_v_temp != UINT32_MAX) {
              assert_not_zero(grad_component_count);
              a_.OpSampleD(dxbc::Dest::R(layer_value_temp, used_result_nonzero_components),
                           dxbc::Src::R(coord_and_sampler_temp), 3, srv_unsigned, sampler,
                           dxbc::Src::R(grad_h_lod_temp), dxbc::Src::R(grad_v_temp),
                           srv_grad_component_count);
            } else {
              a_.OpSampleL(dxbc::Dest::R(layer_value_temp, used_result_nonzero_components),
                           dxbc::Src::R(coord_and_sampler_temp), 3, srv_unsigned, sampler, lod_src);
            }
          }
          a_.OpEndIf();
          a_.OpIf(true, is_any_signed_src);
          {
            load_border_sampler(sampler_binding_index_white);
            uint32_t signed_temp = PushSystemTemp();
            if (bindless_resources_used_) {
              assert_true(srv_selection_temp != UINT32_MAX);
              if (cbuffer_index_descriptor_indices_ == kBindingIndexUnallocated) {
                cbuffer_index_descriptor_indices_ = cbuffer_count_++;
              }
              uint32_t texture_bindless_descriptor_index =
                  texture_binding_signed.bindless_descriptor_index;
              a_.OpMov(dxbc::Dest::R(srv_selection_temp, 0b1000),
                       dxbc::Src::CB(cbuffer_index_descriptor_indices_,
                                     uint32_t(CbufferRegister::kDescriptorIndices),
                                     texture_bindless_descriptor_index >> 2)
                           .Select(texture_bindless_descriptor_index & 3));
            }
            if (grad_v_temp != UINT32_MAX) {
              assert_not_zero(grad_component_count);
              a_.OpSampleD(dxbc::Dest::R(signed_temp, used_result_nonzero_components),
                           dxbc::Src::R(coord_and_sampler_temp), 3, srv_signed, sampler_white,
                           dxbc::Src::R(grad_h_lod_temp), dxbc::Src::R(grad_v_temp),
                           srv_grad_component_count);
            } else {
              a_.OpSampleL(dxbc::Dest::R(signed_temp, used_result_nonzero_components),
                           dxbc::Src::R(coord_and_sampler_temp), 3, srv_signed, sampler_white,
                           lod_src);
            }
            if (get_border_color_frac) {
              a_.OpAdd(dxbc::Dest::R(layer_value_temp), dxbc::Src::R(signed_temp),
                       -dxbc::Src::R(layer_value_temp));
            } else {
              a_.OpMovC(dxbc::Dest::R(layer_value_temp, used_result_nonzero_components),
                        dxbc::Src::R(is_signed_temp), dxbc::Src::R(signed_temp),
                        dxbc::Src::R(layer_value_temp));
            }

            PopSystemTemp();
          }
          a_.OpEndIf();
          if (layer) {
            assert_true(layer_value_temp != system_temp_result_);

            a_.OpAdd(dxbc::Dest::R(layer_value_temp, used_result_nonzero_components),
                     dxbc::Src::R(layer_value_temp), -dxbc::Src::R(system_temp_result_));
            a_.OpMAd(dxbc::Dest::R(system_temp_result_, used_result_nonzero_components),
                     dxbc::Src::R(layer_value_temp), layer_lerp_factor_src,
                     dxbc::Src::R(system_temp_result_));

            a_.OpEndIf();

            PopSystemTemp();
          }
        }
      }
      if (instr.dimension == xenos::FetchOpDimension::k3DOrStacked) {
        a_.OpEndIf();
      }

      if (srv_selection_temp != UINT32_MAX) {
        PopSystemTemp();
      }

      PopSystemTemp();

      if (grad_v_temp != UINT32_MAX) {
        PopSystemTemp();
      }
      if (grad_h_lod_temp != UINT32_MAX) {
        PopSystemTemp();
      }
    }

    PopSystemTemp();

    if (instr.opcode == FetchOpcode::kTextureFetch) {
      assert_true(signs_temp != UINT32_MAX);
      dxbc::Src integer_scale_bits_packed = LoadSystemConstant(
          SystemConstants::Index::kTextureIntegerScaleBits,
          offsetof(SystemConstants, texture_integer_scale_bits) + sizeof(uint32_t) * tfetch_index,
          dxbc::Src::kXXXX);
      for (uint32_t i = 0; i < 4; ++i) {
        if (!(used_result_nonzero_components & (1 << i))) {
          continue;
        }
        dxbc::Dest component_dest(dxbc::Dest::R(system_temp_result_, 1 << i));
        dxbc::Src component_src(dxbc::Src::R(system_temp_result_).Select(i));
        a_.OpSwitch(dxbc::Src::R(signs_temp).Select(i));
        a_.OpCase(dxbc::Src::LU(uint32_t(xenos::TextureSign::kUnsignedBiased)));
        {
          uint32_t biased_temp = PushSystemTemp();
          a_.OpUBFE(dxbc::Dest::R(biased_temp, 0b0001), dxbc::Src::LU(4), dxbc::Src::LU(i * 6),
                    integer_scale_bits_packed);

          a_.OpIShL(dxbc::Dest::R(biased_temp, 0b0010), dxbc::Src::LU(1),
                    dxbc::Src::R(biased_temp, dxbc::Src::kXXXX));
          a_.OpUToF(dxbc::Dest::R(biased_temp, 0b0010),
                    dxbc::Src::R(biased_temp, dxbc::Src::kYYYY));

          a_.OpMAd(dxbc::Dest::R(biased_temp, 0b0100), dxbc::Src::R(biased_temp, dxbc::Src::kYYYY),
                   dxbc::Src::LF(2.0f), dxbc::Src::LF(-1.0f));
          a_.OpMul(dxbc::Dest::R(biased_temp, 0b0100), component_src,
                   dxbc::Src::R(biased_temp, dxbc::Src::kZZZZ));
          a_.OpAdd(dxbc::Dest::R(biased_temp, 0b0100), dxbc::Src::R(biased_temp, dxbc::Src::kZZZZ),
                   -dxbc::Src::R(biased_temp, dxbc::Src::kYYYY));

          a_.OpAdd(dxbc::Dest::R(biased_temp, 0b0010), dxbc::Src::R(biased_temp, dxbc::Src::kYYYY),
                   dxbc::Src::LF(-1.0f));
          a_.OpDiv(dxbc::Dest::R(biased_temp, 0b0100), dxbc::Src::R(biased_temp, dxbc::Src::kZZZZ),
                   dxbc::Src::R(biased_temp, dxbc::Src::kYYYY));
          a_.OpMAd(dxbc::Dest::R(biased_temp, 0b0010), component_src, dxbc::Src::LF(2.0f),
                   dxbc::Src::LF(-1.0f));
          a_.OpMovC(component_dest, dxbc::Src::R(biased_temp, dxbc::Src::kXXXX),
                    dxbc::Src::R(biased_temp, dxbc::Src::kZZZZ),
                    dxbc::Src::R(biased_temp, dxbc::Src::kYYYY));

          PopSystemTemp();
        }
        a_.OpBreak();
        a_.OpCase(dxbc::Src::LU(uint32_t(xenos::TextureSign::kGamma)));
        uint32_t gamma_temp = PushSystemTemp();

        PWLGammaToLinear(a_, system_temp_result_, i, system_temp_result_, i, false, gamma_temp, 0,
                         gamma_temp, 1);

        PopSystemTemp();
        a_.OpBreak();
        a_.OpEndSwitch();
      }

      uint32_t integer_scale_temp = PushSystemTemp();
      dxbc::Dest integer_scale_dest(
          dxbc::Dest::R(integer_scale_temp, used_result_nonzero_components));
      dxbc::Src integer_scale_src(dxbc::Src::R(integer_scale_temp));
      dxbc::Dest integer_scale_flags_dest(
          dxbc::Dest::R(signs_temp, used_result_nonzero_components));
      dxbc::Src integer_scale_flags_src(dxbc::Src::R(signs_temp));

      a_.OpAnd(dxbc::Dest::R(signs_temp, 0b0001), integer_scale_bits_packed,
               dxbc::Src::LU((UINT32_C(1) << 26) - 1));
      a_.OpIf(true, dxbc::Src::R(signs_temp, dxbc::Src::kXXXX));
      a_.OpAnd(dxbc::Dest::R(signs_temp, 0b0001), integer_scale_bits_packed,
               dxbc::Src::LU(UINT32_C(1) << 24));
      a_.OpIf(true, dxbc::Src::R(signs_temp, dxbc::Src::kXXXX));
      if (instr.AllowsPointSampling(use_computed_lod)) {
        a_.OpAnd(dxbc::Dest::R(signs_temp, 0b0001), integer_scale_bits_packed,
                 dxbc::Src::LU((UINT32_C(1) << 24) - 1));
        a_.OpIf(true, dxbc::Src::R(signs_temp, dxbc::Src::kXXXX));

        a_.OpUBFE(integer_scale_dest, dxbc::Src::LU(4), dxbc::Src::LU(0, 6, 12, 18),
                  integer_scale_bits_packed);
        a_.OpIShL(integer_scale_dest, dxbc::Src::LU(2), integer_scale_src);
        a_.OpUToF(integer_scale_dest, integer_scale_src);

        a_.OpAdd(integer_scale_flags_dest, integer_scale_src, dxbc::Src::LF(-1.0f));
        a_.OpMul(integer_scale_flags_dest, dxbc::Src::R(system_temp_result_),
                 integer_scale_flags_src);
        a_.OpRoundNE(integer_scale_flags_dest, integer_scale_flags_src);

        a_.OpMAd(integer_scale_flags_dest, integer_scale_flags_src, integer_scale_src,
                 integer_scale_flags_src);
        a_.OpMul(integer_scale_dest, integer_scale_src, integer_scale_src);
        a_.OpDiv(integer_scale_flags_dest, integer_scale_flags_src, integer_scale_src);

        a_.OpUBFE(integer_scale_dest, dxbc::Src::LU(6), dxbc::Src::LU(0, 6, 12, 18),
                  integer_scale_bits_packed);
        a_.OpIAdd(integer_scale_dest, integer_scale_src, dxbc::Src::LI(-1));
        a_.OpULT(integer_scale_dest, integer_scale_src, dxbc::Src::LU(15));
        a_.OpMovC(dxbc::Dest::R(system_temp_result_, used_result_nonzero_components),
                  integer_scale_src, integer_scale_flags_src, dxbc::Src::R(system_temp_result_));
        a_.OpEndIf();
      }

      a_.OpMul(integer_scale_dest, dxbc::Src::R(system_temp_result_), dxbc::Src::LF(65536.0f));
      a_.OpRoundNE(integer_scale_dest, integer_scale_src);
      a_.OpMul(integer_scale_dest, integer_scale_src, dxbc::Src::LF(1.0f / 65536.0f));
      a_.OpUBFE(integer_scale_flags_dest, dxbc::Src::LU(2), dxbc::Src::LU(4, 10, 16, 22),
                integer_scale_bits_packed);
      a_.OpMovC(dxbc::Dest::R(system_temp_result_, used_result_nonzero_components),
                integer_scale_flags_src, dxbc::Src::R(system_temp_result_), integer_scale_src);

      a_.OpIEq(integer_scale_flags_dest, integer_scale_flags_src,
               dxbc::Src::LU(uint32_t(xenos::TextureSign::kUnsignedBiased)));
      a_.OpMax(integer_scale_dest, dxbc::Src::R(system_temp_result_), dxbc::Src::LF(-1.0f));
      a_.OpMovC(dxbc::Dest::R(system_temp_result_, used_result_nonzero_components),
                integer_scale_flags_src, integer_scale_src, dxbc::Src::R(system_temp_result_));
      a_.OpElse();

      a_.OpUBFE(integer_scale_dest, dxbc::Src::LU(4), dxbc::Src::LU(0, 6, 12, 18),
                integer_scale_bits_packed);
      a_.OpIAdd(integer_scale_dest, integer_scale_src, dxbc::Src::LU(1));

      a_.OpUBFE(integer_scale_flags_dest, dxbc::Src::LU(2), dxbc::Src::LU(4, 10, 16, 22),
                integer_scale_bits_packed);
      a_.OpIAdd(integer_scale_flags_dest, integer_scale_flags_src, dxbc::Src::LI(-1));
      a_.OpULT(integer_scale_flags_dest, integer_scale_flags_src, dxbc::Src::LU(2));
      a_.OpIAdd(integer_scale_dest, integer_scale_src, integer_scale_flags_src);
      a_.OpIShL(integer_scale_dest, dxbc::Src::LU(1), integer_scale_src);
      a_.OpIAdd(integer_scale_dest, integer_scale_src, dxbc::Src::LI(-1));
      a_.OpUToF(integer_scale_dest, integer_scale_src);

      a_.OpMin(integer_scale_flags_dest, integer_scale_src, dxbc::Src::LF(0.5f));
      a_.OpAdd(integer_scale_flags_dest, integer_scale_flags_src, dxbc::Src::LF(-0.5f));
      a_.OpMax(integer_scale_dest, integer_scale_src, dxbc::Src::LF(0.5f));
      a_.OpMAd(dxbc::Dest::R(system_temp_result_, used_result_nonzero_components),
               dxbc::Src::R(system_temp_result_), integer_scale_src, integer_scale_flags_src);
      if (instr.AllowsPointSampling(use_computed_lod)) {
        a_.OpAnd(dxbc::Dest::R(signs_temp, 0b0001), integer_scale_bits_packed,
                 dxbc::Src::LU(UINT32_C(1) << 26));
        a_.OpIf(true, dxbc::Src::R(signs_temp, dxbc::Src::kXXXX));
        a_.OpRoundNE(dxbc::Dest::R(system_temp_result_, used_result_nonzero_components),
                     dxbc::Src::R(system_temp_result_));
        a_.OpEndIf();
      }
      a_.OpEndIf();
      a_.OpEndIf();
      PopSystemTemp();
    }
    if (signs_temp != UINT32_MAX) {
      PopSystemTemp();
    }
  }

  if (size_1d_width_minus_1_temp != UINT32_MAX) {
    PopSystemTemp();
  }
  if (size_and_is_3d_temp != UINT32_MAX) {
    PopSystemTemp();
  }

  if (instr.opcode == FetchOpcode::kTextureFetch) {
    uint32_t exp_adjust_temp = PushSystemTemp();
    a_.OpIBFE(dxbc::Dest::R(exp_adjust_temp, 0b0001), dxbc::Src::LU(6), dxbc::Src::LU(13),
              RequestTextureFetchConstantWord(tfetch_index, 3));
    a_.OpIMAd(dxbc::Dest::R(exp_adjust_temp, 0b0001),
              dxbc::Src::R(exp_adjust_temp, dxbc::Src::kXXXX), dxbc::Src::LI(int32_t(1) << 23),
              dxbc::Src::LF(1.0f));
    a_.OpMul(dxbc::Dest::R(system_temp_result_, used_result_nonzero_components),
             dxbc::Src::R(system_temp_result_), dxbc::Src::R(exp_adjust_temp, dxbc::Src::kXXXX));

    PopSystemTemp();
  }

  if (get_border_color_frac) {
    a_.OpMax(dxbc::Dest::R(system_temp_result_, 0b0001),
             dxbc::Src::R(system_temp_result_, dxbc::Src::kXXXX),
             dxbc::Src::R(system_temp_result_, dxbc::Src::kYYYY));
    a_.OpMax(dxbc::Dest::R(system_temp_result_, 0b0001),
             dxbc::Src::R(system_temp_result_, dxbc::Src::kXXXX),
             dxbc::Src::R(system_temp_result_, dxbc::Src::kZZZZ));
    a_.OpMax(dxbc::Dest::R(system_temp_result_, 0b0001),
             dxbc::Src::R(system_temp_result_, dxbc::Src::kXXXX),
             dxbc::Src::R(system_temp_result_, dxbc::Src::kWWWW));
    used_result_nonzero_components = 0b0001;
  }
  uint32_t used_result_zero_components = used_result_components & ~used_result_nonzero_components;
  if (used_result_zero_components) {
    a_.OpMov(dxbc::Dest::R(system_temp_result_, used_result_zero_components), dxbc::Src::LF(0.0f));
  }
  StoreResult(instr.result, dxbc::Src::R(system_temp_result_));
}

}
