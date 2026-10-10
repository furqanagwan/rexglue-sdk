#pragma once
/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2015 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include <memory>
#include <set>
#include <string>
#include <vector>

#include <rex/graphics/format/ucode.h>
#include <rex/graphics/pipeline/shader/shader.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/xenos.h>
#include <rex/math.h>
#include <rex/string/buffer.h>

namespace rex::graphics {

class ShaderTranslator {
 public:
  virtual ~ShaderTranslator();

  virtual uint64_t GetDefaultVertexShaderModification(
      uint32_t, Shader::HostVertexShaderType = Shader::HostVertexShaderType::kVertex) const {
    return 0;
  }
  virtual uint64_t GetDefaultPixelShaderModification(uint32_t) const { return 0; }

  bool TranslateAnalyzedShader(Shader::Translation& translation);

 protected:
  ShaderTranslator();

  virtual void Reset();

  Shader::Translation& current_translation() const { return *translation_; }
  Shader& current_shader() const { return current_translation().shader(); }

  virtual uint32_t GetModificationRegisterCount() const { return xenos::kMaxShaderTempRegisters; }

  bool is_vertex_shader() const { return current_shader().type() == xenos::ShaderType::kVertex; }

  bool is_pixel_shader() const { return current_shader().type() == xenos::ShaderType::kPixel; }

  bool TextureFetchUsesComputedLod(const ParsedTextureFetchInstruction& instr) const {
    return instr.attributes.use_computed_lod &&
           (is_pixel_shader() || instr.attributes.use_register_gradients);
  }

  uint32_t register_count() const { return register_count_; }

  virtual void EmitTranslationError(const char* message, bool is_fatal = true);

  virtual void StartTranslation() {}

  virtual std::vector<uint8_t> CompleteTranslation() { return std::vector<uint8_t>(); }

  virtual void PostTranslation() {}

  void set_host_disassembly(Shader::Translation& translation, std::string value) {
    translation.host_disassembly_ = std::move(value);
  }

  virtual void PreProcessControlFlowInstructions(std::vector<ucode::ControlFlowInstruction>) {}

  virtual void ProcessLabel(uint32_t) {}

  virtual void ProcessControlFlowNopInstruction(uint32_t) {}

  virtual void ProcessControlFlowInstructionBegin(uint32_t) {}

  virtual void ProcessControlFlowInstructionEnd(uint32_t) {}

  virtual void ProcessExecInstructionBegin(const ParsedExecInstruction&) {}

  virtual void ProcessExecInstructionEnd(const ParsedExecInstruction&) {}

  virtual void ProcessLoopStartInstruction(const ParsedLoopStartInstruction&) {}

  virtual void ProcessLoopEndInstruction(const ParsedLoopEndInstruction&) {}

  virtual void ProcessCallInstruction(const ParsedCallInstruction&) {}

  virtual void ProcessReturnInstruction(const ParsedReturnInstruction&) {}

  virtual void ProcessJumpInstruction(const ParsedJumpInstruction&) {}

  virtual void ProcessAllocInstruction(const ParsedAllocInstruction&, uint8_t) {}

  virtual void ProcessVertexFetchInstruction(const ParsedVertexFetchInstruction&) {}

  virtual void ProcessTextureFetchInstruction(const ParsedTextureFetchInstruction&) {}

  virtual void ProcessAluInstruction(const ParsedAluInstruction&, uint8_t) {}

 private:
  void TranslateControlFlowInstruction(const ucode::ControlFlowInstruction& cf);
  void TranslateExecInstructions(const ParsedExecInstruction& instr);

  Shader::Translation* translation_ = nullptr;

  std::vector<Shader::Error> errors_;

  uint32_t register_count_ = 0;

  uint32_t cf_index_ = 0;

  ucode::VertexFetchInstruction previous_vfetch_full_;
};

}
