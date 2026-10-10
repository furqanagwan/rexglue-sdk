#pragma once
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
#include <atomic>
#include <cstdint>
#include <filesystem>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <rex/graphics/format/ucode.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/xenos.h>
#include <rex/math.h>
#include <rex/string/buffer.h>
#include <rex/types.h>

namespace rex::graphics {

enum class InstructionStorageTarget {

  kNone,

  kRegister,

  kInterpolator,

  kPosition,

  kPointSizeEdgeFlagKillVertex,

  kExportAddress,

  kExportData,

  kColor,

  kDepth,
};

constexpr uint32_t GetInstructionStorageTargetUsedComponentCount(InstructionStorageTarget target) {
  switch (target) {
    case InstructionStorageTarget::kNone:
      return 0;
    case InstructionStorageTarget::kPointSizeEdgeFlagKillVertex:
      return 3;
    case InstructionStorageTarget::kDepth:
      return 1;
    default:
      return 4;
  }
}

enum class InstructionStorageAddressingMode {

  kAbsolute,

  kAddressRegisterRelative,

  kLoopRelative,
};

enum class SwizzleSource {

  kX,

  kY,

  kZ,

  kW,

  k0,

  k1,
};

constexpr SwizzleSource GetSwizzleFromComponentIndex(uint32_t i) {
  return static_cast<SwizzleSource>(i);
}
constexpr SwizzleSource GetSwizzledAluSourceComponent(uint32_t swizzle, uint32_t component_index) {
  return GetSwizzleFromComponentIndex(
      ucode::AluInstruction::GetSwizzledComponentIndex(swizzle, component_index));
}
inline char GetCharForComponentIndex(uint32_t i) {
  const static char kChars[] = {'x', 'y', 'z', 'w'};
  return kChars[i];
}
inline char GetCharForSwizzle(SwizzleSource swizzle_source) {
  const static char kChars[] = {'x', 'y', 'z', 'w', '0', '1'};
  return kChars[static_cast<uint32_t>(swizzle_source)];
}

struct InstructionResult {
  InstructionStorageTarget storage_target = InstructionStorageTarget::kNone;

  uint32_t storage_index = 0;

  InstructionStorageAddressingMode storage_addressing_mode =
      InstructionStorageAddressingMode::kAbsolute;

  bool is_clamped = false;

  uint32_t original_write_mask = 0b0000;

  SwizzleSource components[4] = {SwizzleSource::kX, SwizzleSource::kY, SwizzleSource::kZ,
                                 SwizzleSource::kW};

  uint32_t GetUsedWriteMask() const {
    uint32_t target_component_count = GetInstructionStorageTargetUsedComponentCount(storage_target);
    return original_write_mask & ((1 << target_component_count) - 1);
  }

  bool IsStandardSwizzle() const {
    return (GetUsedWriteMask() == 0b1111) && components[0] == SwizzleSource::kX &&
           components[1] == SwizzleSource::kY && components[2] == SwizzleSource::kZ &&
           components[3] == SwizzleSource::kW;
  }

  uint32_t GetUsedResultComponents() const {
    uint32_t used_write_mask = GetUsedWriteMask();
    uint32_t used_components = 0b0000;
    for (uint32_t i = 0; i < 4; ++i) {
      if ((used_write_mask & (1 << i)) && components[i] >= SwizzleSource::kX &&
          components[i] <= SwizzleSource::kW) {
        used_components |= 1 << (uint32_t(components[i]) - uint32_t(SwizzleSource::kX));
      }
    }
    return used_components;
  }

  uint32_t GetUsedConstantComponents(uint32_t& constant_values_out) const {
    uint32_t constant_components = 0;
    uint32_t constant_values = 0;
    uint32_t used_write_mask = GetUsedWriteMask();
    for (uint32_t i = 0; i < 4; ++i) {
      if (!(used_write_mask & (1 << i))) {
        continue;
      }
      SwizzleSource component = components[i];
      if (component >= SwizzleSource::kX && component <= SwizzleSource::kW) {
        continue;
      }
      constant_components |= 1 << i;
      if (component == SwizzleSource::k1) {
        constant_values |= 1 << i;
      }
    }
    constant_values_out = constant_values;
    return constant_components;
  }
};

enum class InstructionStorageSource {

  kRegister,

  kConstantFloat,

  kVertexFetchConstant,

  kTextureFetchConstant,
};

struct InstructionOperand {
  InstructionStorageSource storage_source = InstructionStorageSource::kRegister;

  uint32_t storage_index = 0;

  InstructionStorageAddressingMode storage_addressing_mode =
      InstructionStorageAddressingMode::kAbsolute;

  bool is_negated = false;

  bool is_absolute_value = false;

  uint32_t component_count = 4;

  SwizzleSource components[4] = {SwizzleSource::kX, SwizzleSource::kY, SwizzleSource::kZ,
                                 SwizzleSource::kW};

  SwizzleSource GetComponent(uint32_t index) const {
    return components[std::min(index, component_count - 1)];
  }

  bool IsStandardSwizzle() const {
    switch (component_count) {
      case 4:
        return components[0] == SwizzleSource::kX && components[1] == SwizzleSource::kY &&
               components[2] == SwizzleSource::kZ && components[3] == SwizzleSource::kW;
    }
    return false;
  }

  uint32_t GetIdenticalComponents(const InstructionOperand& other) const {
    if (storage_source != other.storage_source || storage_index != other.storage_index ||
        storage_addressing_mode != other.storage_addressing_mode ||
        is_negated != other.is_negated || is_absolute_value != other.is_absolute_value) {
      return 0;
    }
    uint32_t identical_components = 0;
    for (uint32_t i = 0; i < 4; ++i) {
      identical_components |= uint32_t(GetComponent(i) == other.GetComponent(i)) << i;
    }
    return identical_components;
  }
};

struct ParsedExecInstruction {
  uint32_t dword_index = 0;

  ucode::ControlFlowOpcode opcode;

  const char* opcode_name = nullptr;

  uint32_t instruction_address = 0;

  uint32_t instruction_count = 0;

  enum class Type {

    kUnconditional,

    kConditional,

    kPredicated,
  };

  Type type = Type::kUnconditional;

  uint32_t bool_constant_index = 0;

  bool condition = false;

  bool is_end = false;

  bool is_predicate_clean = true;

  bool is_yield = false;

  uint32_t sequence = 0;

  void Disassemble(string::StringBuffer* out) const;
};

struct ParsedLoopStartInstruction {
  uint32_t dword_index = 0;

  uint32_t loop_constant_index = 0;

  bool is_repeat = false;

  uint32_t loop_skip_address = 0;

  void Disassemble(string::StringBuffer* out) const;
};

struct ParsedLoopEndInstruction {
  uint32_t dword_index = 0;

  bool is_predicated_break = false;

  bool predicate_condition = false;

  uint32_t loop_constant_index = 0;

  uint32_t loop_body_address = 0;

  void Disassemble(string::StringBuffer* out) const;
};

struct ParsedCallInstruction {
  uint32_t dword_index = 0;

  uint32_t target_address = 0;

  enum class Type {

    kUnconditional,

    kConditional,

    kPredicated,
  };

  Type type = Type::kUnconditional;

  uint32_t bool_constant_index = 0;

  bool condition = false;

  void Disassemble(string::StringBuffer* out) const;
};

struct ParsedReturnInstruction {
  uint32_t dword_index = 0;

  void Disassemble(string::StringBuffer* out) const;
};

struct ParsedJumpInstruction {
  uint32_t dword_index = 0;

  uint32_t target_address = 0;

  enum class Type {

    kUnconditional,

    kConditional,

    kPredicated,
  };

  Type type = Type::kUnconditional;

  uint32_t bool_constant_index = 0;

  bool condition = false;

  void Disassemble(string::StringBuffer* out) const;
};

struct ParsedAllocInstruction {
  uint32_t dword_index = 0;

  ucode::AllocType type = ucode::AllocType::kNone;

  int count = 0;

  bool is_vertex_shader = false;

  void Disassemble(string::StringBuffer* out) const;
};

struct ParsedVertexFetchInstruction {
  ucode::FetchOpcode opcode;

  const char* opcode_name = nullptr;

  bool is_mini_fetch = false;

  bool is_predicated = false;

  bool predicate_condition = false;

  InstructionResult result;

  size_t operand_count = 0;

  InstructionOperand operands[2];

  struct Attributes {
    xenos::VertexFormat data_format = xenos::VertexFormat::kUndefined;
    int32_t offset = 0;
    uint32_t stride = 0;
    int32_t exp_adjust = 0;

    uint32_t prefetch_count = 0;
    xenos::SignedRepeatingFractionMode signed_rf_mode =
        xenos::SignedRepeatingFractionMode::kZeroClampMinusOne;
    bool is_index_rounded = false;
    bool is_signed = false;
    bool is_integer = false;
  };

  Attributes attributes;

  void Disassemble(string::StringBuffer* out) const;
};

struct ParsedTextureFetchInstruction {
  ucode::FetchOpcode opcode;

  const char* opcode_name = nullptr;

  xenos::FetchOpDimension dimension = xenos::FetchOpDimension::k1D;

  bool is_predicated = false;

  bool predicate_condition = false;

  bool has_result() const { return result.storage_target != InstructionStorageTarget::kNone; }

  InstructionResult result;

  size_t operand_count = 0;

  InstructionOperand operands[2];

  struct Attributes {
    bool fetch_valid_only = true;
    bool unnormalized_coordinates = false;
    xenos::TextureFilter mag_filter = xenos::TextureFilter::kUseFetchConst;
    xenos::TextureFilter min_filter = xenos::TextureFilter::kUseFetchConst;
    xenos::TextureFilter mip_filter = xenos::TextureFilter::kUseFetchConst;
    xenos::AnisoFilter aniso_filter = xenos::AnisoFilter::kUseFetchConst;
    xenos::TextureFilter vol_mag_filter = xenos::TextureFilter::kUseFetchConst;
    xenos::TextureFilter vol_min_filter = xenos::TextureFilter::kUseFetchConst;
    bool use_computed_lod = true;
    bool use_register_lod = false;
    bool use_register_gradients = false;
    float lod_bias = 0.0f;
    float offset_x = 0.0f;
    float offset_y = 0.0f;
    float offset_z = 0.0f;
  };

  Attributes attributes;

  uint32_t GetNonZeroResultComponents() const;

  bool AllowsPointSampling(bool use_computed_lod) const {
    return attributes.mag_filter != xenos::TextureFilter::kLinear &&
           attributes.min_filter != xenos::TextureFilter::kLinear &&
           attributes.mip_filter != xenos::TextureFilter::kLinear &&
           (!use_computed_lod || attributes.aniso_filter == xenos::AnisoFilter::kDisabled ||
            attributes.aniso_filter == xenos::AnisoFilter::kUseFetchConst);
  }

  bool CanSnapToTexelCenter(bool use_computed_lod) const {
    return (opcode == ucode::FetchOpcode::kTextureFetch ||
            opcode == ucode::FetchOpcode::kGetTextureBorderColorFrac) &&
           dimension == xenos::FetchOpDimension::k2D && !attributes.unnormalized_coordinates &&
           AllowsPointSampling(use_computed_lod);
  }

  void Disassemble(string::StringBuffer* out) const;
};

constexpr float kTextureCoordEpsilon = 1.5f / 1024.0f;

struct ParsedAluInstruction {
  ucode::AluVectorOpcode vector_opcode = ucode::AluVectorOpcode::kAdd;

  ucode::AluScalarOpcode scalar_opcode = ucode::AluScalarOpcode::kAdds;

  const char* vector_opcode_name = nullptr;

  const char* scalar_opcode_name = nullptr;

  bool is_predicated = false;

  bool predicate_condition = false;

  InstructionResult vector_and_constant_result;

  InstructionResult scalar_result;

  uint32_t vector_operand_count = 0;

  InstructionOperand vector_operands[3];

  uint32_t scalar_operand_count = 0;

  InstructionOperand scalar_operands[2];

  bool IsVectorOpDefaultNop() const;

  bool IsScalarOpDefaultNop() const;

  bool IsNop() const;

  uint32_t GetMemExportStreamConstant() const;

  void Disassemble(string::StringBuffer* out) const;
};

void ParseControlFlowExec(const ucode::ControlFlowExecInstruction& cf, uint32_t cf_index,
                          ParsedExecInstruction& instr);
void ParseControlFlowCondExec(const ucode::ControlFlowCondExecInstruction& cf, uint32_t cf_index,
                              ParsedExecInstruction& instr);
void ParseControlFlowCondExecPred(const ucode::ControlFlowCondExecPredInstruction& cf,
                                  uint32_t cf_index, ParsedExecInstruction& instr);
void ParseControlFlowLoopStart(const ucode::ControlFlowLoopStartInstruction& cf, uint32_t cf_index,
                               ParsedLoopStartInstruction& instr);
void ParseControlFlowLoopEnd(const ucode::ControlFlowLoopEndInstruction& cf, uint32_t cf_index,
                             ParsedLoopEndInstruction& instr);
void ParseControlFlowCondCall(const ucode::ControlFlowCondCallInstruction& cf, uint32_t cf_index,
                              ParsedCallInstruction& instr);
void ParseControlFlowReturn(const ucode::ControlFlowReturnInstruction& cf, uint32_t cf_index,
                            ParsedReturnInstruction& instr);
void ParseControlFlowCondJmp(const ucode::ControlFlowCondJmpInstruction& cf, uint32_t cf_index,
                             ParsedJumpInstruction& instr);
void ParseControlFlowAlloc(const ucode::ControlFlowAllocInstruction& cf, uint32_t cf_index,
                           bool is_vertex_shader, ParsedAllocInstruction& instr);

bool ParseVertexFetchInstruction(const ucode::VertexFetchInstruction& op,
                                 const ucode::VertexFetchInstruction& previous_full_op,
                                 ParsedVertexFetchInstruction& instr);
void ParseTextureFetchInstruction(const ucode::TextureFetchInstruction& op,
                                  ParsedTextureFetchInstruction& instr);
void ParseAluInstruction(const ucode::AluInstruction& op, xenos::ShaderType shader_type,
                         ParsedAluInstruction& instr);

class Shader {
 public:
  enum class HostVertexShaderType : uint32_t {
    kVertex,

    kDomainStart,
    kLineDomainCPIndexed = kDomainStart,
    kLineDomainPatchIndexed,
    kTriangleDomainCPIndexed,
    kTriangleDomainPatchIndexed,
    kQuadDomainCPIndexed,
    kQuadDomainPatchIndexed,
    kDomainEnd,

    kMemExportCompute,

    kPointListAsTriangleStrip,

    kRectangleListAsTriangleStrip,
  };

  static constexpr uint32_t kHostVertexShaderTypeBitCount = 4;

  static constexpr bool IsHostVertexShaderTypeDomain(HostVertexShaderType host_vertex_shader_type) {
    return host_vertex_shader_type >= HostVertexShaderType::kDomainStart &&
           host_vertex_shader_type < HostVertexShaderType::kDomainEnd;
  }

  struct Error {
    bool is_fatal = false;
    std::string message;
  };

  struct VertexBinding {
    struct Attribute {
      ParsedVertexFetchInstruction fetch_instr;
    };

    int binding_index;

    uint32_t fetch_constant;

    uint32_t stride_words;

    std::vector<Attribute> attributes;
  };

  struct TextureBinding {
    size_t binding_index;

    uint32_t fetch_constant;

    ParsedTextureFetchInstruction fetch_instr;
  };

  struct ConstantRegisterMap {
    uint64_t float_bitmap[256 / 64];

    uint32_t loop_bitmap;

    uint32_t bool_bitmap[256 / 32];

    uint32_t vertex_fetch_bitmap[96 / 32];

    uint32_t float_count;

    bool float_dynamic_addressing;

    uint32_t GetPackedFloatConstantIndex(uint32_t float_constant) const {
      if (float_constant >= 256) {
        return UINT32_MAX;
      }
      if (float_dynamic_addressing) {
        return float_constant;
      }
      uint32_t block_index = float_constant / 64;
      uint32_t bit_index = float_constant % 64;
      if (!(float_bitmap[block_index] & (uint64_t(1) << bit_index))) {
        return UINT32_MAX;
      }
      uint32_t offset = 0;
      for (uint32_t i = 0; i < block_index; ++i) {
        offset += rex::bit_count(float_bitmap[i]);
      }
      return offset + rex::bit_count(float_bitmap[block_index] & ((uint64_t(1) << bit_index) - 1));
    }
  };

  struct ControlFlowMemExportInfo {
    uint8_t eM_potentially_written_before = 0;

    uint8_t eM_potentially_written_by_exec = 0;
  };

  class Translation {
   public:
    virtual ~Translation() {}

    Shader& shader() const { return shader_; }

    uint64_t modification() const { return modification_; }

    bool is_valid() const { return is_valid_.load(std::memory_order_acquire); }

    bool is_translated() const { return is_translated_.load(std::memory_order_acquire); }

    void PublishTranslated() { is_translated_.store(true, std::memory_order_release); }

    const std::vector<Error>& errors() const { return errors_; }

    const std::vector<uint8_t>& translated_binary() const { return translated_binary_; }

    void ReplaceTranslatedBinary(std::vector<uint8_t> binary) {
      translated_binary_ = std::move(binary);
    }

    std::string GetTranslatedBinaryString() const;

    const std::string& host_disassembly() const { return host_disassembly_; }

    void set_host_disassembly(std::string disassembly) {
      host_disassembly_ = std::move(disassembly);
    }

    std::pair<std::filesystem::path, std::filesystem::path> Dump(
        const std::filesystem::path& base_path, const char* path_prefix) const;

   protected:
    Translation(Shader& shader, uint64_t modification)
        : shader_(shader), modification_(modification) {}

    void MakeInvalid() { is_valid_.store(false, std::memory_order_release); }

   private:
    friend class Shader;
    friend class ShaderTranslator;

    Shader& shader_;
    uint64_t modification_;

    std::atomic<bool> is_valid_{false};
    std::atomic<bool> is_translated_{false};
    std::vector<Error> errors_;
    std::vector<uint8_t> translated_binary_;
    std::string host_disassembly_;
  };

  Shader(xenos::ShaderType shader_type, uint64_t ucode_data_hash, const uint32_t* ucode_dwords,
         size_t ucode_dword_count, std::endian ucode_source_endian = std::endian::big);
  virtual ~Shader();

  xenos::ShaderType type() const { return shader_type_; }

  const std::vector<uint32_t>& ucode_data() const { return ucode_data_; }
  uint64_t ucode_data_hash() const { return ucode_data_hash_; }
  const uint32_t* ucode_dwords() const { return ucode_data_.data(); }
  size_t ucode_dword_count() const { return ucode_data_.size(); }

  bool is_ucode_analyzed() const { return is_ucode_analyzed_; }

  void AnalyzeUcode(string::StringBuffer& ucode_disasm_buffer);

  const std::string& ucode_disassembly() const { return ucode_disassembly_; }

  const std::vector<VertexBinding>& vertex_bindings() const { return vertex_bindings_; }

  const std::vector<TextureBinding>& texture_bindings() const { return texture_bindings_; }

  const ConstantRegisterMap& constant_register_map() const { return constant_register_map_; }

  const std::vector<ControlFlowMemExportInfo>& cf_memexport_info() const {
    return cf_memexport_info_;
  }

  uint8_t memexport_eM_written() const { return memexport_eM_written_; }
  uint8_t memexport_eM_potentially_written_before_end() const {
    return memexport_eM_potentially_written_before_end_;
  }

  const std::set<uint32_t>& memexport_stream_constants() const {
    return memexport_stream_constants_;
  }

  const std::set<uint32_t>& label_addresses() const { return label_addresses_; }

  uint32_t cf_pair_index_bound() const { return cf_pair_index_bound_; }

  bool uses_subroutine_calls() const { return uses_subroutine_calls_; }

  uint64_t GetRegisterComponentsWrittenBeforeReentering(uint32_t label) const {
    return label < reentered_label_register_components_written_.size()
               ? reentered_label_register_components_written_[label]
               : 0;
  }

  uint32_t point_fetch_coordinate_registers() const { return point_fetch_coordinate_registers_; }

  uint32_t register_static_address_bound() const { return register_static_address_bound_; }

  bool uses_register_dynamic_addressing() const { return uses_register_dynamic_addressing_; }

  uint32_t GetDynamicAddressableRegisterCount(uint32_t program_cntl_num_reg) const {
    if (!uses_register_dynamic_addressing()) {
      return 0;
    }
    return std::max(program_cntl_num_reg + uint32_t(1), register_static_address_bound());
  }

  bool kills_pixels() const { return kills_pixels_; }

  bool uses_texture_fetch_instruction_results() const {
    return uses_texture_fetch_instruction_results_;
  }

  uint32_t writes_interpolators() const { return writes_interpolators_; }

  uint32_t writes_point_size_edge_flag_kill_vertex() const {
    return writes_point_size_edge_flag_kill_vertex_;
  }

  uint32_t GetInterpolatorInputMask(reg::SQ_PROGRAM_CNTL sq_program_cntl,
                                    reg::SQ_CONTEXT_MISC sq_context_misc,
                                    uint32_t& param_gen_pos_out) const;

  bool writes_depth() const { return writes_depth_; }

  bool implicit_early_z_write_allowed() const {
    return !kills_pixels() && !writes_depth() && !memexport_eM_written();
  }

  uint32_t writes_color_targets() const { return writes_color_targets_; }
  bool writes_color_target(uint32_t i) const {
    return (writes_color_targets() & (uint32_t(1) << i)) != 0;
  }

  const std::unordered_map<uint64_t, Translation*>& translations() const { return translations_; }
  Translation* GetTranslation(uint64_t modification) const {
    auto it = translations_.find(modification);
    if (it != translations_.cend()) {
      return it->second;
    }
    return nullptr;
  }
  Translation* GetOrCreateTranslation(uint64_t modification, bool* is_new = nullptr);

  void DestroyTranslation(uint64_t modification);

  uint32_t ucode_storage_index() const { return ucode_storage_index_; }
  void set_ucode_storage_index(uint32_t storage_index) { ucode_storage_index_ = storage_index; }

  std::pair<std::filesystem::path, std::filesystem::path> DumpUcode(
      const std::filesystem::path& base_path) const;

 protected:
  friend class ShaderTranslator;

  virtual Translation* CreateTranslationInstance(uint64_t modification);

  xenos::ShaderType shader_type_;
  std::vector<uint32_t> ucode_data_;
  uint64_t ucode_data_hash_;

  bool is_ucode_analyzed_ = false;

  std::string ucode_disassembly_;
  std::vector<VertexBinding> vertex_bindings_;
  std::vector<TextureBinding> texture_bindings_;
  ConstantRegisterMap constant_register_map_ = {};
  std::set<uint32_t> label_addresses_;
  uint32_t cf_pair_index_bound_ = 0;

  std::vector<uint64_t> cf_register_components_written_;
  std::vector<uint64_t> reentered_label_register_components_written_;
  uint32_t point_fetch_coordinate_registers_ = 0;
  bool uses_subroutine_calls_ = false;
  uint32_t register_static_address_bound_ = 0;
  uint32_t writes_interpolators_ = 0;
  uint32_t writes_point_size_edge_flag_kill_vertex_ = 0;
  uint32_t writes_color_targets_ = 0b0000;
  bool uses_register_dynamic_addressing_ = false;
  bool kills_pixels_ = false;
  bool uses_texture_fetch_instruction_results_ = false;
  bool writes_depth_ = false;

  std::vector<ControlFlowMemExportInfo> cf_memexport_info_;

  uint8_t memexport_eM_written_ = 0;

  uint8_t memexport_eM_potentially_written_before_end_ = 0;
  std::set<uint32_t> memexport_stream_constants_;

  std::unordered_map<uint64_t, Translation*> translations_;

  uint32_t ucode_storage_index_ = UINT32_MAX;

 private:
  void GatherExecInformation(const ParsedExecInstruction& instr,
                             ucode::VertexFetchInstruction& previous_vfetch_full,
                             uint32_t& unique_texture_bindings,
                             string::StringBuffer& ucode_disasm_buffer);
  void GatherVertexFetchInformation(const ucode::VertexFetchInstruction& op, uint32_t exec_cf_index,
                                    ucode::VertexFetchInstruction& previous_vfetch_full,
                                    string::StringBuffer& ucode_disasm_buffer);
  void GatherTextureFetchInformation(const ucode::TextureFetchInstruction& op,
                                     uint32_t exec_cf_index, uint32_t& unique_texture_bindings,
                                     string::StringBuffer& ucode_disasm_buffer);
  void GatherAluInstructionInformation(const ucode::AluInstruction& op, uint32_t exec_cf_index,
                                       string::StringBuffer& ucode_disasm_buffer);
  void GatherOperandInformation(const InstructionOperand& operand);
  void GatherFetchResultInformation(const InstructionResult& result, uint32_t exec_cf_index);
  void GatherRegisterWriteInformation(const InstructionResult& result, uint32_t exec_cf_index);
  void GatherAluResultInformation(const InstructionResult& result, uint32_t exec_cf_index);
};

}
