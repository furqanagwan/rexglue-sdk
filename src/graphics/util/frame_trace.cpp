/**
 * @file        graphics/util/frame_trace.cpp
 * @brief       Per-draw trace of chosen guest frames, and draw skipping by shader
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#include "frame_trace.h"

#include <cinttypes>

#include <fmt/format.h>

#include <rex/cvar.h>
#include <rex/filesystem.h>
#include <rex/graphics/pipeline/shader/shader.h>
#include <rex/graphics/pipeline/texture/info.h>
#include <rex/graphics/register_file.h>
#include <rex/graphics/registers.h>
#include <rex/logging.h>

REXCVAR_DEFINE_INT32(gpu_trace_frame, 0, "GPU/Debug",
                     "Trace every draw of this guest frame (counted from 1) to gpu_trace_path. "
                     "0 disables tracing.")
    .range(0, INT32_MAX);
REXCVAR_DEFINE_INT32(gpu_trace_frame_count, 1, "GPU/Debug",
                     "Number of consecutive frames to trace, starting at gpu_trace_frame.")
    .range(1, 600);
REXCVAR_DEFINE_STRING(gpu_trace_path, "gpu_trace.jsonl", "GPU/Debug",
                      "File the draw trace is written to, one JSON object per line.");
REXCVAR_DEFINE_STRING(gpu_skip_pixel_shaders, "", "GPU/Debug",
                      "Comma-separated pixel shader hashes (as written in the trace) whose "
                      "draws are dropped. Used to find which draw causes an artifact.")
    .lifecycle(rex::cvar::Lifecycle::kHotReload);

namespace rex::graphics {

void FrameTrace::OnSwap(uint64_t frame_index) {
  const uint64_t first = static_cast<uint64_t>(REXCVAR_GET(gpu_trace_frame));
  if (first == 0) {
    return;
  }
  const uint64_t next = frame_index + 1;
  const uint64_t end = first + static_cast<uint64_t>(REXCVAR_GET(gpu_trace_frame_count));
  if (next == first && !file_) {
    const std::string path = REXCVAR_GET(gpu_trace_path);
    file_ = rex::filesystem::OpenFile(rex::to_path(path), "w");
    if (file_) {
      REXGPU_INFO("gpu_trace: tracing frames {}..{} to {}", first, end - 1, path);
    } else {
      REXGPU_WARN("gpu_trace: cannot open {}", path);
    }
  } else if (next == end && file_) {
    std::fclose(file_);
    file_ = nullptr;
    REXGPU_INFO("gpu_trace: done");
  }
  frame_ = next;
  draw_ = 0;
}

void FrameTrace::UpdateSkipList() {
  const std::string text = REXCVAR_GET(gpu_skip_pixel_shaders);
  if (text == skip_list_text_) {
    return;
  }
  skip_list_text_ = text;
  skipped_pixel_shaders_.clear();
  size_t start = 0;
  while (start < text.size()) {
    size_t end = text.find(',', start);
    if (end == std::string::npos) {
      end = text.size();
    }
    std::string item = text.substr(start, end - start);
    if (!item.empty()) {
      skipped_pixel_shaders_.insert(std::strtoull(item.c_str(), nullptr, 16));
    }
    start = end + 1;
  }
  REXGPU_INFO("gpu_trace: skipping draws of {} pixel shader(s)", skipped_pixel_shaders_.size());
}

bool FrameTrace::OnDraw(const RegisterFile& regs, const Shader* vertex_shader,
                        const Shader* pixel_shader, xenos::PrimitiveType primitive_type,
                        uint32_t index_count, bool indexed) {
  UpdateSkipList();
  const bool skipped = pixel_shader && !skipped_pixel_shaders_.empty() &&
                       skipped_pixel_shaders_.contains(pixel_shader->ucode_data_hash());
  if (!file_) {
    return !skipped;
  }

  const auto surface = regs.Get<reg::RB_SURFACE_INFO>();
  const auto color = regs.Get<reg::RB_COLOR_INFO>();
  std::string line = fmt::format(
      R"({{"frame":{},"draw":{},"skipped":{},"primitive":{},"indices":{},"indexed":{},)"
      R"("edram_mode":{},"surface_pitch":{},"msaa":{},"color_format":"{}",)"
      R"("vs":"{:016X}","ps":"{}","textures":[)",
      frame_, draw_++, skipped, static_cast<uint32_t>(primitive_type), index_count, indexed,
      static_cast<uint32_t>(regs.Get<reg::RB_MODECONTROL>().edram_mode), surface.surface_pitch,
      1u << static_cast<uint32_t>(surface.msaa_samples),
      xenos::GetColorRenderTargetFormatName(color.color_format),
      vertex_shader ? vertex_shader->ucode_data_hash() : 0,
      pixel_shader ? fmt::format("{:016X}", pixel_shader->ucode_data_hash()) : std::string());

  bool first_texture = true;
  for (const Shader* shader : {vertex_shader, pixel_shader}) {
    if (!shader) {
      continue;
    }
    for (const auto& binding : shader->texture_bindings()) {
      const auto fetch = regs.GetTextureFetch(binding.fetch_constant);
      const FormatInfo* info = FormatInfo::Get(static_cast<uint32_t>(fetch.format));
      line += fmt::format(
          R"({}{{"stage":"{}","fetch":{},"format":"{}","width":{},"height":{},"address":"0x{:08X}","dimension":{},"swizzle":"0x{:03X}","sign":"{}{}{}{}"}})",
          first_texture ? "" : ",", shader == pixel_shader ? "ps" : "vs", binding.fetch_constant,
          info ? info->name : "unknown", fetch.size_2d.width + 1, fetch.size_2d.height + 1,
          fetch.base_address << 12, static_cast<uint32_t>(fetch.dimension), fetch.swizzle,
          static_cast<uint32_t>(fetch.sign_x), static_cast<uint32_t>(fetch.sign_y),
          static_cast<uint32_t>(fetch.sign_z), static_cast<uint32_t>(fetch.sign_w));
      first_texture = false;
    }
  }
  line += "]}\n";
  std::fputs(line.c_str(), file_);
  return !skipped;
}

}  // namespace rex::graphics
