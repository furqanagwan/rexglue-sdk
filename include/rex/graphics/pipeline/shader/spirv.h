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

#ifndef REX_GRAPHICS_PIPELINE_SHADER_SPIRV_SHADER_H_
#define REX_GRAPHICS_PIPELINE_SHADER_SPIRV_SHADER_H_

#include <atomic>
#include <vector>

#include <rex/graphics/pipeline/shader/shader.h>
#include <rex/graphics/xenos.h>

namespace rex::graphics {

class SpirvShaderTranslator;

class SpirvShader : public Shader {
 public:
  class SpirvTranslation : public Translation {
   public:
    explicit SpirvTranslation(SpirvShader& shader, uint64_t modification)
        : Translation(shader, modification) {}
  };

  explicit SpirvShader(xenos::ShaderType shader_type, uint64_t ucode_data_hash,
                       const uint32_t* ucode_dwords, size_t ucode_dword_count,
                       std::endian ucode_source_endian = std::endian::big);

  // Resource bindings are gathered after the successful translation of any
  // modification for simplicity of translation (and they don't depend on
  // modification bits).

  struct TextureBinding {
    uint32_t fetch_constant : 5;
    // Stacked and 3D are separate TextureBindings.
    xenos::FetchOpDimension dimension : 2;
    uint32_t is_signed : 1;
  };
  // Safe to hash and compare with memcmp for layout hashing.
  const std::vector<TextureBinding>& GetTextureBindingsAfterTranslation() const {
    return texture_bindings_;
  }
  const uint32_t GetUsedTextureMaskAfterTranslation() const { return used_texture_mask_; }

  struct SamplerBinding {
    uint32_t fetch_constant : 5;
    xenos::TextureFilter mag_filter : 2;
    xenos::TextureFilter min_filter : 2;
    xenos::TextureFilter mip_filter : 2;
    xenos::AnisoFilter aniso_filter : 3;
  };
  const std::vector<SamplerBinding>& GetSamplerBindingsAfterTranslation() const {
    return sampler_bindings_;
  }

  // True once a translation has gathered the resource bindings above. Set with
  // release ordering after the binding vectors are filled (which may happen on
  // a pipeline creation thread), so a draw-thread reader that sees this true
  // (acquire) is guaranteed the bindings are fully written and immutable.
  bool bindings_ready() const { return bindings_ready_.load(std::memory_order_acquire); }

 protected:
  Translation* CreateTranslationInstance(uint64_t modification) override;

 private:
  friend class SpirvShaderTranslator;

  std::atomic_flag bindings_setup_entered_ = ATOMIC_FLAG_INIT;
  std::atomic<bool> bindings_ready_{false};
  std::vector<TextureBinding> texture_bindings_;
  std::vector<SamplerBinding> sampler_bindings_;
  uint32_t used_texture_mask_ = 0;
};

}  // namespace rex::graphics

#endif  // REX_GRAPHICS_PIPELINE_SHADER_SPIRV_SHADER_H_
