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

#include <rex/graphics/pipeline/shader/spirv_shader_cache.h>

#include <thread>

#include <rex/assert.h>
#include <rex/logging.h>
#include <rex/math.h>
#include <rex/string/buffer.h>
#include <rex/graphics/register_file.h>
#include <rex/graphics/pipeline/render_target/cache.h>
#include <rex/graphics/pipeline/shader/spirv.h>
#include <rex/graphics/pipeline/shader/spirv_translator.h>

namespace rex::graphics {

GuestSpirvShaderCache::GuestSpirvShaderCache(Host& host, const RegisterFile& register_file,
                                             const RenderTargetCache& render_target_cache)
    : host_(host), register_file_(register_file), render_target_cache_(render_target_cache) {}

GuestSpirvShaderCache::~GuestSpirvShaderCache() {
  Shutdown();
}

bool GuestSpirvShaderCache::Initialize() {
  translator_ = host_.CreateTranslator();
  return translator_ != nullptr;
}

void GuestSpirvShaderCache::Shutdown() {
  translator_.reset();
}

std::unique_ptr<SpirvShaderTranslator> GuestSpirvShaderCache::CreateWorkerTranslator() const {
  return host_.CreateTranslator();
}

uint64_t GuestSpirvShaderCache::GetVertexShaderModification(
    const Shader& shader, Shader::HostVertexShaderType host_vertex_shader_type,
    uint32_t interpolator_mask, bool ps_param_gen_used) const {
  assert_true(shader.type() == xenos::ShaderType::kVertex);
  assert_true(shader.is_ucode_analyzed());
  const auto& regs = register_file_;

  SpirvShaderTranslator::Modification modification(translator_->GetDefaultVertexShaderModification(
      shader.GetDynamicAddressableRegisterCount(regs.Get<reg::SQ_PROGRAM_CNTL>().vs_num_reg),
      host_vertex_shader_type));

  modification.vertex.interpolator_mask = interpolator_mask;

  if (Shader::IsHostVertexShaderTypeDomain(host_vertex_shader_type)) {
    modification.vertex.tessellation_mode = regs.Get<reg::VGT_HOS_CNTL>().tess_mode;
  }

  auto pa_cl_clip_cntl = regs.Get<reg::PA_CL_CLIP_CNTL>();
  uint32_t user_clip_planes = pa_cl_clip_cntl.clip_disable ? 0 : pa_cl_clip_cntl.ucp_ena;
  modification.vertex.user_clip_plane_count = rex::bit_count(user_clip_planes);
  modification.vertex.user_clip_plane_cull =
      uint32_t(user_clip_planes && pa_cl_clip_cntl.ucp_cull_only_ena);

  modification.vertex.vertex_kill_and = uint32_t(
      (shader.writes_point_size_edge_flag_kill_vertex() & 0b100) && !pa_cl_clip_cntl.vtx_kill_or);

  if (host_vertex_shader_type == Shader::HostVertexShaderType::kPointListAsTriangleStrip) {
    modification.vertex.output_point_parameters = uint32_t(ps_param_gen_used);
  } else {
    modification.vertex.output_point_parameters =
        uint32_t((shader.writes_point_size_edge_flag_kill_vertex() & 0b001) &&
                 regs.Get<reg::VGT_DRAW_INITIATOR>().prim_type == xenos::PrimitiveType::kPointList);
  }

  return modification.value;
}

uint64_t GuestSpirvShaderCache::GetPixelShaderModification(
    const Shader& shader, uint32_t interpolator_mask, uint32_t param_gen_pos,
    reg::RB_DEPTHCONTROL normalized_depth_control, uint32_t normalized_color_mask,
    bool apply_polygon_offset_in_shader) const {
  assert_true(shader.type() == xenos::ShaderType::kPixel);
  assert_true(shader.is_ucode_analyzed());
  const auto& regs = register_file_;

  SpirvShaderTranslator::Modification modification(translator_->GetDefaultPixelShaderModification(
      shader.GetDynamicAddressableRegisterCount(regs.Get<reg::SQ_PROGRAM_CNTL>().ps_num_reg)));

  modification.pixel.interpolator_mask = interpolator_mask;
  modification.pixel.interpolators_centroid =
      interpolator_mask & ~xenos::GetInterpolatorSamplingPattern(
                              regs.Get<reg::RB_SURFACE_INFO>().msaa_samples,
                              regs.Get<reg::SQ_CONTEXT_MISC>().sc_sample_cntl,
                              regs.Get<reg::SQ_INTERPOLATOR_CNTL>().sampling_pattern);

  if (param_gen_pos < xenos::kMaxInterpolators) {
    modification.pixel.param_gen_enable = 1;
    modification.pixel.param_gen_interpolator = param_gen_pos;
    modification.pixel.param_gen_point =
        uint32_t(regs.Get<reg::VGT_DRAW_INITIATOR>().prim_type == xenos::PrimitiveType::kPointList);
  } else {
    modification.pixel.param_gen_enable = 0;
    modification.pixel.param_gen_interpolator = 0;
    modification.pixel.param_gen_point = 0;
  }

  if (render_target_cache_.GetPath() == RenderTargetCache::Path::kHostRenderTargets) {
    modification.pixel.resolution_scale_native = 0;

    using DepthStencilMode = SpirvShaderTranslator::Modification::DepthStencilMode;
    if (host_.depth_float24_convert_in_pixel_shader() && normalized_depth_control.z_enable &&
        regs.Get<reg::RB_DEPTH_INFO>().depth_format == xenos::DepthRenderTargetFormat::kD24FS8) {
      modification.pixel.depth_stencil_mode =
          apply_polygon_offset_in_shader
              ? (host_.depth_float24_round() ? DepthStencilMode::kFloat24RoundingPolygonOffset
                                             : DepthStencilMode::kFloat24TruncatingPolygonOffset)
              : (host_.depth_float24_round() ? DepthStencilMode::kFloat24Rounding
                                             : DepthStencilMode::kFloat24Truncating);
    } else {
      if (apply_polygon_offset_in_shader) {
        modification.pixel.depth_stencil_mode = DepthStencilMode::kPolygonOffset;
      } else {
        modification.pixel.depth_stencil_mode = DepthStencilMode::kNoModifiers;
      }
    }

    modification.pixel.rt0_blend_rgb_factor_for_premult = xenos::BlendFactor::kOne;
    modification.pixel.rt0_blend_a_factor_for_premult = xenos::BlendFactor::kOne;

    if (shader.writes_color_target(0)) {
      auto blend_control =
          regs.Get<reg::RB_BLENDCONTROL>(reg::RB_BLENDCONTROL::rt_register_indices[0]);
      if ((blend_control.color_comb_fcn == xenos::BlendOp::kMin ||
           blend_control.color_comb_fcn == xenos::BlendOp::kMax) &&
          blend_control.color_srcblend == xenos::BlendFactor::kSrcAlpha &&
          blend_control.color_destblend == xenos::BlendFactor::kOne) {
        modification.pixel.rt0_blend_rgb_factor_for_premult = xenos::BlendFactor::kSrcAlpha;
      }
      if ((blend_control.alpha_comb_fcn == xenos::BlendOp::kMin ||
           blend_control.alpha_comb_fcn == xenos::BlendOp::kMax) &&
          blend_control.alpha_srcblend == xenos::BlendFactor::kSrcAlpha &&
          blend_control.alpha_destblend == xenos::BlendFactor::kOne) {
        modification.pixel.rt0_blend_a_factor_for_premult = xenos::BlendFactor::kSrcAlpha;
      }
    }

    modification.pixel.color_targets_used = (((normalized_color_mask >> 0) & 0xF) ? 1 : 0) |
                                            (((normalized_color_mask >> 4) & 0xF) ? 2 : 0) |
                                            (((normalized_color_mask >> 8) & 0xF) ? 4 : 0) |
                                            (((normalized_color_mask >> 12) & 0xF) ? 8 : 0);
  } else {
    modification.pixel.set_fsi_msaa_samples(regs.Get<reg::RB_SURFACE_INFO>().msaa_samples);

    bool any_blending = false;
    for (uint32_t i = 0; i < xenos::kMaxColorRenderTargets; ++i) {
      if (!shader.writes_color_target(i) || !((normalized_color_mask >> (i * 4)) & 0xF)) {
        continue;
      }
      modification.pixel.set_fsi_rt_format(
          i, regs.Get<reg::RB_COLOR_INFO>(reg::RB_COLOR_INFO::rt_register_indices[i]).color_format);

      if ((regs.Get<reg::RB_BLENDCONTROL>(reg::RB_BLENDCONTROL::rt_register_indices[i]).value &
           0x1FFF1FFF) != 0x00010001) {
        any_blending = true;
      }
    }

    modification.pixel.set_fsi_no_blending(!any_blending);
  }

  return modification.value;
}

Shader::Translation* GuestSpirvShaderCache::EnsureTranslation(SpirvShader& shader,
                                                              uint64_t modification) {
  if (!shader.is_ucode_analyzed()) {
    string::StringBuffer ucode_disasm;
    shader.AnalyzeUcode(ucode_disasm);
  }
  return shader.GetOrCreateTranslation(modification);
}

Shader::Translation* GuestSpirvShaderCache::TranslateSpirv(SpirvShaderTranslator& translator,
                                                           Shader::Translation& translation,
                                                           bool use_try_claim) {
  if (!translation.is_translated()) {
    bool should_translate = true;

    (void)use_try_claim;
    if (should_translate) {
      translator.TranslateAnalyzedShader(translation);

      translation.PublishTranslated();
    }
  }
  return translation.is_valid() ? &translation : nullptr;
}

Shader::Translation* GuestSpirvShaderCache::EnsureAndTranslate(SpirvShader& shader,
                                                               uint64_t modification) {
  Shader::Translation* translation = EnsureTranslation(shader, modification);
  return TranslateSpirv(*translator_, *translation, false);
}

bool GuestSpirvShaderCache::GetGeometryShaderKey(PipelineGeometryShader geometry_shader_type,
                                                 uint64_t vertex_shader_modification,
                                                 uint64_t pixel_shader_modification,
                                                 GeometryShaderKey& key_out) {
  if (geometry_shader_type == PipelineGeometryShader::kNone) {
    return false;
  }
  SpirvShaderTranslator::Modification vertex_mod(vertex_shader_modification);
  SpirvShaderTranslator::Modification pixel_mod(pixel_shader_modification);

  if (vertex_mod.vertex.host_vertex_shader_type ==
          Shader::HostVertexShaderType::kPointListAsTriangleStrip ||
      vertex_mod.vertex.host_vertex_shader_type ==
          Shader::HostVertexShaderType::kRectangleListAsTriangleStrip) {
    REXGPU_ERROR(
        "GetGeometryShaderKey: AsTriangleStrip vertex shader types should not "
        "be used with geometry shaders");
    return false;
  }
  GeometryShaderKey key;
  key.type = geometry_shader_type;
  key.interpolator_count = rex::bit_count(vertex_mod.vertex.interpolator_mask);
  key.user_clip_plane_count = vertex_mod.vertex.user_clip_plane_count;
  key.user_clip_plane_cull = vertex_mod.vertex.user_clip_plane_cull;
  key.has_vertex_kill_and = vertex_mod.vertex.vertex_kill_and;
  key.has_point_size = vertex_mod.vertex.output_point_parameters;
  key.has_point_coordinates = pixel_mod.pixel.param_gen_point;
  key_out = key;
  return true;
}

}
