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

#include <rex/graphics/pipeline/shader/spirv_translator.h>
#include <climits>
#include <cmath>
#include <fmt/format.h>
#include <SPIRV/GLSL.std.450.h>
#include <rex/assert.h>
#include <rex/math.h>
#include <rex/graphics/pipeline/render_target/cache.h>
#include <rex/graphics/pipeline/shader/spirv_compatibility.h>

namespace rex::graphics {

size_t SpirvShaderTranslator::FindOrAddTextureBinding(uint32_t fetch_constant,
                                                      xenos::FetchOpDimension dimension,
                                                      bool is_signed) {
  if (dimension == xenos::FetchOpDimension::k1D) {
    dimension = xenos::FetchOpDimension::k2D;
  }
  for (size_t i = 0; i < texture_bindings_.size(); ++i) {
    const TextureBinding& texture_binding = texture_bindings_[i];
    if (texture_binding.fetch_constant == fetch_constant &&
        texture_binding.dimension == dimension && texture_binding.is_signed == is_signed) {
      return i;
    }
  }

  size_t new_texture_binding_index = texture_bindings_.size();
  TextureBinding& new_texture_binding = texture_bindings_.emplace_back();
  new_texture_binding.fetch_constant = fetch_constant;
  new_texture_binding.dimension = dimension;
  new_texture_binding.is_signed = is_signed;
  spv::Dim type_dimension;
  bool is_array;
  const char* dimension_name;
  switch (dimension) {
    case xenos::FetchOpDimension::k3DOrStacked:
      type_dimension = spv::Dim3D;
      is_array = false;
      dimension_name = "3d";
      break;
    case xenos::FetchOpDimension::kCube:
      type_dimension = spv::DimCube;
      is_array = false;
      dimension_name = "cube";
      break;
    default:
      type_dimension = spv::Dim2D;
      is_array = true;
      dimension_name = "2d";
  }
  new_texture_binding.variable = builder_->createVariable(
      spv::NoPrecision, spv::StorageClassUniformConstant,
      builder_->makeImageType(type_float_, type_dimension, false, is_array, false, 1,
                              spv::ImageFormatUnknown),
      fmt::format("xe_texture{}_{}_{}", fetch_constant, dimension_name, is_signed ? 's' : 'u')
          .c_str());
  builder_->addDecoration(
      new_texture_binding.variable, spv::DecorationDescriptorSet,
      int(is_vertex_shader() ? kDescriptorSetTexturesVertex : kDescriptorSetTexturesPixel));
  builder_->addDecoration(new_texture_binding.variable, spv::DecorationBinding,
                          int(new_texture_binding_index));
  if (features_.spirv_version >= spv::Spv_1_4) {
    main_interface_.push_back(new_texture_binding.variable);
  }
  return new_texture_binding_index;
}

size_t SpirvShaderTranslator::FindOrAddSamplerBinding(
    uint32_t fetch_constant, xenos::TextureFilter mag_filter, xenos::TextureFilter min_filter,
    xenos::TextureFilter mip_filter, xenos::AnisoFilter aniso_filter,
    std::optional<xenos::BorderColor> forced_border_color) {
  if (aniso_filter != xenos::AnisoFilter::kUseFetchConst) {
    aniso_filter = std::min(aniso_filter, xenos::AnisoFilter::kMax_16_1);
  }
  for (size_t i = 0; i < sampler_bindings_.size(); ++i) {
    const SamplerBinding& sampler_binding = sampler_bindings_[i];
    if (sampler_binding.fetch_constant == fetch_constant &&
        sampler_binding.mag_filter == mag_filter && sampler_binding.min_filter == min_filter &&
        sampler_binding.mip_filter == mip_filter && sampler_binding.aniso_filter == aniso_filter &&
        sampler_binding.border_color_forced == forced_border_color.has_value() &&
        (!forced_border_color || sampler_binding.forced_border_color == *forced_border_color)) {
      return i;
    }
  }

  size_t new_sampler_binding_index = sampler_bindings_.size();
  SamplerBinding& new_sampler_binding = sampler_bindings_.emplace_back();
  new_sampler_binding.fetch_constant = fetch_constant;
  new_sampler_binding.mag_filter = mag_filter;
  new_sampler_binding.min_filter = min_filter;
  new_sampler_binding.mip_filter = mip_filter;
  new_sampler_binding.aniso_filter = aniso_filter;
  new_sampler_binding.border_color_forced = forced_border_color.has_value();
  new_sampler_binding.forced_border_color =
      forced_border_color.value_or(xenos::BorderColor::k_ABGR_Black);
  std::ostringstream name;
  static constexpr char kFilterSuffixes[] = {'p', 'l', 'b', 'f'};
  name << "xe_sampler" << fetch_constant << '_' << kFilterSuffixes[uint32_t(mag_filter)]
       << kFilterSuffixes[uint32_t(min_filter)] << kFilterSuffixes[uint32_t(mip_filter)];
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
  new_sampler_binding.variable =
      builder_->createVariable(spv::NoPrecision, spv::StorageClassUniformConstant,
                               builder_->makeSamplerType(), name.str().c_str());
  builder_->addDecoration(
      new_sampler_binding.variable, spv::DecorationDescriptorSet,
      int(is_vertex_shader() ? kDescriptorSetTexturesVertex : kDescriptorSetTexturesPixel));

  if (features_.spirv_version >= spv::Spv_1_4) {
    main_interface_.push_back(new_sampler_binding.variable);
  }
  return new_sampler_binding_index;
}

void SpirvShaderTranslator::SampleTexture(spv::Builder::TextureParameters& texture_parameters,
                                          spv::ImageOperandsMask image_operands_mask,
                                          spv::Id image_unsigned, spv::Id image_signed,
                                          spv::Id sampler_unsigned, spv::Id sampler_signed,
                                          spv::Id is_any_unsigned, spv::Id is_any_signed,
                                          spv::Id& result_unsigned_out, spv::Id& result_signed_out,
                                          spv::Id lerp_factor, spv::Id lerp_first_unsigned,
                                          spv::Id lerp_first_signed) {
  for (uint32_t i = 0; i < 2; ++i) {
    SpirvBuilder::IfBuilder sign_if(i ? is_any_signed : is_any_unsigned,
                                    spv::SelectionControlDontFlattenMask, *builder_);
    spv::Id sign_result;
    {
      spv::Id image = i ? image_signed : image_unsigned;

      texture_parameters.sampler = builder_->createBinOp(
          spv::OpSampledImage, builder_->makeSampledImageType(builder_->getTypeId(image)), image,
          i ? sampler_signed : sampler_unsigned);
      sign_result =
          builder_->createTextureCall(spv::NoPrecision, type_float4_, false, false, false, false,
                                      false, texture_parameters, image_operands_mask);
      if (lerp_factor != spv::NoResult) {
        spv::Id lerp_first = i ? lerp_first_signed : lerp_first_unsigned;
        if (lerp_first != spv::NoResult) {
          spv::Id lerp_difference = builder_->createNoContractionBinOp(
              spv::OpVectorTimesScalar, type_float4_,
              builder_->createNoContractionBinOp(spv::OpFSub, type_float4_, sign_result,
                                                 lerp_first),
              lerp_factor);
          sign_result = builder_->createNoContractionBinOp(spv::OpFAdd, type_float4_, lerp_first,
                                                           lerp_difference);
        }
      }
    }
    sign_if.makeEndIf();

    (i ? result_signed_out : result_unsigned_out) =
        sign_if.createMergePhi(sign_result, const_float4_0_);
  }
}

spv::Id SpirvShaderTranslator::QueryTextureLod(spv::Builder::TextureParameters& texture_parameters,
                                               spv::Id image_unsigned, spv::Id image_signed,
                                               spv::Id sampler, spv::Id is_all_signed) {
  SpirvBuilder::IfBuilder if_signed(is_all_signed, spv::SelectionControlDontFlattenMask, *builder_);
  spv::Id lod_signed;
  {
    texture_parameters.sampler = builder_->createBinOp(
        spv::OpSampledImage, builder_->makeSampledImageType(builder_->getTypeId(image_signed)),
        image_signed, sampler);
    lod_signed = builder_->createCompositeExtract(
        builder_->createTextureQueryCall(spv::OpImageQueryLod, texture_parameters, false),
        type_float_, 1);
  }
  if_signed.makeBeginElse();
  spv::Id lod_unsigned;
  {
    texture_parameters.sampler = builder_->createBinOp(
        spv::OpSampledImage, builder_->makeSampledImageType(builder_->getTypeId(image_unsigned)),
        image_unsigned, sampler);
    lod_unsigned = builder_->createCompositeExtract(
        builder_->createTextureQueryCall(spv::OpImageQueryLod, texture_parameters, false),
        type_float_, 1);
  }
  if_signed.makeEndIf();
  return if_signed.createMergePhi(lod_signed, lod_unsigned);
}

}
