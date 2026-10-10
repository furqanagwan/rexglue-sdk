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

#ifndef REX_GRAPHICS_PIPELINE_SHADER_GUEST_SPIRV_SHADER_CACHE_H_
#define REX_GRAPHICS_PIPELINE_SHADER_GUEST_SPIRV_SHADER_CACHE_H_

#include <cstdint>
#include <memory>
#include <vector>

#include <rex/assert.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/pipeline/shader/shader.h>
#include <rex/graphics/xenos.h>

namespace rex::graphics {

class RegisterFile;
class RenderTargetCache;
class SpirvShader;
class SpirvShaderTranslator;

enum class PipelineGeometryShader : uint32_t {
  kNone,
  kPointList,
  kRectangleList,
  kQuadList,

  kLineList,
};

class GuestSpirvShaderCache {
 public:
  class Host {
   public:
    virtual ~Host() = default;

    virtual std::unique_ptr<SpirvShaderTranslator> CreateTranslator() const = 0;

    virtual bool depth_float24_round() const = 0;
    virtual bool depth_float24_convert_in_pixel_shader() const = 0;
  };

  GuestSpirvShaderCache(Host& host, const RegisterFile& register_file,
                        const RenderTargetCache& render_target_cache);
  ~GuestSpirvShaderCache();

  bool Initialize();
  void Shutdown();

  SpirvShaderTranslator& translator() const { return *translator_; }

  std::unique_ptr<SpirvShaderTranslator> CreateWorkerTranslator() const;

  uint64_t GetVertexShaderModification(const Shader& shader,
                                       Shader::HostVertexShaderType host_vertex_shader_type,
                                       uint32_t interpolator_mask, bool ps_param_gen_used) const;
  uint64_t GetPixelShaderModification(const Shader& shader, uint32_t interpolator_mask,
                                      uint32_t param_gen_pos,
                                      reg::RB_DEPTHCONTROL normalized_depth_control,
                                      uint32_t normalized_color_mask,
                                      bool apply_polygon_offset_in_shader) const;

  Shader::Translation* EnsureTranslation(SpirvShader& shader, uint64_t modification);

  Shader::Translation* TranslateSpirv(SpirvShaderTranslator& translator,
                                      Shader::Translation& translation, bool use_try_claim);

  Shader::Translation* EnsureAndTranslate(SpirvShader& shader, uint64_t modification);

  union GeometryShaderKey {
    uint32_t key;
    struct {
      PipelineGeometryShader type : 3;
      uint32_t interpolator_count : 5;

      uint32_t user_clip_plane_count : 3;
      uint32_t user_clip_plane_cull : 1;
      uint32_t has_vertex_kill_and : 1;
      uint32_t has_point_size : 1;
      uint32_t has_point_coordinates : 1;
    };
    GeometryShaderKey() : key(0) { static_assert_size(*this, sizeof(key)); }
    struct Hasher {
      size_t operator()(const GeometryShaderKey& key) const {
        return std::hash<uint32_t>{}(key.key);
      }
    };
    bool operator==(const GeometryShaderKey& other) const { return key == other.key; }
    bool operator!=(const GeometryShaderKey& other) const { return !(*this == other); }
  };

  static bool GetGeometryShaderKey(PipelineGeometryShader geometry_shader_type,
                                   uint64_t vertex_shader_modification,
                                   uint64_t pixel_shader_modification, GeometryShaderKey& key_out);

 private:
  Host& host_;
  const RegisterFile& register_file_;
  const RenderTargetCache& render_target_cache_;

  std::unique_ptr<SpirvShaderTranslator> translator_;
};

}

#endif
