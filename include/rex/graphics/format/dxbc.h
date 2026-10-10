/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2021 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <rex/assert.h>
#include <rex/math.h>
#include <rex/memory.h>

namespace rex::graphics::dxbc {

constexpr uint8_t kAlignmentPadding = 0xAB;

constexpr uint32_t MakeFourCC(uint32_t ch0, uint32_t ch1, uint32_t ch2, uint32_t ch3) {
  return uint32_t(ch0) | (uint32_t(ch1) << 8) | (uint32_t(ch2) << 16) | (uint32_t(ch3) << 24);
}

struct alignas(uint32_t) ContainerHeader {
  static constexpr uint32_t kFourCC = MakeFourCC('D', 'X', 'B', 'C');
  static constexpr uint16_t kVersionMajor = 1;
  static constexpr uint16_t kVersionMinor = 0;
  uint32_t fourcc;

  uint32_t hash[4];
  uint16_t version_major;
  uint16_t version_minor;
  uint32_t size_bytes;
  uint32_t blob_count;
  void InitializeIdentification() {
    fourcc = kFourCC;
    version_major = kVersionMajor;
    version_minor = kVersionMinor;
  }
};
static_assert_size(ContainerHeader, sizeof(uint32_t) * 8);

struct alignas(uint32_t) BlobHeader {
  enum class FourCC : uint32_t {

    kResourceDefinition = MakeFourCC('R', 'D', 'E', 'F'),
    kInputSignature = MakeFourCC('I', 'S', 'G', 'N'),
    kInputSignature_11_1 = MakeFourCC('I', 'S', 'G', '1'),
    kPatchConstantSignature = MakeFourCC('P', 'C', 'S', 'G'),
    kOutputSignature = MakeFourCC('O', 'S', 'G', 'N'),
    kOutputSignatureForGS = MakeFourCC('O', 'S', 'G', '5'),
    kOutputSignature_11_1 = MakeFourCC('O', 'S', 'G', '1'),
    kShaderEx = MakeFourCC('S', 'H', 'E', 'X'),
    kShaderFeatureInfo = MakeFourCC('S', 'F', 'I', '0'),
    kStatistics = MakeFourCC('S', 'T', 'A', 'T'),
  };
  FourCC fourcc;
  uint32_t size_bytes;
};
static_assert_size(BlobHeader, sizeof(uint32_t) * 2);

inline uint32_t AppendAlignedString(std::vector<uint32_t>& dest, const char* source) {
  size_t size = std::strlen(source) + 1;
  size_t size_aligned = rex::align(size, sizeof(uint32_t));
  size_t dest_position = dest.size();
  dest.resize(dest_position + size_aligned / sizeof(uint32_t));
  std::memcpy(&dest[dest_position], source, size);

  std::memset(reinterpret_cast<uint8_t*>(&dest[dest_position]) + size, dxbc::kAlignmentPadding,
              size_aligned - size);
  return uint32_t(size_aligned);
}

inline uint32_t GetAlignedStringLength(const char* source) {
  return uint32_t(rex::align(std::strlen(source) + 1, sizeof(uint32_t)));
}

enum CompileFlags : uint32_t {

  kCompileFlagNoPreshader = 1 << 8,
  kCompileFlagPreferFlowControl = 1 << 10,
  kCompileFlagIeeeStrictness = 1 << 13,
  kCompileFlagEnableUnboundedDescriptorTables = 1 << 20,
  kCompileFlagAllResourcesBound = 1 << 21,
};

enum class RdefVariableClass : uint16_t {
  kScalar,
  kVector,
  kMatrixRows,
  kMatrixColumns,
  kObject,
  kStruct,
  kInterfaceClass,
  kInterfacePointer,
};

enum class RdefVariableType : uint16_t {
  kInt = 2,
  kFloat = 3,
  kUInt = 19,
};

enum RdefVariableFlags : uint32_t {
  kRdefVariableFlagUserPacked = 1 << 0,
  kRdefVariableFlagUsed = 1 << 1,
  kRdefVariableFlagInterfacePointer = 1 << 2,
  kRdefVariableFlagInterfaceParameter = 1 << 3,
};

enum RdefCbufferFlags : uint32_t {
  kRdefCbufferFlagUserPacked = 1 << 0,
};

enum class RdefCbufferType : uint32_t {
  kCbuffer,
  kTbuffer,
  kInterfacePointers,
  kResourceBindInfo,
};

enum class RdefInputType : uint32_t {
  kCbuffer,
  kTbuffer,
  kTexture,
  kSampler,
  kUAVRWTyped,
  kStructured,
  kUAVRWStructured,
  kByteAddress,
  kUAVRWByteAddress,
  kUAVAppendStructured,
  kUAVConsumeStructured,
  kUAVRWStructuredWithCounter,
};

enum class ResourceReturnType : uint32_t {
  kVoid,
  kUNorm,
  kSNorm,
  kSInt,
  kUInt,
  kFloat,
  kMixed,
  kDouble,
  kContinued,
};

enum class RdefDimension : uint32_t {
  kUnknown = 0,

  kSRVBuffer = 1,
  kSRVTexture1D,
  kSRVTexture1DArray,
  kSRVTexture2D,
  kSRVTexture2DArray,
  kSRVTexture2DMS,
  kSRVTexture2DMSArray,
  kSRVTexture3D,
  kSRVTextureCube,
  kSRVTextureCubeArray,

  kUAVBuffer = 1,
  kUAVTexture1D,
  kUAVTexture1DArray,
  kUAVTexture2D,
  kUAVTexture2DArray,
  kUAVTexture3D,
};

enum RdefInputFlags : uint32_t {

  kRdefInputFlagUserPacked = 1 << 0,
  kRdefInputFlagComparisonSampler = 1 << 1,

  kRdefInputFlagsComponentsShift = 2,
  kRdefInputFlags2Component = 1 << kRdefInputFlagsComponentsShift,
  kRdefInputFlags3Component = 2 << kRdefInputFlagsComponentsShift,
  kRdefInputFlags4Component = 3 << kRdefInputFlagsComponentsShift,
  kRdefInputFlagUnused = 1 << 4,
};

enum class RdefShaderModel : uint32_t {
  kPixelShader5_1 = 0xFFFF0501u,
  kVertexShader5_1 = 0xFFFE0501u,
  kGeometryShader5_1 = 0x47530501u,
  kDomainShader5_1 = 0x44530501u,
  kComputeShader5_1 = 0x43530501u,
};

struct alignas(uint32_t) RdefType {
  RdefVariableClass variable_class;
  RdefVariableType variable_type;

  uint16_t row_count;

  uint16_t column_count;

  uint16_t element_count;

  uint16_t member_count;

  uint32_t members_ptr;

  uint32_t unknown_0[4];

  uint32_t name_ptr;
};
static_assert_size(RdefType, sizeof(uint32_t) * 9);

struct alignas(uint32_t) RdefStructureMember {
  uint32_t name_ptr;
  uint32_t type_ptr;
  uint32_t offset_bytes;
};
static_assert_size(RdefStructureMember, sizeof(uint32_t) * 3);

struct alignas(uint32_t) RdefVariable {
  uint32_t name_ptr;
  uint32_t start_offset_bytes;
  uint32_t size_bytes;

  uint32_t flags;
  uint32_t type_ptr;
  uint32_t default_value_ptr;

  uint32_t start_texture;

  uint32_t texture_size;

  uint32_t start_sampler;

  uint32_t sampler_size;
};
static_assert_size(RdefVariable, sizeof(uint32_t) * 10);

struct alignas(uint32_t) RdefCbuffer {
  uint32_t name_ptr;
  uint32_t variable_count;
  uint32_t variables_ptr;

  uint32_t size_vector_aligned_bytes;
  RdefCbufferType type;

  uint32_t flags;
};
static_assert_size(RdefCbuffer, sizeof(uint32_t) * 6);

struct alignas(uint32_t) RdefInputBind {
  uint32_t name_ptr;
  RdefInputType type;
  ResourceReturnType return_type;
  RdefDimension dimension;

  uint32_t sample_count;
  uint32_t bind_point;

  uint32_t bind_count;

  uint32_t flags;

  uint32_t bind_point_space;
  uint32_t id;
};
static_assert_size(RdefInputBind, sizeof(uint32_t) * 10);

struct alignas(uint32_t) RdefHeader {
  enum class FourCC : uint32_t {

    k5_0 = MakeFourCC('R', 'D', '1', '1'),

    k5_1 = 0x25441313u,
  };
  uint32_t cbuffer_count;
  uint32_t cbuffers_ptr;
  uint32_t input_bind_count;
  uint32_t input_binds_ptr;
  RdefShaderModel shader_model;

  uint32_t compile_flags;
  uint32_t generator_name_ptr;
  FourCC fourcc;
  uint32_t sizeof_header_bytes;
  uint32_t sizeof_cbuffer_bytes;
  uint32_t sizeof_input_bind_bytes;
  uint32_t sizeof_variable_bytes;
  uint32_t sizeof_type_bytes;
  uint32_t sizeof_structure_member_bytes;

  uint32_t unknown_0;
  void InitializeSizes() {
    sizeof_header_bytes = sizeof(*this);
    sizeof_cbuffer_bytes = sizeof(RdefCbuffer);
    sizeof_input_bind_bytes = sizeof(RdefInputBind);
    sizeof_variable_bytes = sizeof(RdefVariable);
    sizeof_type_bytes = sizeof(RdefType);
    sizeof_structure_member_bytes = sizeof(RdefStructureMember);
  }
};
static_assert_size(RdefHeader, sizeof(uint32_t) * 15);

enum class Name : uint32_t {
  kUndefined = 0,
  kPosition = 1,
  kClipDistance = 2,
  kCullDistance = 3,
  kVertexID = 6,
  kIsFrontFace = 9,
  kSampleIndex = 10,
  kFinalQuadEdgeTessFactor = 11,
  kFinalQuadInsideTessFactor = 12,
  kFinalTriEdgeTessFactor = 13,
  kFinalTriInsideTessFactor = 14,
};

enum class SignatureRegisterComponentType : uint32_t {
  kUnknown,
  kUInt32,
  kSInt32,
  kFloat32,
};

enum class MinPrecision : uint32_t {
  kDefault,
  kFloat16,
  kFloat2_8,
  kSInt16 = 4,
  kUInt16,
  kAny16 = 0xF0,
  kAny10,
};

struct alignas(uint32_t) SignatureParameter {
  uint32_t semantic_name_ptr;
  uint32_t semantic_index;

  Name system_value;
  SignatureRegisterComponentType component_type;

  uint32_t register_index;
  uint8_t mask;
  union {
    uint8_t never_writes_mask;

    uint8_t always_reads_mask;
  };
};
static_assert_size(SignatureParameter, sizeof(uint32_t) * 6);

struct alignas(uint32_t) SignatureParameterForGS {
  uint32_t stream;
  uint32_t semantic_name_ptr;
  uint32_t semantic_index;
  Name system_value;
  SignatureRegisterComponentType component_type;
  uint32_t register_index;
  uint8_t mask;
  union {
    uint8_t never_writes_mask;
    uint8_t always_reads_mask;
  };
};
static_assert_size(SignatureParameterForGS, sizeof(uint32_t) * 7);

struct alignas(uint32_t) SignatureParameter_11_1 {
  uint32_t stream;
  uint32_t semantic_name_ptr;
  uint32_t semantic_index;
  Name system_value;
  SignatureRegisterComponentType component_type;
  uint32_t register_index;
  uint8_t mask;
  union {
    uint8_t never_writes_mask;
    uint8_t always_reads_mask;
  };
  MinPrecision min_precision;
};
static_assert_size(SignatureParameter_11_1, sizeof(uint32_t) * 8);

struct alignas(uint32_t) Signature {
  uint32_t parameter_count;

  uint32_t parameter_info_ptr;
};
static_assert_size(Signature, sizeof(uint32_t) * 2);

enum ShaderFeature0 : uint32_t {
  kShaderFeature0_Doubles = 1 << 0,
  kShaderFeature0_ComputeShadersPlusRawAndStructuredBuffersViaShader_4_X = 1 << 1,
  kShaderFeature0_UAVsAtEveryStage = 1 << 2,
  kShaderFeature0_64UAVs = 1 << 3,
  kShaderFeature0_MinimumPrecision = 1 << 4,
  kShaderFeature0_11_1_DoubleExtensions = 1 << 5,
  kShaderFeature0_11_1_ShaderExtensions = 1 << 6,
  kShaderFeature0_Level9ComparisonFiltering = 1 << 7,
  kShaderFeature0_TiledResources = 1 << 8,
  kShaderFeature0_StencilRef = 1 << 9,
  kShaderFeature0_InnerCoverage = 1 << 10,
  kShaderFeature0_TypedUAVLoadAdditionalFormats = 1 << 11,
  kShaderFeature0_ROVs = 1 << 12,
  kShaderFeature0_ViewportAndRTArrayIndexFromAnyShaderFeedingRasterizer = 1 << 13,
};

struct alignas(uint32_t) ShaderFeatureInfo {
  uint32_t feature_flags[2];
};
static_assert_size(ShaderFeatureInfo, sizeof(uint32_t) * 2);

enum class TessellatorDomain : uint32_t {
  kUndefined,
  kIsoline,
  kTriangle,
  kQuad,
};

enum class PrimitiveTopology : uint32_t {
  kUndefined = 0,
  kPointList = 1,
  kLineList = 2,
  kLineStrip = 3,
  kTriangleList = 4,
  kTriangleStrip = 5,
  kLineListWithAdjacency = 10,
  kLineStripWithAdjacency = 11,
  kTriangleListWithAdjacency = 12,
  kTriangleStripWithAdjacency = 13,
};

enum class Primitive : uint32_t {
  kUndefined = 0,
  kPoint = 1,
  kLine = 2,
  kTriangle = 3,
  kLineWithAdjacency = 6,
  kTriangleWithAdjacency = 7,
  k1ControlPointPatch = 8,
  k2ControlPointPatch = 9,
  k3ControlPointPatch = 10,
  k4ControlPointPatch = 11,
  k5ControlPointPatch = 12,
  k6ControlPointPatch = 13,
  k7ControlPointPatch = 14,
  k8ControlPointPatch = 15,
  k9ControlPointPatch = 16,
  k10ControlPointPatch = 17,
  k11ControlPointPatch = 18,
  k12ControlPointPatch = 19,
  k13ControlPointPatch = 20,
  k14ControlPointPatch = 21,
  k15ControlPointPatch = 22,
  k16ControlPointPatch = 23,
  k17ControlPointPatch = 24,
  k18ControlPointPatch = 25,
  k19ControlPointPatch = 26,
  k20ControlPointPatch = 27,
  k21ControlPointPatch = 28,
  k22ControlPointPatch = 29,
  k23ControlPointPatch = 30,
  k24ControlPointPatch = 31,
  k25ControlPointPatch = 32,
  k26ControlPointPatch = 33,
  k27ControlPointPatch = 34,
  k28ControlPointPatch = 35,
  k29ControlPointPatch = 36,
  k30ControlPointPatch = 37,
  k31ControlPointPatch = 38,
  k32ControlPointPatch = 39,
};

struct alignas(uint32_t) Statistics {
  uint32_t instruction_count;
  uint32_t temp_register_count;

  uint32_t def_count;

  uint32_t dcl_count;
  uint32_t float_instruction_count;
  uint32_t int_instruction_count;
  uint32_t uint_instruction_count;

  uint32_t static_flow_control_count;

  uint32_t dynamic_flow_control_count;

  uint32_t macro_instruction_count;
  uint32_t temp_array_count;
  uint32_t array_instruction_count;
  uint32_t cut_instruction_count;
  uint32_t emit_instruction_count;
  uint32_t texture_normal_instructions;
  uint32_t texture_load_instructions;
  uint32_t texture_comp_instructions;
  uint32_t texture_bias_instructions;
  uint32_t texture_gradient_instructions;

  uint32_t mov_instruction_count;

  uint32_t movc_instruction_count;
  uint32_t conversion_instruction_count;

  uint32_t unknown_22;
  Primitive input_primitive;
  PrimitiveTopology gs_output_topology;
  uint32_t gs_max_output_vertex_count;
  uint32_t unknown_26;

  uint32_t lod_instructions;
  uint32_t unknown_28;
  uint32_t unknown_29;
  uint32_t c_control_points;
  uint32_t hs_output_primitive;
  uint32_t hs_partitioning;
  TessellatorDomain tessellator_domain;

  uint32_t c_barrier_instructions;

  uint32_t c_interlocked_instructions;

  uint32_t c_texture_store_instructions;
};
static_assert_size(Statistics, sizeof(uint32_t) * 37);

enum class ProgramType : uint32_t {
  kPixelShader,
  kVertexShader,
  kGeometryShader,
  kHullShader,
  kDomainShader,
  kComputeShader,
};

constexpr uint32_t VersionToken(ProgramType program_type, uint32_t major_version,
                                uint32_t minor_version) {
  return (uint32_t(program_type) << 16) | (major_version << 4) | minor_version;
}

enum class CustomDataClass : uint32_t {
  kComment,
  kDebugInfo,
  kOpaque,
  kDclImmediateConstantBuffer,
  kShaderMessage,
  kShaderClipPlaneConstantMappingsForDX9,
};

enum class OperandType : uint32_t {
  kTemp = 0,
  kInput = 1,
  kOutput = 2,

  kIndexableTemp = 3,
  kImmediate32 = 4,
  kSampler = 6,
  kResource = 7,
  kConstantBuffer = 8,
  kLabel = 10,
  kInputPrimitiveID = 11,
  kOutputDepth = 12,
  kNull = 13,
  kOutputCoverageMask = 15,
  kStream = 16,
  kInputControlPoint = 25,
  kInputDomainPoint = 28,
  kUnorderedAccessView = 30,
  kInputThreadID = 32,
  kInputThreadGroupID = 33,
  kInputThreadIDInGroup = 34,
  kInputCoverageMask = 35,
  kOutputDepthLessEqual = 39,
  kOutputStencilRef = 41,
};

enum class OperandDimension : uint32_t {
  kNoData,
  kScalar,
  kVector,
};

constexpr OperandDimension GetOperandDimension(OperandType type, bool in_dcl = false) {
  switch (type) {
    case OperandType::kSampler:
      return in_dcl ? OperandDimension::kVector : OperandDimension::kNoData;
    case OperandType::kLabel:
    case OperandType::kNull:
    case OperandType::kStream:
      return OperandDimension::kNoData;
    case OperandType::kInputPrimitiveID:
    case OperandType::kOutputDepth:
    case OperandType::kOutputCoverageMask:
    case OperandType::kOutputDepthLessEqual:
    case OperandType::kOutputStencilRef:
      return OperandDimension::kScalar;
    case OperandType::kInputCoverageMask:
      return in_dcl ? OperandDimension::kScalar : OperandDimension::kVector;
    default:
      return OperandDimension::kVector;
  }
}

enum class ComponentSelection {
  kMask,
  kSwizzle,
  kSelect1,
};

struct Index {
  enum class Representation : uint32_t {
    kImmediate32,
    kImmediate64,
    kRelative,
    kImmediate32PlusRelative,
    kImmediate64PlusRelative,
  };

  uint32_t index_;

  uint32_t relative_to_temp_;

  Index(uint32_t index = 0) : index_(index), relative_to_temp_(UINT32_MAX) {}
  Index(uint32_t temp, uint32_t temp_component, uint32_t offset = 0)
      : index_(offset), relative_to_temp_((temp << 2) | temp_component) {}

  Representation GetRepresentation() const {
    if (relative_to_temp_ != UINT32_MAX) {
      return index_ != 0 ? Representation::kImmediate32PlusRelative : Representation::kRelative;
    }
    return Representation::kImmediate32;
  }
  uint32_t GetLength() const { return relative_to_temp_ != UINT32_MAX ? (index_ != 0 ? 3 : 2) : 1; }
  void Write(std::vector<uint32_t>& code) const {
    if (relative_to_temp_ == UINT32_MAX || index_ != 0) {
      code.push_back(index_);
    }
    if (relative_to_temp_ != UINT32_MAX) {
      code.push_back(uint32_t(OperandDimension::kVector) |
                     (uint32_t(ComponentSelection::kSelect1) << 2) |
                     ((relative_to_temp_ & 3) << 4) | (uint32_t(OperandType::kTemp) << 12) |
                     (1 << 20) | (uint32_t(Representation::kImmediate32) << 22));
      code.push_back(relative_to_temp_ >> 2);
    }
  }
};

struct OperandAddress {
  OperandType type_;
  uint32_t index_dimension_;
  Index index_1d_, index_2d_, index_3d_;

  explicit OperandAddress(OperandType type) : type_(type), index_dimension_(0) {}
  explicit OperandAddress(OperandType type, Index index_1d)
      : type_(type), index_dimension_(1), index_1d_(index_1d) {}
  explicit OperandAddress(OperandType type, Index index_1d, Index index_2d)
      : type_(type), index_dimension_(2), index_1d_(index_1d), index_2d_(index_2d) {}
  explicit OperandAddress(OperandType type, Index index_1d, Index index_2d, Index index_3d)
      : type_(type),
        index_dimension_(3),
        index_1d_(index_1d),
        index_2d_(index_2d),
        index_3d_(index_3d) {}

  OperandDimension GetDimension(bool in_dcl = false) const {
    return GetOperandDimension(type_, in_dcl);
  }
  uint32_t GetOperandTokenTypeAndIndex() const {
    uint32_t operand_token = (uint32_t(type_) << 12) | (index_dimension_ << 20);
    if (index_dimension_ > 0) {
      operand_token |= uint32_t(index_1d_.GetRepresentation()) << 22;
      if (index_dimension_ > 1) {
        operand_token |= uint32_t(index_2d_.GetRepresentation()) << 25;
        if (index_dimension_ > 2) {
          operand_token |= uint32_t(index_3d_.GetRepresentation()) << 28;
        }
      }
    }
    return operand_token;
  }
  uint32_t GetLength() const {
    uint32_t length = 0;
    if (index_dimension_ > 0) {
      length += index_1d_.GetLength();
      if (index_dimension_ > 1) {
        length += index_2d_.GetLength();
        if (index_dimension_ > 2) {
          length += index_3d_.GetLength();
        }
      }
    }
    return length;
  }
  void Write(std::vector<uint32_t>& code) const {
    if (index_dimension_ > 0) {
      index_1d_.Write(code);
      if (index_dimension_ > 1) {
        index_2d_.Write(code);
        if (index_dimension_ > 2) {
          index_3d_.Write(code);
        }
      }
    }
  }
};

enum class ExtendedOperandType : uint32_t {
  kEmpty,
  kModifier,
};

enum class OperandModifier : uint32_t {
  kNone,
  kNegate,
  kAbsolute,
  kAbsoluteNegate,
};

struct Dest : OperandAddress {
  uint32_t write_mask_;

  explicit Dest(OperandType type, uint32_t write_mask)
      : OperandAddress(type), write_mask_(write_mask) {}
  explicit Dest(OperandType type, uint32_t write_mask, Index index_1d)
      : OperandAddress(type, index_1d), write_mask_(write_mask) {}
  explicit Dest(OperandType type, uint32_t write_mask, Index index_1d, Index index_2d)
      : OperandAddress(type, index_1d, index_2d), write_mask_(write_mask) {}
  explicit Dest(OperandType type, uint32_t write_mask, Index index_1d, Index index_2d,
                Index index_3d)
      : OperandAddress(type, index_1d, index_2d, index_3d), write_mask_(write_mask) {}

  static Dest R(uint32_t index, uint32_t write_mask = 0b1111) {
    return Dest(OperandType::kTemp, write_mask, index);
  }
  static Dest V1D(uint32_t index, uint32_t read_mask = 0b1111) {
    return Dest(OperandType::kInput, read_mask, index);
  }
  static Dest V2D(uint32_t index_1d, uint32_t index_2d, uint32_t read_mask = 0b1111) {
    return Dest(OperandType::kInput, read_mask, index_1d, index_2d);
  }
  static Dest O(Index index, uint32_t write_mask = 0b1111) {
    return Dest(OperandType::kOutput, write_mask, index);
  }
  static Dest X(uint32_t index_1d, Index index_2d, uint32_t write_mask = 0b1111) {
    return Dest(OperandType::kIndexableTemp, write_mask, index_1d, index_2d);
  }
  static Dest VPrim() { return Dest(OperandType::kInputPrimitiveID, 0b0001); }
  static Dest ODepth() { return Dest(OperandType::kOutputDepth, 0b0001); }
  static Dest Null() { return Dest(OperandType::kNull, 0b0000); }
  static Dest OMask() { return Dest(OperandType::kOutputCoverageMask, 0b0001); }
  static Dest M(uint32_t index) { return Dest(OperandType::kStream, 0b0000, index); }
  static Dest VICP(uint32_t control_point_count, uint32_t element, uint32_t read_mask = 0b1111) {
    return Dest(OperandType::kInputControlPoint, read_mask, control_point_count, element);
  }
  static Dest VDomain(uint32_t read_mask) {
    return Dest(OperandType::kInputDomainPoint, read_mask);
  }
  static Dest U(uint32_t index_1d, Index index_2d, uint32_t write_mask = 0b1111) {
    return Dest(OperandType::kUnorderedAccessView, write_mask, index_1d, index_2d);
  }
  static Dest VThreadID(uint32_t read_mask) { return Dest(OperandType::kInputThreadID, read_mask); }
  static Dest VThreadGroupID(uint32_t read_mask) {
    return Dest(OperandType::kInputThreadGroupID, read_mask);
  }
  static Dest VThreadIDInGroup(uint32_t read_mask) {
    return Dest(OperandType::kInputThreadIDInGroup, read_mask);
  }
  static Dest VCoverage() { return Dest(OperandType::kInputCoverageMask, 0b0001); }
  static Dest ODepthLE() { return Dest(OperandType::kOutputDepthLessEqual, 0b0001); }
  static Dest OStencilRef() { return Dest(OperandType::kOutputStencilRef, 0b0001); }

  uint32_t GetMask(bool in_dcl = false) const {
    OperandDimension dimension = GetDimension(in_dcl);
    switch (dimension) {
      case OperandDimension::kNoData:
        return 0b0000;
      case OperandDimension::kScalar:
        return 0b0001;
      case OperandDimension::kVector:
        return write_mask_;
      default:
        assert_unhandled_case(dimension);
        return 0b0000;
    }
  }
  [[nodiscard]] Dest Mask(uint32_t write_mask) const {
    Dest new_dest(*this);
    new_dest.write_mask_ = write_mask;
    return new_dest;
  }
  [[nodiscard]] Dest MaskMasked(uint32_t write_mask) const {
    Dest new_dest(*this);
    new_dest.write_mask_ &= write_mask;
    return new_dest;
  }
  static uint32_t GetMaskSingleComponent(uint32_t write_mask) {
    uint32_t component;
    if (rex::bit_scan_forward(write_mask, &component)) {
      if ((write_mask >> component) == 1) {
        return component;
      }
    }
    return UINT32_MAX;
  }
  uint32_t GetMaskSingleComponent(bool in_dcl = false) const {
    return GetMaskSingleComponent(GetMask(in_dcl));
  }

  uint32_t GetLength() const { return 1 + OperandAddress::GetLength(); }
  void Write(std::vector<uint32_t>& code, bool in_dcl = false) const {
    uint32_t operand_token = GetOperandTokenTypeAndIndex();
    OperandDimension dimension = GetDimension(in_dcl);
    if (dimension == OperandDimension::kVector) {
      if (write_mask_) {
        assert_true(write_mask_ <= 0b1111);
        operand_token |= (uint32_t(ComponentSelection::kMask) << 2) | (write_mask_ << 4);
      } else {
        dimension = OperandDimension::kNoData;
      }
    }
    operand_token |= uint32_t(dimension);
    code.push_back(operand_token);
    OperandAddress::Write(code);
  }
};

struct Src : OperandAddress {
  enum : uint32_t {
    kXYZW = 0b11100100,
    kXXXX = 0b00000000,
    kYYYY = 0b01010101,
    kZZZZ = 0b10101010,
    kWWWW = 0b11111111,
    kXYXY = 0b01000100,
  };

  uint32_t swizzle_;
  bool absolute_ = false;
  bool negate_ = false;

  uint32_t immediate_[4];

  explicit Src(OperandType type, uint32_t swizzle) : OperandAddress(type), swizzle_(swizzle) {}
  explicit Src(OperandType type, uint32_t swizzle, Index index_1d)
      : OperandAddress(type, index_1d), swizzle_(swizzle) {}
  explicit Src(OperandType type, uint32_t swizzle, Index index_1d, Index index_2d)
      : OperandAddress(type, index_1d, index_2d), swizzle_(swizzle) {}
  explicit Src(OperandType type, uint32_t swizzle, Index index_1d, Index index_2d, Index index_3d)
      : OperandAddress(type, index_1d, index_2d, index_3d), swizzle_(swizzle) {}

  struct DclT {};
  static constexpr DclT Dcl = {};

  static Src R(uint32_t index, uint32_t swizzle = kXYZW) {
    return Src(OperandType::kTemp, swizzle, index);
  }
  static Src V1D(Index index, uint32_t swizzle = kXYZW) {
    return Src(OperandType::kInput, swizzle, index);
  }
  static Src V2D(Index index_1d, Index index_2d, uint32_t swizzle = kXYZW) {
    return Src(OperandType::kInput, swizzle, index_1d, index_2d);
  }
  static Src X(uint32_t index_1d, Index index_2d, uint32_t swizzle = kXYZW) {
    return Src(OperandType::kIndexableTemp, swizzle, index_1d, index_2d);
  }
  static Src LU(uint32_t x, uint32_t y, uint32_t z, uint32_t w) {
    Src src(OperandType::kImmediate32, kXYZW);
    src.immediate_[0] = x;
    src.immediate_[1] = y;
    src.immediate_[2] = z;
    src.immediate_[3] = w;
    return src;
  }
  static Src LU(uint32_t x) { return LU(x, x, x, x); }
  static Src LI(int32_t x, int32_t y, int32_t z, int32_t w) {
    return LU(uint32_t(x), uint32_t(y), uint32_t(z), uint32_t(w));
  }
  static Src LI(int32_t x) { return LI(x, x, x, x); }
  static Src LF(float x, float y, float z, float w) {
    return LU(rex::memory::Reinterpret<uint32_t>(x), rex::memory::Reinterpret<uint32_t>(y),
              rex::memory::Reinterpret<uint32_t>(z), rex::memory::Reinterpret<uint32_t>(w));
  }
  static Src LF(float x) { return LF(x, x, x, x); }
  static Src LP(const uint32_t* xyzw) { return LU(xyzw[0], xyzw[1], xyzw[2], xyzw[3]); }
  static Src LP(const int32_t* xyzw) { return LI(xyzw[0], xyzw[1], xyzw[2], xyzw[3]); }
  static Src LP(const float* xyzw) { return LF(xyzw[0], xyzw[1], xyzw[2], xyzw[3]); }
  static Src S(uint32_t index_1d, Index index_2d) {
    return Src(OperandType::kSampler, kXXXX, index_1d, index_2d);
  }
  static Src S(DclT, uint32_t id, uint32_t lower_bound, uint32_t upper_bound) {
    return Src(OperandType::kSampler, kXYZW, id, lower_bound, upper_bound);
  }
  static Src T(uint32_t index_1d, Index index_2d, uint32_t swizzle = kXYZW) {
    return Src(OperandType::kResource, swizzle, index_1d, index_2d);
  }
  static Src T(DclT, uint32_t id, uint32_t lower_bound, uint32_t upper_bound) {
    return Src(OperandType::kResource, kXYZW, id, lower_bound, upper_bound);
  }
  static Src CB(uint32_t id, Index index, Index location, uint32_t swizzle = kXYZW) {
    return Src(OperandType::kConstantBuffer, swizzle, id, index, location);
  }
  static Src CB(DclT, uint32_t id, uint32_t lower_bound, uint32_t upper_bound) {
    return Src(OperandType::kConstantBuffer, kXYZW, id, lower_bound, upper_bound);
  }
  static Src Label(uint32_t index) { return Src(OperandType::kLabel, kXXXX, index); }
  static Src VPrim() { return Src(OperandType::kInputPrimitiveID, kXXXX); }
  static Src VICP(Index control_point, Index element, uint32_t swizzle = kXYZW) {
    return Src(OperandType::kInputControlPoint, swizzle, control_point, element);
  }
  static Src VDomain(uint32_t swizzle = kXYZW) {
    return Src(OperandType::kInputDomainPoint, swizzle);
  }
  static Src U(uint32_t index_1d, Index index_2d, uint32_t swizzle = kXYZW) {
    return Src(OperandType::kUnorderedAccessView, swizzle, index_1d, index_2d);
  }
  static Src U(DclT, uint32_t id, uint32_t lower_bound, uint32_t upper_bound) {
    return Src(OperandType::kUnorderedAccessView, kXYZW, id, lower_bound, upper_bound);
  }
  static Src VThreadID(uint32_t swizzle = kXYZW) {
    return Src(OperandType::kInputThreadID, swizzle);
  }
  static Src VThreadGroupID(uint32_t swizzle = kXYZW) {
    return Src(OperandType::kInputThreadGroupID, swizzle);
  }
  static Src VThreadIDInGroup(uint32_t swizzle = kXYZW) {
    return Src(OperandType::kInputThreadIDInGroup, swizzle);
  }
  static Src VCoverage() { return Src(OperandType::kInputCoverageMask, kXXXX); }

  [[nodiscard]] Src WithModifiers(bool absolute, bool negate) const {
    Src new_src(*this);
    new_src.absolute_ = absolute;
    new_src.negate_ = negate;
    return new_src;
  }
  [[nodiscard]] Src WithAbs(bool absolute) const { return WithModifiers(absolute, negate_); }
  [[nodiscard]] Src WithNeg(bool negate) const { return WithModifiers(absolute_, negate); }
  [[nodiscard]] Src Abs() const { return WithModifiers(true, false); }
  [[nodiscard]] Src operator-() const { return WithModifiers(absolute_, !negate_); }
  [[nodiscard]] Src Swizzle(uint32_t swizzle) const {
    Src new_src(*this);
    new_src.swizzle_ = swizzle;
    return new_src;
  }
  [[nodiscard]] Src SwizzleSwizzled(uint32_t swizzle) const {
    Src new_src(*this);
    new_src.swizzle_ = 0;
    for (uint32_t i = 0; i < 4; ++i) {
      new_src.swizzle_ |= ((swizzle_ >> (((swizzle >> (i * 2)) & 3) * 2)) & 3) << (i * 2);
    }
    return new_src;
  }
  [[nodiscard]] Src Select(uint32_t component) const {
    Src new_src(*this);
    new_src.swizzle_ = component * 0b01010101;
    return new_src;
  }
  [[nodiscard]] Src SelectFromSwizzled(uint32_t component) const {
    Src new_src(*this);
    new_src.swizzle_ = ((swizzle_ >> (component * 2)) & 3) * 0b01010101;
    return new_src;
  }

  uint32_t GetLength(uint32_t mask, bool force_vector = false) const {
    bool is_vector =
        force_vector || (mask != 0b0000 && Dest::GetMaskSingleComponent(mask) == UINT32_MAX);
    if (type_ == OperandType::kImmediate32) {
      return is_vector ? 5 : 2;
    }
    return ((absolute_ || negate_) ? 2 : 1) + OperandAddress::GetLength();
  }
  static constexpr uint32_t GetModifiedImmediate(uint32_t value, bool is_integer, bool absolute,
                                                 bool negate) {
    if (is_integer) {
      if (absolute) {
        value = uint32_t(std::abs(int32_t(value)));
      }
      if (negate) {
        value = uint32_t(-int32_t(value));
      }
    } else {
      if (absolute) {
        value &= uint32_t(INT32_MAX);
      }
      if (negate) {
        value ^= uint32_t(INT32_MAX) + 1;
      }
    }
    return value;
  }
  uint32_t GetModifiedImmediate(uint32_t swizzle_index, bool is_integer) const {
    return GetModifiedImmediate(immediate_[(swizzle_ >> (swizzle_index * 2)) & 3], is_integer,
                                absolute_, negate_);
  }
  void Write(std::vector<uint32_t>& code, bool is_integer, uint32_t mask, bool force_vector = false,
             bool in_dcl = false) const {
    uint32_t operand_token = GetOperandTokenTypeAndIndex();
    uint32_t mask_single_component = Dest::GetMaskSingleComponent(mask);
    uint32_t select_component = mask_single_component != UINT32_MAX ? mask_single_component : 0;
    bool is_vector = force_vector || (mask != 0b0000 && mask_single_component == UINT32_MAX);
    if (type_ == OperandType::kImmediate32) {
      if (is_vector) {
        operand_token |= uint32_t(OperandDimension::kVector) |
                         (uint32_t(ComponentSelection::kSwizzle) << 2) | (Src::kXYZW << 4);
      } else {
        operand_token |= uint32_t(OperandDimension::kScalar);
      }
      code.push_back(operand_token);
      if (is_vector) {
        for (uint32_t i = 0; i < 4; ++i) {
          code.push_back((mask & (1 << i)) ? GetModifiedImmediate(i, is_integer) : 0);
        }
      } else {
        code.push_back(GetModifiedImmediate(select_component, is_integer));
      }
    } else {
      switch (GetDimension(in_dcl)) {
        case OperandDimension::kScalar:
          if (is_vector) {
            operand_token |= uint32_t(OperandDimension::kVector) |
                             (uint32_t(ComponentSelection::kSwizzle) << 2) | (Src::kXXXX << 4);
          } else {
            operand_token |= uint32_t(OperandDimension::kScalar);
          }
          break;
        case OperandDimension::kVector:
          operand_token |= uint32_t(OperandDimension::kVector);
          if (is_vector) {
            operand_token |= uint32_t(ComponentSelection::kSwizzle) << 2;

            uint32_t used_component;
            if (!rex::bit_scan_forward(mask, &used_component)) {
              used_component = 0;
            }
            for (uint32_t i = 0; i < 4; ++i) {
              uint32_t swizzle_index = (mask & (1 << i)) ? i : used_component;
              operand_token |= (((swizzle_ >> (swizzle_index * 2)) & 3) << (4 + i * 2));
            }
          } else {
            operand_token |= (uint32_t(ComponentSelection::kSelect1) << 2) |
                             (((swizzle_ >> (select_component * 2)) & 3) << 4);
          }
          break;
        default:
          break;
      }
      OperandModifier modifier = OperandModifier::kNone;
      if (absolute_ && negate_) {
        modifier = OperandModifier::kAbsoluteNegate;
      } else if (absolute_) {
        modifier = OperandModifier::kAbsolute;
      } else if (negate_) {
        modifier = OperandModifier::kNegate;
      }
      if (modifier != OperandModifier::kNone) {
        operand_token |= uint32_t(1) << 31;
      }
      code.push_back(operand_token);
      if (modifier != OperandModifier::kNone) {
        code.push_back(uint32_t(ExtendedOperandType::kModifier) | (uint32_t(modifier) << 6));
      }
      OperandAddress::Write(code);
    }
  }
};

enum GlobalFlags : uint32_t {

  kGlobalFlagRefactoringAllowed = 1 << 11,
  kGlobalFlagEnableDoublePrecisionFloatOps = 1 << 12,
  kGlobalFlagForceEarlyDepthStencil = 1 << 13,

  kGlobalFlagEnableRawAndStructuredBuffers = 1 << 14,

  kGlobalFlagSkipOptimization = 1 << 15,
  kGlobalFlagEnableMinimumPrecision = 1 << 16,

  kGlobalFlagEnableDoubleExtensions = 1 << 17,

  kGlobalFlagEnableShaderExtensions = 1 << 18,

  kGlobalFlagAllResourcesBound = 1 << 19,
};

enum class SamplerMode : uint32_t {
  kDefault,
  kComparison,
  kMono,
};

enum class ConstantBufferAccessPattern : uint32_t {
  kImmediateIndexed,
  kDynamicIndexed,
};

enum class InterpolationMode : uint32_t {
  kUndefined,
  kConstant,
  kLinear,
  kLinearCentroid,
  kLinearNoPerspective,
  kLinearNoPerspectiveCentroid,
  kLinearSample,
  kLinearNoPerspectiveSample,
};

enum class ResourceDimension : uint32_t {
  kUnknown,
  kBuffer,
  kTexture1D,
  kTexture2D,
  kTexture2DMS,
  kTexture3D,
  kTextureCube,
  kTexture1DArray,
  kTexture2DArray,
  kTexture2DMSArray,
  kTextureCubeArray,
  kRawBuffer,
  kStructuredBuffer,
};

enum UAVFlags : uint32_t {
  kUAVFlagGloballyCoherentAccess = 1 << 16,
  kUAVFlagRasterizerOrderedAccess = 1 << 17,
  kUAVFlagHasOrderPreservingCounter = 1 << 23,
};

enum class Opcode : uint32_t {
  kAdd = 0,
  kAnd = 1,
  kBreak = 2,
  kCall = 4,
  kCallC = 5,
  kCase = 6,
  kContinue = 7,
  kDefault = 10,
  kDiscard = 13,
  kDiv = 14,
  kDP2 = 15,
  kDP3 = 16,
  kDP4 = 17,
  kElse = 18,
  kEndIf = 21,
  kEndLoop = 22,
  kEndSwitch = 23,
  kEq = 24,
  kExp = 25,
  kFrc = 26,
  kFToI = 27,
  kFToU = 28,
  kGE = 29,
  kIAdd = 30,
  kIf = 31,
  kIEq = 32,
  kIGE = 33,
  kILT = 34,
  kIMAd = 35,
  kIMax = 36,
  kIMin = 37,
  kIMul = 38,
  kINE = 39,
  kIShL = 41,
  kIToF = 43,
  kLabel = 44,
  kLd = 45,
  kLdMS = 46,
  kLog = 47,
  kLoop = 48,
  kLT = 49,
  kMAd = 50,
  kMin = 51,
  kMax = 52,
  kCustomData = 53,
  kMov = 54,
  kMovC = 55,
  kMul = 56,
  kNE = 57,
  kNot = 59,
  kOr = 60,
  kRet = 62,
  kRetC = 63,
  kRoundNE = 64,
  kRoundNI = 65,
  kRoundPI = 66,
  kRoundZ = 67,
  kRSq = 68,
  kSampleL = 72,
  kSampleD = 73,
  kSqRt = 75,
  kSwitch = 76,
  kSinCos = 77,
  kUDiv = 78,
  kULT = 79,
  kUGE = 80,
  kUMul = 81,
  kUMAd = 82,
  kUMax = 83,
  kUMin = 84,
  kUShR = 85,
  kUToF = 86,
  kXOr = 87,
  kDclResource = 88,
  kDclConstantBuffer = 89,
  kDclSampler = 90,
  kDclOutputTopology = 92,
  kDclInputPrimitive = 93,
  kDclMaxOutputVertexCount = 94,
  kDclInput = 95,
  kDclInputSGV = 96,
  kDclInputSIV = 97,
  kDclInputPS = 98,
  kDclInputPSSGV = 99,
  kDclInputPSSIV = 100,
  kDclOutput = 101,
  kDclOutputSIV = 103,
  kDclTemps = 104,
  kDclIndexableTemp = 105,
  kDclGlobalFlags = 106,
  kLOD = 108,
  kEmitStream = 117,
  kCutStream = 118,
  kEmitThenCutStream = 119,
  kDerivRTXCoarse = 122,
  kDerivRTXFine = 123,
  kDerivRTYCoarse = 124,
  kDerivRTYFine = 125,
  kRcp = 129,
  kF32ToF16 = 130,
  kF16ToF32 = 131,
  kCountBits = 134,
  kFirstBitHi = 135,
  kFirstBitLo = 136,
  kUBFE = 138,
  kIBFE = 139,
  kBFI = 140,
  kBFRev = 141,
  kDclStream = 143,
  kDclInputControlPointCount = 147,
  kDclTessDomain = 149,
  kDclThreadGroup = 155,
  kDclUnorderedAccessViewTyped = 156,
  kDclUnorderedAccessViewRaw = 157,
  kDclResourceRaw = 161,
  kLdUAVTyped = 163,
  kStoreUAVTyped = 164,
  kLdRaw = 165,
  kStoreRaw = 166,
  kAtomicAnd = 169,
  kAtomicOr = 170,
  kAtomicIAdd = 173,
  kEvalSampleIndex = 204,
  kEvalCentroid = 205,
};

enum class ExtendedOpcodeType : uint32_t {
  kEmpty,
  kSampleControls,
  kResourceDim,
  kResourceReturnType,
};

constexpr uint32_t OpcodeToken(Opcode opcode, uint32_t operands_length, bool saturate = false,
                               uint32_t extended_opcode_count = 0) {
  return uint32_t(opcode) | (saturate ? (uint32_t(1) << 13) : 0) |
         ((uint32_t(1) + extended_opcode_count + operands_length) << 24) |
         (extended_opcode_count ? (uint32_t(1) << 31) : 0);
}

constexpr uint32_t GetOpcodeTokenInstructionLength(uint32_t opcode_token) {
  return (opcode_token >> 24) & ((UINT32_C(1) << 7) - 1);
}

constexpr uint32_t SampleControlsExtendedOpcodeToken(int32_t aoffimmi_u, int32_t aoffimmi_v,
                                                     int32_t aoffimmi_w, bool extended = false) {
  return uint32_t(ExtendedOpcodeType::kSampleControls) |
         ((uint32_t(aoffimmi_u) & uint32_t(0b1111)) << 9) |
         ((uint32_t(aoffimmi_v) & uint32_t(0b1111)) << 13) |
         ((uint32_t(aoffimmi_w) & uint32_t(0b1111)) << 17) | (extended ? (uint32_t(1) << 31) : 0);
}

constexpr uint32_t ResourceReturnTypeToken(ResourceReturnType x, ResourceReturnType y,
                                           ResourceReturnType z, ResourceReturnType w) {
  return uint32_t(x) | (uint32_t(y) << 4) | (uint32_t(z) << 8) | (uint32_t(w) << 12);
}

constexpr uint32_t ResourceReturnTypeX4Token(ResourceReturnType xyzw) {
  return ResourceReturnTypeToken(xyzw, xyzw, xyzw, xyzw);
}

class Assembler {
 public:
  Assembler(std::vector<uint32_t>& code, Statistics& stat) : code_(code), stat_(stat) {}

  void OpAdd(const Dest& dest, const Src& src0, const Src& src1, bool saturate = false) {
    EmitAluOp(Opcode::kAdd, 0b00, dest, src0, src1, saturate);
    ++stat_.float_instruction_count;
  }
  void OpAnd(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kAnd, 0b11, dest, src0, src1);
    ++stat_.uint_instruction_count;
  }
  void OpBreak() {
    code_.push_back(OpcodeToken(Opcode::kBreak, 0));
    ++stat_.instruction_count;
  }
  void OpCall(const Src& label) {
    EmitFlowOp(Opcode::kCall, label);
    ++stat_.static_flow_control_count;
  }
  void OpCallC(bool test, const Src& src, const Src& label) {
    EmitFlowOp(Opcode::kCallC, src, label, test);
    ++stat_.dynamic_flow_control_count;
  }
  void OpCase(const Src& src) {
    EmitFlowOp(Opcode::kCase, src);
    ++stat_.static_flow_control_count;
  }
  void OpContinue() {
    code_.push_back(OpcodeToken(Opcode::kContinue, 0));
    ++stat_.instruction_count;
  }
  void OpDefault() {
    code_.push_back(OpcodeToken(Opcode::kDefault, 0));
    ++stat_.instruction_count;
    ++stat_.static_flow_control_count;
  }
  void OpDiscard(bool test, const Src& src) { EmitFlowOp(Opcode::kDiscard, src, test); }
  void OpDiv(const Dest& dest, const Src& src0, const Src& src1, bool saturate = false) {
    EmitAluOp(Opcode::kDiv, 0b00, dest, src0, src1, saturate);
    ++stat_.float_instruction_count;
  }
  void OpDP2(const Dest& dest, const Src& src0, const Src& src1, bool saturate = false) {
    uint32_t operands_length = dest.GetLength() + src0.GetLength(0b0011) + src1.GetLength(0b0011);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDP2, operands_length, saturate));
    dest.Write(code_);
    src0.Write(code_, false, 0b0011);
    src1.Write(code_, false, 0b0011);
    ++stat_.instruction_count;
    ++stat_.float_instruction_count;
  }
  void OpDP3(const Dest& dest, const Src& src0, const Src& src1, bool saturate = false) {
    uint32_t operands_length = dest.GetLength() + src0.GetLength(0b0111) + src1.GetLength(0b0111);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDP3, operands_length, saturate));
    dest.Write(code_);
    src0.Write(code_, false, 0b0111);
    src1.Write(code_, false, 0b0111);
    ++stat_.instruction_count;
    ++stat_.float_instruction_count;
  }
  void OpDP4(const Dest& dest, const Src& src0, const Src& src1, bool saturate = false) {
    uint32_t operands_length = dest.GetLength() + src0.GetLength(0b1111) + src1.GetLength(0b1111);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDP4, operands_length, saturate));
    dest.Write(code_);
    src0.Write(code_, false, 0b1111);
    src1.Write(code_, false, 0b1111);
    ++stat_.instruction_count;
    ++stat_.float_instruction_count;
  }
  void OpElse() {
    code_.push_back(OpcodeToken(Opcode::kElse, 0));
    ++stat_.instruction_count;
  }
  void OpEndIf() {
    code_.push_back(OpcodeToken(Opcode::kEndIf, 0));
    ++stat_.instruction_count;
  }
  void OpEndLoop() {
    code_.push_back(OpcodeToken(Opcode::kEndLoop, 0));
    ++stat_.instruction_count;
  }
  void OpEndSwitch() {
    code_.push_back(OpcodeToken(Opcode::kEndSwitch, 0));
    ++stat_.instruction_count;
  }
  void OpEq(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kEq, 0b00, dest, src0, src1);
    ++stat_.float_instruction_count;
  }
  void OpExp(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kExp, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpFrc(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kFrc, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpFToI(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kFToI, 0b0, dest, src);
    ++stat_.conversion_instruction_count;
  }
  void OpFToU(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kFToU, 0b0, dest, src);
    ++stat_.conversion_instruction_count;
  }
  void OpGE(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kGE, 0b00, dest, src0, src1);
    ++stat_.float_instruction_count;
  }
  void OpIAdd(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kIAdd, 0b11, dest, src0, src1);
    ++stat_.int_instruction_count;
  }
  void OpIf(bool test, const Src& src) {
    EmitFlowOp(Opcode::kIf, src, test);
    ++stat_.dynamic_flow_control_count;
  }
  void OpIEq(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kIEq, 0b11, dest, src0, src1);
    ++stat_.int_instruction_count;
  }
  void OpIGE(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kIGE, 0b11, dest, src0, src1);
    ++stat_.int_instruction_count;
  }
  void OpILT(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kILT, 0b11, dest, src0, src1);
    ++stat_.int_instruction_count;
  }
  void OpIMAd(const Dest& dest, const Src& mul0, const Src& mul1, const Src& add) {
    EmitAluOp(Opcode::kIMAd, 0b111, dest, mul0, mul1, add);
    ++stat_.int_instruction_count;
  }
  void OpIMax(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kIMax, 0b11, dest, src0, src1);
    ++stat_.int_instruction_count;
  }
  void OpIMin(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kIMin, 0b11, dest, src0, src1);
    ++stat_.int_instruction_count;
  }
  void OpIMul(const Dest& dest_hi, const Dest& dest_lo, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kIMul, 0b11, dest_hi, dest_lo, src0, src1);
    ++stat_.int_instruction_count;
  }
  void OpINE(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kINE, 0b11, dest, src0, src1);
    ++stat_.int_instruction_count;
  }
  void OpIShL(const Dest& dest, const Src& value, const Src& shift) {
    EmitAluOp(Opcode::kIShL, 0b11, dest, value, shift);
    ++stat_.int_instruction_count;
  }
  void OpIToF(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kIToF, 0b1, dest, src);
    ++stat_.conversion_instruction_count;
  }
  void OpLabel(const Src& label) {
    uint32_t operands_length = label.GetLength(0b0000);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kLabel, operands_length));
    label.Write(code_, true, 0b0000);
  }
  void OpLd(const Dest& dest, const Src& address, uint32_t address_mask, const Src& resource,
            int32_t aoffimmi_u = 0, int32_t aoffimmi_v = 0, int32_t aoffimmi_w = 0) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t sample_controls = 0;
    if (aoffimmi_u || aoffimmi_v || aoffimmi_w) {
      sample_controls = SampleControlsExtendedOpcodeToken(aoffimmi_u, aoffimmi_v, aoffimmi_w);
    }
    uint32_t operands_length = dest.GetLength() + address.GetLength(address_mask, true) +
                               resource.GetLength(dest_write_mask, true);
    code_.reserve(code_.size() + 1 + (sample_controls ? 1 : 0) + operands_length);
    code_.push_back(OpcodeToken(Opcode::kLd, operands_length, false, sample_controls ? 1 : 0));
    if (sample_controls) {
      code_.push_back(sample_controls);
    }
    dest.Write(code_);
    address.Write(code_, false, address_mask, true);
    resource.Write(code_, false, dest_write_mask, true);
    ++stat_.instruction_count;
    ++stat_.texture_load_instructions;
  }
  void OpLdMS(const Dest& dest, const Src& address, uint32_t address_mask, const Src& resource,
              const Src& sample_index, int32_t aoffimmi_u = 0, int32_t aoffimmi_v = 0) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t sample_controls = 0;
    if (aoffimmi_u || aoffimmi_v) {
      sample_controls = SampleControlsExtendedOpcodeToken(aoffimmi_u, aoffimmi_v, 0);
    }
    uint32_t operands_length = dest.GetLength() + address.GetLength(address_mask, true) +
                               resource.GetLength(dest_write_mask, true) +
                               sample_index.GetLength(0b0000);
    code_.reserve(code_.size() + 1 + (sample_controls ? 1 : 0) + operands_length);
    code_.push_back(OpcodeToken(Opcode::kLdMS, operands_length, false, sample_controls ? 1 : 0));
    if (sample_controls) {
      code_.push_back(sample_controls);
    }
    dest.Write(code_);
    address.Write(code_, false, address_mask, true);
    resource.Write(code_, false, dest_write_mask, true);
    sample_index.Write(code_, true, 0b0000);
    ++stat_.instruction_count;
    ++stat_.texture_load_instructions;
  }
  void OpLog(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kLog, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpLoop() {
    code_.push_back(OpcodeToken(Opcode::kLoop, 0));
    ++stat_.instruction_count;
    ++stat_.dynamic_flow_control_count;
  }
  void OpLT(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kLT, 0b00, dest, src0, src1);
    ++stat_.float_instruction_count;
  }
  void OpMAd(const Dest& dest, const Src& mul0, const Src& mul1, const Src& add,
             bool saturate = false) {
    EmitAluOp(Opcode::kMAd, 0b000, dest, mul0, mul1, add, saturate);
    ++stat_.float_instruction_count;
  }
  void OpMin(const Dest& dest, const Src& src0, const Src& src1, bool saturate = false) {
    EmitAluOp(Opcode::kMin, 0b00, dest, src0, src1, saturate);
    ++stat_.float_instruction_count;
  }
  void OpMax(const Dest& dest, const Src& src0, const Src& src1, bool saturate = false) {
    EmitAluOp(Opcode::kMax, 0b00, dest, src0, src1, saturate);
    ++stat_.float_instruction_count;
  }

  void* OpCustomData(CustomDataClass custom_data_class, uint32_t length_bytes) {
    uint32_t length_bytes_aligned = rex::align(length_bytes, uint32_t(sizeof(uint32_t)));
    uint32_t total_length_dwords = length_bytes_aligned / sizeof(uint32_t) + 2;
    size_t offset_dwords = code_.size();
    code_.resize(offset_dwords + total_length_dwords);
    uint32_t* data = code_.data() + offset_dwords;

    *(data++) = uint32_t(Opcode::kCustomData) | (uint32_t(custom_data_class) << 11);
    *(data++) = total_length_dwords;

    std::memset(reinterpret_cast<uint8_t*>(data) + length_bytes, dxbc::kAlignmentPadding,
                length_bytes_aligned - length_bytes);
    return data;
  }
  void OpMov(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kMov, 0b0, dest, src, saturate);
    if (dest.type_ == OperandType::kIndexableTemp || src.type_ == OperandType::kIndexableTemp) {
      ++stat_.array_instruction_count;
    } else {
      ++stat_.mov_instruction_count;
    }
  }
  void OpMovC(const Dest& dest, const Src& test, const Src& src_nz, const Src& src_z,
              bool saturate = false) {
    EmitAluOp(Opcode::kMovC, 0b001, dest, test, src_nz, src_z, saturate);
    ++stat_.movc_instruction_count;
  }
  void OpMul(const Dest& dest, const Src& src0, const Src& src1, bool saturate = false) {
    EmitAluOp(Opcode::kMul, 0b00, dest, src0, src1, saturate);
    ++stat_.float_instruction_count;
  }
  void OpNE(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kNE, 0b00, dest, src0, src1);
    ++stat_.float_instruction_count;
  }
  void OpNot(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kNot, 0b1, dest, src);
    ++stat_.uint_instruction_count;
  }
  void OpOr(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kOr, 0b11, dest, src0, src1);
    ++stat_.uint_instruction_count;
  }
  void OpRet() {
    code_.push_back(OpcodeToken(Opcode::kRet, 0));
    ++stat_.instruction_count;
    ++stat_.static_flow_control_count;
  }
  void OpRetC(bool test, const Src& src) {
    EmitFlowOp(Opcode::kRetC, src, test);
    ++stat_.dynamic_flow_control_count;
  }
  void OpRoundNE(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kRoundNE, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpRoundNI(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kRoundNI, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpRoundPI(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kRoundPI, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpRoundZ(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kRoundZ, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpRSq(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kRSq, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpSampleL(const Dest& dest, const Src& address, uint32_t address_components,
                 const Src& resource, const Src& sampler, const Src& lod, int32_t aoffimmi_u = 0,
                 int32_t aoffimmi_v = 0, int32_t aoffimmi_w = 0) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t sample_controls = 0;
    if (aoffimmi_u || aoffimmi_v || aoffimmi_w) {
      sample_controls = SampleControlsExtendedOpcodeToken(aoffimmi_u, aoffimmi_v, aoffimmi_w);
    }
    uint32_t address_mask = (1 << address_components) - 1;
    uint32_t operands_length = dest.GetLength() + address.GetLength(address_mask) +
                               resource.GetLength(dest_write_mask, true) +
                               sampler.GetLength(0b0000) + lod.GetLength(0b0000);
    code_.reserve(code_.size() + 1 + (sample_controls ? 1 : 0) + operands_length);
    code_.push_back(OpcodeToken(Opcode::kSampleL, operands_length, false, sample_controls ? 1 : 0));
    if (sample_controls) {
      code_.push_back(sample_controls);
    }
    dest.Write(code_);
    address.Write(code_, false, address_mask);
    resource.Write(code_, false, dest_write_mask, true);
    sampler.Write(code_, false, 0b0000);
    lod.Write(code_, false, 0b0000);
    ++stat_.instruction_count;
    ++stat_.texture_normal_instructions;
  }
  void OpSampleD(const Dest& dest, const Src& address, uint32_t address_components,
                 const Src& resource, const Src& sampler, const Src& x_derivatives,
                 const Src& y_derivatives, uint32_t derivatives_components, int32_t aoffimmi_u = 0,
                 int32_t aoffimmi_v = 0, int32_t aoffimmi_w = 0) {
    assert_true(derivatives_components <= address_components);
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t sample_controls = 0;
    if (aoffimmi_u || aoffimmi_v || aoffimmi_w) {
      sample_controls = SampleControlsExtendedOpcodeToken(aoffimmi_u, aoffimmi_v, aoffimmi_w);
    }
    uint32_t address_mask = (1 << address_components) - 1;
    uint32_t derivatives_mask = (1 << derivatives_components) - 1;
    uint32_t operands_length = dest.GetLength() + address.GetLength(address_mask) +
                               resource.GetLength(dest_write_mask, true) +
                               sampler.GetLength(0b0000) +
                               x_derivatives.GetLength(derivatives_mask, address_components > 1) +
                               y_derivatives.GetLength(derivatives_mask, address_components > 1);
    code_.reserve(code_.size() + 1 + (sample_controls ? 1 : 0) + operands_length);
    code_.push_back(OpcodeToken(Opcode::kSampleD, operands_length, false, sample_controls ? 1 : 0));
    if (sample_controls) {
      code_.push_back(sample_controls);
    }
    dest.Write(code_);
    address.Write(code_, false, address_mask);
    resource.Write(code_, false, dest_write_mask, true);
    sampler.Write(code_, false, 0b0000);
    x_derivatives.Write(code_, false, derivatives_mask, address_components > 1);
    y_derivatives.Write(code_, false, derivatives_mask, address_components > 1);
    ++stat_.instruction_count;
    ++stat_.texture_gradient_instructions;
  }
  void OpSqRt(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kSqRt, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpSwitch(const Src& src) {
    EmitFlowOp(Opcode::kSwitch, src);
    ++stat_.dynamic_flow_control_count;
  }
  void OpSinCos(const Dest& dest_sin, const Dest& dest_cos, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kSinCos, 0b0, dest_sin, dest_cos, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpUDiv(const Dest& dest_quotient, const Dest& dest_remainder, const Src& src0,
              const Src& src1) {
    EmitAluOp(Opcode::kUDiv, 0b11, dest_quotient, dest_remainder, src0, src1);
    ++stat_.uint_instruction_count;
  }
  void OpULT(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kULT, 0b11, dest, src0, src1);
    ++stat_.uint_instruction_count;
  }
  void OpUGE(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kUGE, 0b11, dest, src0, src1);
    ++stat_.uint_instruction_count;
  }
  void OpUMul(const Dest& dest_hi, const Dest& dest_lo, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kUMul, 0b11, dest_hi, dest_lo, src0, src1);
    ++stat_.uint_instruction_count;
  }
  void OpUMAd(const Dest& dest, const Src& mul0, const Src& mul1, const Src& add) {
    EmitAluOp(Opcode::kUMAd, 0b111, dest, mul0, mul1, add);
    ++stat_.uint_instruction_count;
  }
  void OpUMax(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kUMax, 0b11, dest, src0, src1);
    ++stat_.uint_instruction_count;
  }
  void OpUMin(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kUMin, 0b11, dest, src0, src1);
    ++stat_.uint_instruction_count;
  }
  void OpUShR(const Dest& dest, const Src& value, const Src& shift) {
    EmitAluOp(Opcode::kUShR, 0b11, dest, value, shift);
    ++stat_.uint_instruction_count;
  }
  void OpUToF(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kUToF, 0b1, dest, src);
    ++stat_.conversion_instruction_count;
  }
  void OpXOr(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kXOr, 0b11, dest, src0, src1);
    ++stat_.uint_instruction_count;
  }
  void OpDclResource(ResourceDimension dimension, uint32_t return_type_token, const Src& operand,
                     uint32_t space = 0) {
    uint32_t operands_length = operand.GetLength(0b1111, false);
    code_.reserve(code_.size() + 3 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclResource, 2 + operands_length) |
                    (uint32_t(dimension) << 11));
    operand.Write(code_, false, 0b1111, false, true);
    code_.push_back(return_type_token);
    code_.push_back(space);
  }

  void OpDclConstantBuffer(
      const Src& operand, uint32_t size_vectors,
      ConstantBufferAccessPattern access_pattern = ConstantBufferAccessPattern::kImmediateIndexed,
      uint32_t space = 0) {
    uint32_t operands_length = operand.GetLength(0b1111, false);
    code_.reserve(code_.size() + 3 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclConstantBuffer, 2 + operands_length) |
                    (uint32_t(access_pattern) << 11));
    operand.Write(code_, false, 0b1111, false, true);
    code_.push_back(size_vectors);
    code_.push_back(space);
  }
  void OpDclSampler(const Src& operand, SamplerMode mode = SamplerMode::kDefault,
                    uint32_t space = 0) {
    uint32_t operands_length = operand.GetLength(0b1111, false);
    code_.reserve(code_.size() + 2 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclSampler, 1 + operands_length) | (uint32_t(mode) << 11));
    operand.Write(code_, false, 0b1111, false, true);
    code_.push_back(space);
  }

  void OpDclOutputTopology(PrimitiveTopology output_topology) {
    code_.push_back(OpcodeToken(Opcode::kDclOutputTopology, 0) | (uint32_t(output_topology) << 11));
    stat_.gs_output_topology = output_topology;
  }

  void OpDclInputPrimitive(Primitive input_primitive) {
    code_.push_back(OpcodeToken(Opcode::kDclInputPrimitive, 0) | (uint32_t(input_primitive) << 11));
    stat_.input_primitive = input_primitive;
  }

  size_t OpDclMaxOutputVertexCount(uint32_t count) {
    code_.reserve(code_.size() + 2);
    code_.push_back(OpcodeToken(Opcode::kDclMaxOutputVertexCount, 1));
    code_.push_back(count);
    stat_.gs_max_output_vertex_count = count;
    return code_.size() - 1;
  }
  void OpDclInput(const Dest& operand) {
    uint32_t operands_length = operand.GetLength();
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclInput, operands_length));
    operand.Write(code_, true);
    ++stat_.dcl_count;
  }
  void OpDclInputSGV(const Dest& operand, Name name) {
    uint32_t operands_length = operand.GetLength();
    code_.reserve(code_.size() + 2 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclInputSGV, 1 + operands_length));
    operand.Write(code_, true);
    code_.push_back(uint32_t(name));
    ++stat_.dcl_count;
  }
  void OpDclInputSIV(const Dest& operand, Name name) {
    uint32_t operands_length = operand.GetLength();
    code_.reserve(code_.size() + 2 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclInputSIV, 1 + operands_length));
    operand.Write(code_, true);
    code_.push_back(uint32_t(name));
    ++stat_.dcl_count;
  }
  void OpDclInputPS(InterpolationMode interpolation_mode, const Dest& operand) {
    uint32_t operands_length = operand.GetLength();
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclInputPS, operands_length) |
                    (uint32_t(interpolation_mode) << 11));
    operand.Write(code_, true);
    ++stat_.dcl_count;
  }
  void OpDclInputPSSGV(const Dest& operand, Name name) {
    uint32_t operands_length = operand.GetLength();
    code_.reserve(code_.size() + 2 + operands_length);

    code_.push_back(OpcodeToken(Opcode::kDclInputPSSGV, 1 + operands_length) |
                    (uint32_t(InterpolationMode::kConstant) << 11));
    operand.Write(code_, true);
    code_.push_back(uint32_t(name));
    ++stat_.dcl_count;
  }
  void OpDclInputPSSIV(InterpolationMode interpolation_mode, const Dest& operand, Name name) {
    uint32_t operands_length = operand.GetLength();
    code_.reserve(code_.size() + 2 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclInputPSSIV, 1 + operands_length) |
                    (uint32_t(interpolation_mode) << 11));
    operand.Write(code_, true);
    code_.push_back(uint32_t(name));
    ++stat_.dcl_count;
  }
  void OpDclOutput(const Dest& operand) {
    uint32_t operands_length = operand.GetLength();
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclOutput, operands_length));
    operand.Write(code_, true);
    ++stat_.dcl_count;
  }
  void OpDclOutputSIV(const Dest& operand, Name name) {
    uint32_t operands_length = operand.GetLength();
    code_.reserve(code_.size() + 2 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclOutputSIV, 1 + operands_length));
    operand.Write(code_, true);
    code_.push_back(uint32_t(name));
    ++stat_.dcl_count;
  }

  size_t OpDclTemps(uint32_t count) {
    code_.reserve(code_.size() + 2);
    code_.push_back(OpcodeToken(Opcode::kDclTemps, 1));
    code_.push_back(count);
    stat_.temp_register_count = count;
    return code_.size() - 1;
  }
  void OpDclIndexableTemp(uint32_t index, uint32_t count, uint32_t component_count) {
    code_.reserve(code_.size() + 4);
    code_.push_back(OpcodeToken(Opcode::kDclIndexableTemp, 3));
    code_.push_back(index);
    code_.push_back(count);
    code_.push_back(component_count);
    stat_.temp_array_count += count;
  }

  void OpDclGlobalFlags(uint32_t flags) {
    code_.push_back(OpcodeToken(Opcode::kDclGlobalFlags, 0) | flags);
  }
  void OpLOD(const Dest& dest, const Src& address, uint32_t address_components, const Src& resource,
             const Src& sampler) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t address_mask = (1 << address_components) - 1;
    uint32_t operands_length = dest.GetLength() + address.GetLength(address_mask) +
                               resource.GetLength(dest_write_mask) + sampler.GetLength(0b0000);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kLOD, operands_length));
    dest.Write(code_);
    address.Write(code_, false, address_mask);
    resource.Write(code_, false, dest_write_mask);
    sampler.Write(code_, false, 0b0000);
    ++stat_.instruction_count;
    ++stat_.lod_instructions;
  }
  void OpEmitStream(const Dest& stream) {
    uint32_t operands_length = stream.GetLength();
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kEmitStream, operands_length));
    stream.Write(code_);
    ++stat_.instruction_count;
    ++stat_.emit_instruction_count;
  }
  void OpCutStream(const Dest& stream) {
    uint32_t operands_length = stream.GetLength();
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kCutStream, operands_length));
    stream.Write(code_);
    ++stat_.instruction_count;
    ++stat_.cut_instruction_count;
  }

  void OpEmitThenCutStream(const Dest& stream) {
    uint32_t operands_length = stream.GetLength();
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kEmitThenCutStream, operands_length));
    stream.Write(code_);
    ++stat_.instruction_count;

    ++stat_.emit_instruction_count;
    ++stat_.cut_instruction_count;
  }
  void OpDerivRTXCoarse(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kDerivRTXCoarse, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpDerivRTXFine(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kDerivRTXFine, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpDerivRTYCoarse(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kDerivRTYCoarse, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpDerivRTYFine(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kDerivRTYFine, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpRcp(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kRcp, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpF32ToF16(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kF32ToF16, 0b0, dest, src);
    ++stat_.conversion_instruction_count;
  }
  void OpF16ToF32(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kF16ToF32, 0b1, dest, src);
    ++stat_.conversion_instruction_count;
  }
  void OpCountBits(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kCountBits, 0b1, dest, src);
    ++stat_.uint_instruction_count;
  }
  void OpFirstBitHi(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kFirstBitHi, 0b1, dest, src);
    ++stat_.uint_instruction_count;
  }
  void OpFirstBitLo(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kFirstBitLo, 0b1, dest, src);
    ++stat_.uint_instruction_count;
  }
  void OpUBFE(const Dest& dest, const Src& width, const Src& offset, const Src& src) {
    EmitAluOp(Opcode::kUBFE, 0b111, dest, width, offset, src);
    ++stat_.uint_instruction_count;
  }
  void OpIBFE(const Dest& dest, const Src& width, const Src& offset, const Src& src) {
    EmitAluOp(Opcode::kIBFE, 0b111, dest, width, offset, src);
    ++stat_.int_instruction_count;
  }
  void OpBFI(const Dest& dest, const Src& width, const Src& offset, const Src& from,
             const Src& to) {
    EmitAluOp(Opcode::kBFI, 0b1111, dest, width, offset, from, to);
    ++stat_.uint_instruction_count;
  }
  void OpBFRev(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kBFRev, 0b1, dest, src);
    ++stat_.uint_instruction_count;
  }
  void OpDclStream(const Dest& stream) {
    uint32_t operands_length = stream.GetLength();
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclStream, operands_length));
    stream.Write(code_, true);
  }
  void OpDclInputControlPointCount(uint32_t count) {
    code_.push_back(OpcodeToken(Opcode::kDclInputControlPointCount, 0) | (count << 11));
    stat_.c_control_points = count;
  }
  void OpDclTessDomain(TessellatorDomain domain) {
    code_.push_back(OpcodeToken(Opcode::kDclTessDomain, 0) | (uint32_t(domain) << 11));
    stat_.tessellator_domain = domain;
  }
  void OpDclThreadGroup(uint32_t x, uint32_t y, uint32_t z) {
    code_.reserve(code_.size() + 4);
    code_.push_back(OpcodeToken(Opcode::kDclThreadGroup, 3));
    code_.push_back(x);
    code_.push_back(y);
    code_.push_back(z);
  }

  void OpDclUnorderedAccessViewTyped(ResourceDimension dimension, uint32_t flags,
                                     uint32_t return_type_token, const Src& operand,
                                     uint32_t space = 0) {
    uint32_t operands_length = operand.GetLength(0b1111, false);
    code_.reserve(code_.size() + 3 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclUnorderedAccessViewTyped, 2 + operands_length) |
                    (uint32_t(dimension) << 11) | flags);
    operand.Write(code_, false, 0b1111, false, true);
    code_.push_back(return_type_token);
    code_.push_back(space);
  }

  void OpDclUnorderedAccessViewRaw(uint32_t flags, const Src& operand, uint32_t space = 0) {
    uint32_t operands_length = operand.GetLength(0b1111, false);
    code_.reserve(code_.size() + 2 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclUnorderedAccessViewRaw, 1 + operands_length) | flags);
    operand.Write(code_, true, 0b1111, false, true);
    code_.push_back(space);
  }
  void OpDclResourceRaw(const Src& operand, uint32_t space = 0) {
    uint32_t operands_length = operand.GetLength(0b1111, false);
    code_.reserve(code_.size() + 2 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclResourceRaw, 1 + operands_length));
    operand.Write(code_, true, 0b1111, false, true);
    code_.push_back(space);
  }
  void OpLdUAVTyped(const Dest& dest, const Src& address, uint32_t address_components,
                    const Src& uav) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t address_mask = (1 << address_components) - 1;
    uint32_t operands_length = dest.GetLength() + address.GetLength(address_mask, true) +
                               uav.GetLength(dest_write_mask, true);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kLdUAVTyped, operands_length));
    dest.Write(code_);
    address.Write(code_, true, address_mask, true);
    uav.Write(code_, false, dest_write_mask, true);
    ++stat_.instruction_count;
    ++stat_.texture_load_instructions;
  }
  void OpStoreUAVTyped(const Dest& dest, const Src& address, uint32_t address_components,
                       const Src& value) {
    uint32_t dest_write_mask = dest.GetMask();

    assert_true(dest_write_mask == 0b1111);
    uint32_t address_mask = (1 << address_components) - 1;
    uint32_t operands_length =
        dest.GetLength() + address.GetLength(address_mask, true) + value.GetLength(dest_write_mask);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kStoreUAVTyped, operands_length));
    dest.Write(code_);
    address.Write(code_, true, address_mask, true);
    value.Write(code_, false, dest_write_mask);
    ++stat_.instruction_count;
    ++stat_.c_texture_store_instructions;
  }
  void OpLdRaw(const Dest& dest, const Src& byte_offset, const Src& src) {
    uint32_t dest_write_mask = dest.GetMask();
    assert_true(dest_write_mask == 0b0001 || dest_write_mask == 0b0010 ||
                dest_write_mask == 0b0100 || dest_write_mask == 0b1000 ||
                dest_write_mask == 0b0011 || dest_write_mask == 0b0111 ||
                dest_write_mask == 0b1111);
    uint32_t component_count = rex::bit_count(dest_write_mask);
    assert_true((src.swizzle_ & ((1 << (component_count * 2)) - 1)) ==
                (Src::kXYZW & ((1 << (component_count * 2)) - 1)));
    uint32_t src_mask = (1 << component_count) - 1;
    uint32_t operands_length =
        dest.GetLength() + byte_offset.GetLength(0b0000) + src.GetLength(src_mask, true);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kLdRaw, operands_length));
    dest.Write(code_);
    byte_offset.Write(code_, true, 0b0000);
    src.Write(code_, true, src_mask, true);
    ++stat_.instruction_count;
    ++stat_.texture_load_instructions;
  }
  void OpStoreRaw(const Dest& dest, const Src& byte_offset, const Src& value) {
    uint32_t dest_write_mask = dest.GetMask();
    assert_true(dest_write_mask == 0b0001 || dest_write_mask == 0b0011 ||
                dest_write_mask == 0b0111 || dest_write_mask == 0b1111);
    uint32_t operands_length =
        dest.GetLength() + byte_offset.GetLength(0b0000) + value.GetLength(dest_write_mask);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kStoreRaw, operands_length));
    dest.Write(code_);
    byte_offset.Write(code_, true, 0b0000);
    value.Write(code_, true, dest_write_mask);
    ++stat_.instruction_count;
    ++stat_.c_texture_store_instructions;
  }
  void OpAtomicAnd(const Dest& dest, const Src& address, uint32_t address_components,
                   const Src& value) {
    EmitAtomicOp(Opcode::kAtomicAnd, dest, address, address_components, value);
  }
  void OpAtomicOr(const Dest& dest, const Src& address, uint32_t address_components,
                  const Src& value) {
    EmitAtomicOp(Opcode::kAtomicOr, dest, address, address_components, value);
  }
  void OpAtomicIAdd(const Dest& dest, const Src& address, uint32_t address_components,
                    const Src& value) {
    EmitAtomicOp(Opcode::kAtomicIAdd, dest, address, address_components, value);
  }
  void OpEvalSampleIndex(const Dest& dest, const Src& value, const Src& sample_index) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t operands_length =
        dest.GetLength() + value.GetLength(dest_write_mask) + sample_index.GetLength(0b0000);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kEvalSampleIndex, operands_length));
    dest.Write(code_);
    value.Write(code_, false, dest_write_mask);
    sample_index.Write(code_, true, 0b0000);
    ++stat_.instruction_count;
  }
  void OpEvalCentroid(const Dest& dest, const Src& value) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t operands_length = dest.GetLength() + value.GetLength(dest_write_mask);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kEvalCentroid, operands_length));
    dest.Write(code_);
    value.Write(code_, false, dest_write_mask);
    ++stat_.instruction_count;
  }

 private:
  void EmitAluOp(Opcode opcode, uint32_t src_are_integer, const Dest& dest, const Src& src,
                 bool saturate = false) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t operands_length = dest.GetLength() + src.GetLength(dest_write_mask);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(opcode, operands_length, saturate));
    dest.Write(code_);
    src.Write(code_, (src_are_integer & 0b1) != 0, dest_write_mask);
    ++stat_.instruction_count;
  }
  void EmitAluOp(Opcode opcode, uint32_t src_are_integer, const Dest& dest, const Src& src0,
                 const Src& src1, bool saturate = false) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t operands_length =
        dest.GetLength() + src0.GetLength(dest_write_mask) + src1.GetLength(dest_write_mask);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(opcode, operands_length, saturate));
    dest.Write(code_);
    src0.Write(code_, (src_are_integer & 0b1) != 0, dest_write_mask);
    src1.Write(code_, (src_are_integer & 0b10) != 0, dest_write_mask);
    ++stat_.instruction_count;
  }
  void EmitAluOp(Opcode opcode, uint32_t src_are_integer, const Dest& dest, const Src& src0,
                 const Src& src1, const Src& src2, bool saturate = false) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t operands_length = dest.GetLength() + src0.GetLength(dest_write_mask) +
                               src1.GetLength(dest_write_mask) + src2.GetLength(dest_write_mask);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(opcode, operands_length, saturate));
    dest.Write(code_);
    src0.Write(code_, (src_are_integer & 0b1) != 0, dest_write_mask);
    src1.Write(code_, (src_are_integer & 0b10) != 0, dest_write_mask);
    src2.Write(code_, (src_are_integer & 0b100) != 0, dest_write_mask);
    ++stat_.instruction_count;
  }
  void EmitAluOp(Opcode opcode, uint32_t src_are_integer, const Dest& dest, const Src& src0,
                 const Src& src1, const Src& src2, const Src& src3, bool saturate = false) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t operands_length = dest.GetLength() + src0.GetLength(dest_write_mask) +
                               src1.GetLength(dest_write_mask) + src2.GetLength(dest_write_mask) +
                               src3.GetLength(dest_write_mask);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(opcode, operands_length, saturate));
    dest.Write(code_);
    src0.Write(code_, (src_are_integer & 0b1) != 0, dest_write_mask);
    src1.Write(code_, (src_are_integer & 0b10) != 0, dest_write_mask);
    src2.Write(code_, (src_are_integer & 0b100) != 0, dest_write_mask);
    src3.Write(code_, (src_are_integer & 0b1000) != 0, dest_write_mask);
    ++stat_.instruction_count;
  }
  void EmitAluOp(Opcode opcode, uint32_t src_are_integer, const Dest& dest0, const Dest& dest1,
                 const Src& src, bool saturate = false) {
    uint32_t dest_write_mask = dest0.GetMask() | dest1.GetMask();
    uint32_t operands_length =
        dest0.GetLength() + dest1.GetLength() + src.GetLength(dest_write_mask);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(opcode, operands_length, saturate));
    dest0.Write(code_);
    dest1.Write(code_);
    src.Write(code_, (src_are_integer & 0b1) != 0, dest_write_mask);
    ++stat_.instruction_count;
  }
  void EmitAluOp(Opcode opcode, uint32_t src_are_integer, const Dest& dest0, const Dest& dest1,
                 const Src& src0, const Src& src1, bool saturate = false) {
    uint32_t dest_write_mask = dest0.GetMask() | dest1.GetMask();
    uint32_t operands_length = dest0.GetLength() + dest1.GetLength() +
                               src0.GetLength(dest_write_mask) + src1.GetLength(dest_write_mask);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(opcode, operands_length, saturate));
    dest0.Write(code_);
    dest1.Write(code_);
    src0.Write(code_, (src_are_integer & 0b1) != 0, dest_write_mask);
    src1.Write(code_, (src_are_integer & 0b10) != 0, dest_write_mask);
    ++stat_.instruction_count;
  }
  void EmitFlowOp(Opcode opcode, const Src& src, bool test = false) {
    uint32_t operands_length = src.GetLength(0b0000);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(opcode, operands_length) | (test ? (1 << 18) : 0));
    src.Write(code_, true, 0b0000);
    ++stat_.instruction_count;
  }
  void EmitFlowOp(Opcode opcode, const Src& src0, const Src& src1, bool test = false) {
    uint32_t operands_length = src0.GetLength(0b0000) + src1.GetLength(0b0000);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(opcode, operands_length) | (test ? (1 << 18) : 0));
    src0.Write(code_, true, 0b0000);
    src1.Write(code_, true, 0b0000);
    ++stat_.instruction_count;
  }
  void EmitAtomicOp(Opcode opcode, const Dest& dest, const Src& address,
                    uint32_t address_components, const Src& value) {
    assert_zero(dest.GetMask());
    uint32_t address_mask = (1 << address_components) - 1;
    uint32_t operands_length =
        dest.GetLength() + address.GetLength(address_mask) + value.GetLength(0b0001);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(opcode, operands_length));
    dest.Write(code_);
    address.Write(code_, true, address_mask);
    value.Write(code_, true, 0b0001);
    ++stat_.instruction_count;
    ++stat_.c_interlocked_instructions;
  }

  std::vector<uint32_t>& code_;
  Statistics& stat_;
};

}
