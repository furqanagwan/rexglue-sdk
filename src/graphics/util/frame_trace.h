/**
 * @file        graphics/util/frame_trace.h
 * @brief       Per-draw trace of chosen guest frames, and draw skipping by shader
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#pragma once

#include <cstdint>
#include <cstdio>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include <rex/graphics/xenos.h>

namespace rex::graphics {

class RegisterFile;
class Shader;

// Tools for tracking down rendering bugs without a graphics debugger:
//
//  gpu_trace_frame=N   writes one JSON line per draw of guest frame N (and the
//                      gpu_trace_frame_count - 1 frames after it) to
//                      gpu_trace_path: render target, shaders, textures.
//  gpu_trace_shaders=VS[:PS],...
//                      traces only the draws of these shader programs, which is
//                      what a native renderer's work needs: a whole frame of a
//                      busy scene is hundreds of megabytes, one geometry
//                      program is a few.
//  gpu_trace_constants=N
//                      records the first N vertex shader constant vectors of
//                      each traced draw (the transform chain lives there).
//  gpu_trace_vertex_buffers=true
//                      records each traced draw's vertex buffers: fetch slot,
//                      guest address, size and stride.
//  gpu_skip_pixel_shaders=HASH,...
//                      drops draws whose pixel shader hash is listed, to bisect
//                      which draw causes an artifact.
//
// All are off by default and cost one branch per draw when unused.
class FrameTrace {
 public:
  // Call once per guest swap with the index of the frame that just ended.
  void OnSwap(uint64_t frame_index);
  // Returns false when the draw should be skipped.
  bool OnDraw(const RegisterFile& regs, const Shader* vertex_shader, const Shader* pixel_shader,
              xenos::PrimitiveType primitive_type, uint32_t index_count, bool indexed);

  // A gpu_trace_shaders entry: a vertex hash, a pixel hash, or a pair. 0 is a
  // wildcard, so "VS" matches that vertex shader with any pixel shader.
  struct ShaderMatch {
    uint64_t vertex_hash = 0;
    uint64_t pixel_hash = 0;
  };
  static std::vector<ShaderMatch> ParseShaderMatches(const std::string& text);

 private:
  void UpdateSkipList();
  void UpdateShaderMatches();
  bool Traced(const Shader* vertex_shader, const Shader* pixel_shader) const;

  FILE* file_ = nullptr;
  uint64_t frame_ = 0;
  uint32_t draw_ = 0;
  std::string skip_list_text_;
  std::unordered_set<uint64_t> skipped_pixel_shaders_;
  std::string shader_matches_text_;
  std::vector<ShaderMatch> shader_matches_;
};

}  // namespace rex::graphics
