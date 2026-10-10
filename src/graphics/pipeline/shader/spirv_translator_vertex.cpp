

#include <rex/graphics/pipeline/shader/spirv_translator.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fmt/format.h>
#include <SPIRV/GLSL.std.450.h>
#include <rex/assert.h>
#include <rex/cvar.h>
#include <rex/logging.h>
#include <rex/math.h>
#include <rex/string/buffer.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/pipeline/shader/spirv_compatibility.h>
#include <rex/graphics/pipeline/shader/spirv.h>
#include <rex/graphics/xenos_zpd_report.h>

namespace rex::graphics {

void SpirvShaderTranslator::ResetVertexShaderInvocationStateInMain() {
  if (var_main_point_size_edge_flag_kill_vertex_ != spv::NoResult) {
    id_vector_temp_.clear();

    id_vector_temp_.push_back(builder_->makeFloatConstant(-1.0f));

    id_vector_temp_.push_back(const_float_0_);

    id_vector_temp_.push_back(const_float_0_);
    builder_->createStore(builder_->makeCompositeConstant(type_float3_, id_vector_temp_),
                          var_main_point_size_edge_flag_kill_vertex_);
  }

  for (uint32_t i = 0; i < register_count(); ++i) {
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(int(i)));
    builder_->createStore(
        const_float4_0_, builder_->createAccessChain(spv::StorageClassFunction, var_main_registers_,
                                                     id_vector_temp_));
  }

  uint32_t interpolators_remaining = GetModificationInterpolatorMask();
  uint32_t interpolator_index;
  while (rex::bit_scan_forward(interpolators_remaining, &interpolator_index)) {
    interpolators_remaining &= ~(UINT32_C(1) << interpolator_index);
    builder_->createStore(const_float4_0_, input_output_interpolators_[interpolator_index]);
  }
}

void SpirvShaderTranslator::WriteVertexIndexToRegister0(spv::Id vertex_index) {
  if (!register_count()) {
    return;
  }
  id_vector_temp_.clear();
  id_vector_temp_.push_back(const_int_0_);
  id_vector_temp_.push_back(const_int_0_);
  builder_->createStore(
      builder_->createUnaryOp(spv::OpConvertSToF, type_float_, vertex_index),
      builder_->createAccessChain(spv::StorageClassFunction, var_main_registers_, id_vector_temp_));
}

void SpirvShaderTranslator::StartVertexOrTessEvalShaderBeforeMain() {
  if (IsSpirvTessEvalShader()) {
    uint32_t control_point_count = 1;
    switch (GetSpirvShaderModification().vertex.host_vertex_shader_type) {
      case Shader::HostVertexShaderType::kTriangleDomainCPIndexed:
        control_point_count = 3;
        break;
      case Shader::HostVertexShaderType::kQuadDomainCPIndexed:
        control_point_count = 4;
        break;
      default:

        control_point_count = 1;
        break;
    }
    input_control_point_index_ = builder_->createVariable(
        spv::NoPrecision, spv::StorageClassInput,
        builder_->makeArrayType(type_float_, builder_->makeUintConstant(control_point_count), 0),
        "xe_in_control_point_index");
    builder_->addDecoration(input_control_point_index_, spv::DecorationLocation, 0);
    main_interface_.push_back(input_control_point_index_);

    input_tess_coord_ = builder_->createVariable(spv::NoPrecision, spv::StorageClassInput,
                                                 type_float3_, "gl_TessCoord");
    builder_->addDecoration(input_tess_coord_, spv::DecorationBuiltIn,
                            static_cast<int>(spv::BuiltIn::TessCoord));
    main_interface_.push_back(input_tess_coord_);
  } else {
    input_vertex_index_ = builder_->createVariable(spv::NoPrecision, spv::StorageClassInput,
                                                   type_int_, "gl_VertexIndex");
    builder_->addDecoration(input_vertex_index_, spv::DecorationBuiltIn,
                            static_cast<int>(spv::BuiltIn::VertexIndex));
    main_interface_.push_back(input_vertex_index_);
  }

  uint32_t output_location = 0;

  {
    uint32_t interpolators_remaining = GetModificationInterpolatorMask();
    uint32_t interpolator_index;
    while (rex::bit_scan_forward(interpolators_remaining, &interpolator_index)) {
      interpolators_remaining &= ~(UINT32_C(1) << interpolator_index);
      spv::Id interpolator = builder_->createVariable(
          spv::NoPrecision, spv::StorageClassOutput, type_float4_,
          fmt::format("xe_out_interpolator_{}", interpolator_index).c_str());
      input_output_interpolators_[interpolator_index] = interpolator;
      builder_->addDecoration(interpolator, spv::DecorationLocation, int(output_location));
      builder_->addDecoration(interpolator, spv::DecorationInvariant);
      main_interface_.push_back(interpolator);
      ++output_location;
    }
  }

  Modification shader_modification = GetSpirvShaderModification();

  if (shader_modification.vertex.output_point_parameters) {
    if (shader_modification.vertex.host_vertex_shader_type ==
        Shader::HostVertexShaderType::kPointListAsTriangleStrip) {
      output_point_coordinates_ = builder_->createVariable(
          spv::NoPrecision, spv::StorageClassOutput, type_float2_, "xe_out_point_coordinates");
      builder_->addDecoration(output_point_coordinates_, spv::DecorationLocation,
                              int(output_location));
      builder_->addDecoration(output_point_coordinates_, spv::DecorationInvariant);
      main_interface_.push_back(output_point_coordinates_);
      ++output_location;
    } else {
      output_point_size_ = builder_->createVariable(spv::NoPrecision, spv::StorageClassOutput,
                                                    type_float_, "xe_out_point_size");
      builder_->addDecoration(output_point_size_, spv::DecorationLocation, int(output_location));
      builder_->addDecoration(output_point_size_, spv::DecorationInvariant);
      main_interface_.push_back(output_point_size_);
      ++output_location;
    }
  }

  std::vector<spv::Id> struct_per_vertex_members;
  struct_per_vertex_members.reserve(kOutputPerVertexMemberCount);
  struct_per_vertex_members.push_back(type_float4_);

  uint32_t user_clip_plane_count = shader_modification.vertex.user_clip_plane_count;
  uint32_t clip_distance_count = 0;
  uint32_t cull_distance_count = 0;
  if (shader_modification.vertex.user_clip_plane_cull) {
    cull_distance_count = user_clip_plane_count;
  } else {
    clip_distance_count = user_clip_plane_count;
  }

  if (shader_modification.vertex.vertex_kill_and) {
    ++cull_distance_count;
  }
  output_per_vertex_clip_distance_member_index_ = 0;
  output_per_vertex_cull_distance_member_index_ = 0;
  if (clip_distance_count > 0) {
    output_per_vertex_clip_distance_member_index_ =
        static_cast<unsigned int>(struct_per_vertex_members.size());
    struct_per_vertex_members.push_back(
        builder_->makeArrayType(type_float_, builder_->makeUintConstant(clip_distance_count), 0));
  }
  if (cull_distance_count > 0) {
    output_per_vertex_cull_distance_member_index_ =
        static_cast<unsigned int>(struct_per_vertex_members.size());
    struct_per_vertex_members.push_back(
        builder_->makeArrayType(type_float_, builder_->makeUintConstant(cull_distance_count), 0));
  }

  spv::Id type_struct_per_vertex =
      builder_->makeStructType(struct_per_vertex_members, "gl_PerVertex");
  builder_->addMemberName(type_struct_per_vertex, kOutputPerVertexMemberPosition, "gl_Position");
  builder_->addMemberDecoration(type_struct_per_vertex, kOutputPerVertexMemberPosition,
                                spv::DecorationBuiltIn, static_cast<int>(spv::BuiltIn::Position));

  if (clip_distance_count > 0) {
    builder_->addMemberName(type_struct_per_vertex, output_per_vertex_clip_distance_member_index_,
                            "gl_ClipDistance");
    builder_->addMemberDecoration(
        type_struct_per_vertex, output_per_vertex_clip_distance_member_index_,
        spv::DecorationBuiltIn, static_cast<int>(spv::BuiltIn::ClipDistance));
  }
  if (cull_distance_count > 0) {
    builder_->addMemberName(type_struct_per_vertex, output_per_vertex_cull_distance_member_index_,
                            "gl_CullDistance");
    builder_->addMemberDecoration(
        type_struct_per_vertex, output_per_vertex_cull_distance_member_index_,
        spv::DecorationBuiltIn, static_cast<int>(spv::BuiltIn::CullDistance));
  }

  builder_->addDecoration(type_struct_per_vertex, spv::DecorationBlock);
  output_per_vertex_ = builder_->createVariable(spv::NoPrecision, spv::StorageClassOutput,
                                                type_struct_per_vertex, "");
  builder_->addDecoration(output_per_vertex_, spv::DecorationInvariant);
  main_interface_.push_back(output_per_vertex_);
}

void SpirvShaderTranslator::StartVertexOrTessEvalShaderInMain() {
  Modification shader_modification = GetSpirvShaderModification();
  main_vertex_rect_list_as_triangle_strip_ = IsSpirvRectListAsTriangleStrip();

  if (current_shader().writes_point_size_edge_flag_kill_vertex() & 0b101) {
    id_vector_temp_.clear();

    id_vector_temp_.push_back(builder_->makeFloatConstant(-1.0f));

    id_vector_temp_.push_back(const_float_0_);

    id_vector_temp_.push_back(const_float_0_);
    var_main_point_size_edge_flag_kill_vertex_ =
        builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_float3_,
                                 "xe_var_point_size_edge_flag_kill_vertex",
                                 builder_->makeCompositeConstant(type_float3_, id_vector_temp_));
  }

  if (!main_vertex_rect_list_as_triangle_strip_) {
    ResetVertexShaderInvocationStateInMain();
  }

  if (IsMemoryExportUsed()) {
    spv::Id memexport_allowed_for_host_vertex_of_guest_primitive = spv::NoResult;
    if (main_vertex_rect_list_as_triangle_strip_) {
      memexport_allowed_for_host_vertex_of_guest_primitive = builder_->createBinOp(
          spv::OpIEqual, type_bool_,
          builder_->createBinOp(
              spv::OpBitwiseAnd, type_uint_,
              builder_->createUnaryOp(spv::OpBitcast, type_uint_,
                                      builder_->createLoad(input_vertex_index_, spv::NoPrecision)),
              builder_->makeUintConstant(3)),
          const_uint_0_);
    } else if (shader_modification.vertex.host_vertex_shader_type ==
               Shader::HostVertexShaderType::kPointListAsTriangleStrip) {
      memexport_allowed_for_host_vertex_of_guest_primitive = builder_->createBinOp(
          spv::OpIEqual, type_bool_,
          builder_->createBinOp(
              spv::OpBitwiseAnd, type_uint_,
              builder_->createUnaryOp(spv::OpBitcast, type_uint_,
                                      builder_->createLoad(input_vertex_index_, spv::NoPrecision)),
              builder_->makeUintConstant(3)),
          const_uint_0_);
    }

    if (memexport_allowed_for_host_vertex_of_guest_primitive != spv::NoResult) {
      main_memexport_allowed_ =
          main_memexport_allowed_ != spv::NoResult
              ? builder_->createBinOp(spv::OpLogicalAnd, type_bool_, main_memexport_allowed_,
                                      memexport_allowed_for_host_vertex_of_guest_primitive)
              : memexport_allowed_for_host_vertex_of_guest_primitive;
    }
  }

  if (main_vertex_rect_list_as_triangle_strip_) {
    spv::Id host_vertex_index = builder_->createUnaryOp(
        spv::OpBitcast, type_uint_, builder_->createLoad(input_vertex_index_, spv::NoPrecision));
    var_main_rect_list_strip_vertex_ =
        builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_uint_,
                                 "xe_var_rect_strip_vertex", const_uint_0_);
    builder_->createStore(builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, host_vertex_index,
                                                builder_->makeUintConstant(3)),
                          var_main_rect_list_strip_vertex_);

    spv::Id type_int_array_3 =
        builder_->makeArrayType(type_int_, builder_->makeUintConstant(3), -1);
    var_main_rect_list_guest_vertex_indices_ =
        builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_int_array_3,
                                 "xe_var_rect_guest_vertex_indices");

    spv::Id type_float4_array_3 =
        builder_->makeArrayType(type_float4_, builder_->makeUintConstant(3), -1);
    var_main_rect_list_guest_positions_ =
        builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_float4_array_3,
                                 "xe_var_rect_guest_positions");
    uint32_t interpolators_remaining = GetModificationInterpolatorMask();
    uint32_t interpolator_index;
    while (rex::bit_scan_forward(interpolators_remaining, &interpolator_index)) {
      interpolators_remaining &= ~(UINT32_C(1) << interpolator_index);
      var_main_rect_list_guest_interpolators_[interpolator_index] = builder_->createVariable(
          spv::NoPrecision, spv::StorageClassFunction, type_float4_array_3,
          fmt::format("xe_var_rect_guest_interpolators_{}", interpolator_index).c_str());
    }

    spv::Id rect_index = builder_->createBinOp(spv::OpShiftRightLogical, type_uint_,
                                               host_vertex_index, builder_->makeUintConstant(2));
    spv::Id rect_vertex_base =
        builder_->createBinOp(spv::OpIMul, type_uint_, rect_index, builder_->makeUintConstant(3));
    spv::Id const_uint_2 = builder_->makeUintConstant(2);

    spv::Id load_vertex_index = builder_->createBinOp(
        spv::OpINotEqual, type_bool_,
        builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
                              builder_->makeUintConstant(static_cast<unsigned int>(
                                  kSysFlag_ComputeOrPrimitiveVertexIndexLoad))),
        const_uint_0_);
    spv::Id vertex_index_is_32bit = builder_->createBinOp(
        spv::OpINotEqual, type_bool_,
        builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
                              builder_->makeUintConstant(static_cast<unsigned int>(
                                  kSysFlag_ComputeOrPrimitiveVertexIndexLoad32Bit))),
        const_uint_0_);

    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantVertexIndexLoadAddress));
    spv::Id vertex_index_load_address_base = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                    id_vector_temp_),
        spv::NoPrecision);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantVertexIndexCount));
    spv::Id vertex_index_count = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                    id_vector_temp_),
        spv::NoPrecision);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantVertexIndexEndian));
    spv::Id vertex_index_endian = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                    id_vector_temp_),
        spv::NoPrecision);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantVertexBaseIndex));
    spv::Id vertex_base_index = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                    id_vector_temp_),
        spv::NoPrecision);

    for (uint32_t i = 0; i < 3; ++i) {
      spv::Id vertex_index = builder_->createBinOp(spv::OpIAdd, type_uint_, rect_vertex_base,
                                                   builder_->makeUintConstant(i));
      spv::Id vertex_index_in_bounds =
          builder_->createBinOp(spv::OpULessThan, type_bool_, vertex_index, vertex_index_count);
      spv::Id load_vertex_index_safe = builder_->createBinOp(
          spv::OpLogicalAnd, type_bool_, load_vertex_index, vertex_index_in_bounds);

      SpirvBuilder::IfBuilder load_vertex_index_if(load_vertex_index_safe,
                                                   spv::SelectionControlDontFlattenMask, *builder_);
      spv::Id loaded_vertex_index = spv::NoResult;
      {
        spv::Id vertex_index_address = builder_->createBinOp(
            spv::OpIAdd, type_uint_, vertex_index_load_address_base,
            builder_->createBinOp(
                spv::OpShiftLeftLogical, type_uint_, vertex_index,
                builder_->createTriOp(spv::OpSelect, type_uint_, vertex_index_is_32bit,
                                      const_uint_2, builder_->makeUintConstant(1))));
        loaded_vertex_index = LoadUint32FromSharedMemory(
            builder_->createUnaryOp(spv::OpBitcast, type_int_,
                                    builder_->createBinOp(spv::OpShiftRightLogical, type_uint_,
                                                          vertex_index_address, const_uint_2)));
        loaded_vertex_index = builder_->createTriOp(
            spv::OpSelect, type_uint_, vertex_index_is_32bit, loaded_vertex_index,
            builder_->createTriOp(
                spv::OpBitFieldUExtract, type_uint_, loaded_vertex_index,
                builder_->createBinOp(spv::OpShiftLeftLogical, type_uint_,
                                      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_,
                                                            vertex_index_address, const_uint_2),
                                      builder_->makeUintConstant(4 - 1)),
                builder_->makeUintConstant(16)));
        loaded_vertex_index = EndianSwap32Uint(loaded_vertex_index, vertex_index_endian);
      }
      load_vertex_index_if.makeEndIf();
      vertex_index = load_vertex_index_if.createMergePhi(loaded_vertex_index, vertex_index);
      vertex_index = builder_->createTriOp(spv::OpSelect, type_uint_, vertex_index_in_bounds,
                                           vertex_index, const_uint_0_);

      spv::Id guest_vertex_index = builder_->createBinOp(
          spv::OpIAdd, type_int_, builder_->createUnaryOp(spv::OpBitcast, type_int_, vertex_index),
          vertex_base_index);
      id_vector_temp_.clear();
      id_vector_temp_.push_back(builder_->makeIntConstant(i));
      builder_->createStore(
          guest_vertex_index,
          builder_->createAccessChain(spv::StorageClassFunction,
                                      var_main_rect_list_guest_vertex_indices_, id_vector_temp_));
    }
  }

  if (register_count()) {
    if (IsSpirvTessEvalShader()) {
      Shader::HostVertexShaderType host_type = shader_modification.vertex.host_vertex_shader_type;

      spv::Id tess_coord = builder_->createLoad(input_tess_coord_, spv::NoPrecision);

      switch (host_type) {
        case Shader::HostVertexShaderType::kTriangleDomainCPIndexed:
        case Shader::HostVertexShaderType::kTriangleDomainPatchIndexed: {
          uint_vector_temp_.clear();
          uint_vector_temp_.push_back(2);
          uint_vector_temp_.push_back(1);
          uint_vector_temp_.push_back(0);
          spv::Id tess_coord_zyx = builder_->createRvalueSwizzle(spv::NoPrecision, type_float3_,
                                                                 tess_coord, uint_vector_temp_);

          id_vector_temp_.clear();
          id_vector_temp_.push_back(const_int_0_);
          spv::Id r0_ptr = builder_->createAccessChain(spv::StorageClassFunction,
                                                       var_main_registers_, id_vector_temp_);

          id_vector_temp_.clear();
          id_vector_temp_.push_back(
              builder_->createCompositeExtract(tess_coord_zyx, type_float_, 0));
          id_vector_temp_.push_back(
              builder_->createCompositeExtract(tess_coord_zyx, type_float_, 1));
          id_vector_temp_.push_back(
              builder_->createCompositeExtract(tess_coord_zyx, type_float_, 2));
          id_vector_temp_.push_back(const_float_1_);
          builder_->createStore(builder_->createCompositeConstruct(type_float4_, id_vector_temp_),
                                r0_ptr);
          break;
        }
        case Shader::HostVertexShaderType::kQuadDomainCPIndexed: {
          spv::Id tess_coord_x = builder_->createCompositeExtract(tess_coord, type_float_, 0);
          spv::Id tess_coord_y = builder_->createCompositeExtract(tess_coord, type_float_, 1);

          id_vector_temp_.clear();
          id_vector_temp_.push_back(const_int_0_);
          spv::Id control_point_index_0 = builder_->createLoad(
              builder_->createAccessChain(spv::StorageClassInput, input_control_point_index_,
                                          id_vector_temp_),
              spv::NoPrecision);

          id_vector_temp_.clear();
          id_vector_temp_.push_back(const_int_0_);
          spv::Id r0_ptr = builder_->createAccessChain(spv::StorageClassFunction,
                                                       var_main_registers_, id_vector_temp_);
          id_vector_temp_.clear();
          id_vector_temp_.push_back(tess_coord_x);
          id_vector_temp_.push_back(tess_coord_y);
          id_vector_temp_.push_back(control_point_index_0);
          id_vector_temp_.push_back(const_float_0_);
          builder_->createStore(builder_->createCompositeConstruct(type_float4_, id_vector_temp_),
                                r0_ptr);

          for (uint32_t i = 1; i <= 3 && register_count() >= 2; ++i) {
            id_vector_temp_.clear();
            id_vector_temp_.push_back(builder_->makeIntConstant(int(i)));
            spv::Id control_point_index = builder_->createLoad(
                builder_->createAccessChain(spv::StorageClassInput, input_control_point_index_,
                                            id_vector_temp_),
                spv::NoPrecision);
            id_vector_temp_.clear();
            id_vector_temp_.push_back(builder_->makeIntConstant(1));
            id_vector_temp_.push_back(builder_->makeIntConstant(int(i - 1)));
            builder_->createStore(control_point_index, builder_->createAccessChain(
                                                           spv::StorageClassFunction,
                                                           var_main_registers_, id_vector_temp_));
          }
          break;
        }
        case Shader::HostVertexShaderType::kQuadDomainPatchIndexed: {
          uint_vector_temp_.clear();
          uint_vector_temp_.push_back(0);
          uint_vector_temp_.push_back(1);
          spv::Id tess_coord_xy = builder_->createRvalueSwizzle(spv::NoPrecision, type_float2_,
                                                                tess_coord, uint_vector_temp_);

          id_vector_temp_.clear();
          id_vector_temp_.push_back(const_int_0_);
          spv::Id patch_index_float = builder_->createLoad(
              builder_->createAccessChain(spv::StorageClassInput, input_control_point_index_,
                                          id_vector_temp_),
              spv::NoPrecision);

          id_vector_temp_.clear();
          id_vector_temp_.push_back(const_int_0_);
          spv::Id r0_ptr = builder_->createAccessChain(spv::StorageClassFunction,
                                                       var_main_registers_, id_vector_temp_);
          id_vector_temp_.clear();
          id_vector_temp_.push_back(patch_index_float);
          id_vector_temp_.push_back(
              builder_->createCompositeExtract(tess_coord_xy, type_float_, 0));
          id_vector_temp_.push_back(
              builder_->createCompositeExtract(tess_coord_xy, type_float_, 1));
          id_vector_temp_.push_back(const_float_1_);
          builder_->createStore(builder_->createCompositeConstruct(type_float4_, id_vector_temp_),
                                r0_ptr);

          if (register_count() >= 2) {
            id_vector_temp_.clear();
            id_vector_temp_.push_back(builder_->makeIntConstant(1));
            id_vector_temp_.push_back(const_int_0_);
            builder_->createStore(
                const_float_0_, builder_->createAccessChain(spv::StorageClassFunction,
                                                            var_main_registers_, id_vector_temp_));
          }
          break;
        }
        case Shader::HostVertexShaderType::kLineDomainCPIndexed:
        case Shader::HostVertexShaderType::kLineDomainPatchIndexed:

          REXGPU_ERROR(
              "SPIRV: Line domain tessellation not implemented for host type "
              "{}",
              static_cast<uint32_t>(host_type));
          assert_unhandled_case(host_type);
          break;
        default:
          break;
      }

      if (register_count() >= 2) {
        if (host_type == Shader::HostVertexShaderType::kTriangleDomainPatchIndexed) {
          id_vector_temp_.clear();
          id_vector_temp_.push_back(const_int_0_);
          spv::Id patch_index_float = builder_->createLoad(
              builder_->createAccessChain(spv::StorageClassInput, input_control_point_index_,
                                          id_vector_temp_),
              spv::NoPrecision);

          id_vector_temp_.clear();
          id_vector_temp_.push_back(builder_->makeIntConstant(1));
          id_vector_temp_.push_back(const_int_0_);
          builder_->createStore(patch_index_float,
                                builder_->createAccessChain(spv::StorageClassFunction,
                                                            var_main_registers_, id_vector_temp_));

          id_vector_temp_.clear();
          id_vector_temp_.push_back(builder_->makeIntConstant(1));
          id_vector_temp_.push_back(builder_->makeIntConstant(1));
          builder_->createStore(const_float_0_,
                                builder_->createAccessChain(spv::StorageClassFunction,
                                                            var_main_registers_, id_vector_temp_));
        } else if (host_type == Shader::HostVertexShaderType::kTriangleDomainCPIndexed) {
          for (uint32_t i = 0; i < 3; ++i) {
            id_vector_temp_.clear();
            id_vector_temp_.push_back(builder_->makeIntConstant(int(i)));
            spv::Id control_point_index = builder_->createLoad(
                builder_->createAccessChain(spv::StorageClassInput, input_control_point_index_,
                                            id_vector_temp_),
                spv::NoPrecision);
            id_vector_temp_.clear();
            id_vector_temp_.push_back(builder_->makeIntConstant(1));
            id_vector_temp_.push_back(builder_->makeIntConstant(int(i)));
            builder_->createStore(control_point_index, builder_->createAccessChain(
                                                           spv::StorageClassFunction,
                                                           var_main_registers_, id_vector_temp_));
          }
        }
      }
    } else if (IsSpirvVertexShader()) {
      spv::Id vertex_index = builder_->createUnaryOp(
          spv::OpBitcast, type_uint_, builder_->createLoad(input_vertex_index_, spv::NoPrecision));
      id_vector_temp_.clear();
      id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantVertexIndexCount));
      spv::Id vertex_index_count = builder_->createLoad(
          builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                      id_vector_temp_),
          spv::NoPrecision);
      if (main_vertex_rect_list_as_triangle_strip_) {
      } else if (shader_modification.vertex.host_vertex_shader_type ==
                 Shader::HostVertexShaderType::kPointListAsTriangleStrip) {
        spv::Id const_uint_2 = builder_->makeUintConstant(2);
        vertex_index =
            builder_->createBinOp(spv::OpShiftRightLogical, type_uint_, vertex_index, const_uint_2);
        spv::Id vertex_index_in_bounds =
            builder_->createBinOp(spv::OpULessThan, type_bool_, vertex_index, vertex_index_count);

        spv::Id load_vertex_index = builder_->createBinOp(
            spv::OpINotEqual, type_bool_,
            builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
                                  builder_->makeUintConstant(static_cast<unsigned int>(
                                      kSysFlag_ComputeOrPrimitiveVertexIndexLoad))),
            const_uint_0_);
        spv::Id load_vertex_index_safe = builder_->createBinOp(
            spv::OpLogicalAnd, type_bool_, load_vertex_index, vertex_index_in_bounds);
        SpirvBuilder::IfBuilder load_vertex_index_if(
            load_vertex_index_safe, spv::SelectionControlDontFlattenMask, *builder_);
        spv::Id loaded_vertex_index;
        {
          spv::Id vertex_index_is_32bit = builder_->createBinOp(
              spv::OpINotEqual, type_bool_,
              builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
                                    builder_->makeUintConstant(static_cast<unsigned int>(
                                        kSysFlag_ComputeOrPrimitiveVertexIndexLoad32Bit))),
              const_uint_0_);

          id_vector_temp_.clear();
          id_vector_temp_.push_back(
              builder_->makeIntConstant(kSystemConstantVertexIndexLoadAddress));
          spv::Id vertex_index_address = builder_->createBinOp(
              spv::OpIAdd, type_uint_,
              builder_->createLoad(
                  builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                              id_vector_temp_),
                  spv::NoPrecision),
              builder_->createBinOp(
                  spv::OpShiftLeftLogical, type_uint_, vertex_index,
                  builder_->createTriOp(spv::OpSelect, type_uint_, vertex_index_is_32bit,
                                        const_uint_2, builder_->makeUintConstant(1))));

          loaded_vertex_index = LoadUint32FromSharedMemory(
              builder_->createUnaryOp(spv::OpBitcast, type_int_,
                                      builder_->createBinOp(spv::OpShiftRightLogical, type_uint_,
                                                            vertex_index_address, const_uint_2)));

          loaded_vertex_index = builder_->createTriOp(
              spv::OpSelect, type_uint_, vertex_index_is_32bit, loaded_vertex_index,
              builder_->createTriOp(
                  spv::OpBitFieldUExtract, type_uint_, loaded_vertex_index,
                  builder_->createBinOp(spv::OpShiftLeftLogical, type_uint_,
                                        builder_->createBinOp(spv::OpBitwiseAnd, type_uint_,
                                                              vertex_index_address, const_uint_2),
                                        builder_->makeUintConstant(4 - 1)),
                  builder_->makeUintConstant(16)));

          id_vector_temp_.clear();
          id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantVertexIndexEndian));
          loaded_vertex_index = EndianSwap32Uint(
              loaded_vertex_index,
              builder_->createLoad(
                  builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                              id_vector_temp_),
                  spv::NoPrecision));
        }
        load_vertex_index_if.makeEndIf();

        vertex_index = load_vertex_index_if.createMergePhi(loaded_vertex_index, vertex_index);
        vertex_index = builder_->createTriOp(spv::OpSelect, type_uint_, vertex_index_in_bounds,
                                             vertex_index, const_uint_0_);
      } else {
        if (!features_.full_draw_index_uint32) {
          spv::Id vertex_index_in_bounds =
              builder_->createBinOp(spv::OpULessThan, type_bool_, vertex_index, vertex_index_count);

          spv::Id load_vertex_index = builder_->createBinOp(
              spv::OpINotEqual, type_bool_,
              builder_->createBinOp(
                  spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
                  builder_->makeUintConstant(static_cast<unsigned int>(kSysFlag_VertexIndexLoad))),
              const_uint_0_);
          spv::Id load_vertex_index_safe = builder_->createBinOp(
              spv::OpLogicalAnd, type_bool_, load_vertex_index, vertex_index_in_bounds);
          SpirvBuilder::IfBuilder load_vertex_index_if(
              load_vertex_index_safe, spv::SelectionControlDontFlattenMask, *builder_);
          spv::Id loaded_vertex_index;
          {
            id_vector_temp_.clear();
            id_vector_temp_.push_back(
                builder_->makeIntConstant(kSystemConstantVertexIndexLoadAddress));
            loaded_vertex_index = LoadUint32FromSharedMemory(builder_->createUnaryOp(
                spv::OpBitcast, type_int_,
                builder_->createBinOp(
                    spv::OpIAdd, type_uint_,
                    builder_->createBinOp(
                        spv::OpShiftRightLogical, type_uint_,
                        builder_->createLoad(
                            builder_->createAccessChain(spv::StorageClassUniform,
                                                        uniform_system_constants_, id_vector_temp_),
                            spv::NoPrecision),
                        builder_->makeUintConstant(2)),
                    vertex_index)));
          }
          load_vertex_index_if.makeEndIf();

          vertex_index = load_vertex_index_if.createMergePhi(loaded_vertex_index, vertex_index);

          spv::Id vertex_index_clamped = builder_->createTriOp(
              spv::OpSelect, type_uint_, vertex_index_in_bounds, vertex_index, const_uint_0_);
          vertex_index = builder_->createTriOp(spv::OpSelect, type_uint_, load_vertex_index,
                                               vertex_index_clamped, vertex_index);
        }

        id_vector_temp_.clear();
        id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantVertexIndexEndian));
        vertex_index = EndianSwap32Uint(
            vertex_index, builder_->createLoad(builder_->createAccessChain(
                                                   spv::StorageClassUniform,
                                                   uniform_system_constants_, id_vector_temp_),
                                               spv::NoPrecision));
      }
      if (!main_vertex_rect_list_as_triangle_strip_) {
        vertex_index = builder_->createUnaryOp(spv::OpBitcast, type_int_, vertex_index);

        id_vector_temp_.clear();
        id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantVertexBaseIndex));
        vertex_index = builder_->createBinOp(
            spv::OpIAdd, type_int_, vertex_index,
            builder_->createLoad(
                builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                            id_vector_temp_),
                spv::NoPrecision));
        WriteVertexIndexToRegister0(vertex_index);
      }
    }
  }
}

void SpirvShaderTranslator::CompleteVertexOrTessEvalShaderInMain() {
  Modification shader_modification = GetSpirvShaderModification();

  id_vector_temp_.clear();
  id_vector_temp_.push_back(builder_->makeIntConstant(kOutputPerVertexMemberPosition));
  spv::Id position_ptr =
      builder_->createAccessChain(spv::StorageClassOutput, output_per_vertex_, id_vector_temp_);
  if (main_vertex_rect_list_as_triangle_strip_) {
    assert_true(var_main_rect_list_strip_vertex_ != spv::NoResult);
    assert_true(var_main_rect_list_guest_positions_ != spv::NoResult);

    auto load_rect_list_position = [&](spv::Id index) {
      id_vector_temp_.clear();
      id_vector_temp_.push_back(index);
      return builder_->createLoad(
          builder_->createAccessChain(spv::StorageClassFunction,
                                      var_main_rect_list_guest_positions_, id_vector_temp_),
          spv::NoPrecision);
    };

    spv::Id rect_strip_vertex =
        builder_->createLoad(var_main_rect_list_strip_vertex_, spv::NoPrecision);
    spv::Id rect_positions[3] = {
        load_rect_list_position(builder_->makeIntConstant(0)),
        load_rect_list_position(builder_->makeIntConstant(1)),
        load_rect_list_position(builder_->makeIntConstant(2)),
    };
    spv::Id rect_positions_have_nan = builder_->makeBoolConstant(false);
    for (uint32_t i = 0; i < 3; ++i) {
      rect_positions_have_nan = builder_->createBinOp(
          spv::OpLogicalOr, type_bool_, rect_positions_have_nan,
          builder_->createUnaryOp(
              spv::OpAny, type_bool_,
              builder_->createUnaryOp(spv::OpIsNan, type_bool4_, rect_positions[i])));
    }

    spv::Id is_w_not_reciprocal = builder_->createBinOp(
        spv::OpINotEqual, type_bool_,
        builder_->createBinOp(
            spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
            builder_->makeUintConstant(static_cast<unsigned int>(kSysFlag_WNotReciprocal))),
        const_uint_0_);
    spv::Id is_xy_divided_by_w = builder_->createBinOp(
        spv::OpINotEqual, type_bool_,
        builder_->createBinOp(
            spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
            builder_->makeUintConstant(static_cast<unsigned int>(kSysFlag_XYDividedByW))),
        const_uint_0_);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantNdcScale));
    spv::Id ndc_scale = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                    id_vector_temp_),
        spv::NoPrecision);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantNdcOffset));
    spv::Id ndc_offset = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                    id_vector_temp_),
        spv::NoPrecision);
    uint_vector_temp_.clear();
    uint_vector_temp_.push_back(0);
    uint_vector_temp_.push_back(1);
    spv::Id ndc_scale_xy =
        builder_->createRvalueSwizzle(spv::NoPrecision, type_float2_, ndc_scale, uint_vector_temp_);
    spv::Id ndc_offset_xy = builder_->createRvalueSwizzle(spv::NoPrecision, type_float2_,
                                                          ndc_offset, uint_vector_temp_);
    spv::Id rect_positions_xy_converted[3];
    for (uint32_t i = 0; i < 3; ++i) {
      spv::Id rect_position_w_raw =
          builder_->createCompositeExtract(rect_positions[i], type_float_, 3);
      spv::Id rect_position_w = builder_->createTriOp(
          spv::OpSelect, type_float_, is_w_not_reciprocal, rect_position_w_raw,
          builder_->createNoContractionBinOp(spv::OpFDiv, type_float_, const_float_1_,
                                             rect_position_w_raw));
      spv::Id rect_position_xy = builder_->createRvalueSwizzle(
          spv::NoPrecision, type_float2_, rect_positions[i], uint_vector_temp_);
      rect_position_xy = builder_->createTriOp(
          spv::OpSelect, type_float2_,
          builder_->smearScalar(spv::NoPrecision, is_xy_divided_by_w, type_bool2_),
          builder_->createNoContractionBinOp(spv::OpVectorTimesScalar, type_float2_,
                                             rect_position_xy, rect_position_w),
          rect_position_xy);
      rect_positions_xy_converted[i] = builder_->createNoContractionBinOp(
          spv::OpFAdd, type_float2_,
          builder_->createNoContractionBinOp(spv::OpFMul, type_float2_, rect_position_xy,
                                             ndc_scale_xy),
          builder_->createNoContractionBinOp(spv::OpVectorTimesScalar, type_float2_, ndc_offset_xy,
                                             rect_position_w));
    }

    spv::Id edge_lengths[3];
    for (uint32_t i = 0; i < 3; ++i) {
      spv::Id edge_0_xy = rect_positions_xy_converted[(1 + i) % 3];
      spv::Id edge_1_xy = rect_positions_xy_converted[(2 + i) % 3];
      spv::Id edge_xy = builder_->createBinOp(spv::OpFSub, type_float2_, edge_1_xy, edge_0_xy);
      edge_lengths[i] = builder_->createBinOp(spv::OpDot, type_float_, edge_xy, edge_xy);
    }

    spv::Id const_int_1 = builder_->makeIntConstant(1);
    spv::Id const_int_2 = builder_->makeIntConstant(2);
    spv::Id const_int_3 = builder_->makeIntConstant(3);
    spv::Id vertex_indices[3];
    vertex_indices[0] = builder_->createTriOp(
        spv::OpSelect, type_int_,
        builder_->createBinOp(spv::OpLogicalAnd, type_bool_,
                              builder_->createBinOp(spv::OpFOrdGreaterThan, type_bool_,
                                                    edge_lengths[0], edge_lengths[1]),
                              builder_->createBinOp(spv::OpFOrdGreaterThan, type_bool_,
                                                    edge_lengths[0], edge_lengths[2])),
        const_int_0_,
        builder_->createTriOp(spv::OpSelect, type_int_,
                              builder_->createBinOp(spv::OpFOrdGreaterThan, type_bool_,
                                                    edge_lengths[1], edge_lengths[2]),
                              const_int_1, const_int_2));
    for (uint32_t i = 1; i < 3; ++i) {
      spv::Id vertex_index_without_wrapping = builder_->createBinOp(
          spv::OpIAdd, type_int_, vertex_indices[0], builder_->makeIntConstant(int32_t(i)));
      vertex_indices[i] =
          builder_->createTriOp(spv::OpSelect, type_int_,
                                builder_->createBinOp(spv::OpSLessThan, type_bool_,
                                                      vertex_index_without_wrapping, const_int_3),
                                vertex_index_without_wrapping,
                                builder_->createBinOp(spv::OpISub, type_int_,
                                                      vertex_index_without_wrapping, const_int_3));
    }

    auto select_rect_list_value = [&](spv::Id value_0, spv::Id value_1, spv::Id value_2,
                                      spv::Id value_3, spv::Id value_type) {
      spv::Id value = builder_->createTriOp(
          spv::OpSelect, value_type,
          builder_->smearScalar(
              spv::NoPrecision,
              builder_->createBinOp(spv::OpIEqual, type_bool_, rect_strip_vertex, const_uint_0_),
              type_bool_vectors_[builder_->getNumTypeComponents(value_type) - 1]),
          value_0,
          builder_->createTriOp(
              spv::OpSelect, value_type,
              builder_->smearScalar(
                  spv::NoPrecision,
                  builder_->createBinOp(spv::OpIEqual, type_bool_, rect_strip_vertex,
                                        builder_->makeUintConstant(1)),
                  type_bool_vectors_[builder_->getNumTypeComponents(value_type) - 1]),
              value_1, value_2));
      return builder_->createTriOp(
          spv::OpSelect, value_type,
          builder_->smearScalar(spv::NoPrecision,
                                builder_->createBinOp(spv::OpIEqual, type_bool_, rect_strip_vertex,
                                                      builder_->makeUintConstant(3)),
                                type_bool_vectors_[builder_->getNumTypeComponents(value_type) - 1]),
          value_3, value);
    };

    auto load_rect_list_interpolator = [&](spv::Id interpolator_array, spv::Id index) {
      id_vector_temp_.clear();
      id_vector_temp_.push_back(index);
      return builder_->createLoad(builder_->createAccessChain(spv::StorageClassFunction,
                                                              interpolator_array, id_vector_temp_),
                                  spv::NoPrecision);
    };

    spv::Id position_v0 = load_rect_list_position(vertex_indices[0]);
    spv::Id position_v1 = load_rect_list_position(vertex_indices[1]);
    spv::Id position_v2 = load_rect_list_position(vertex_indices[2]);
    spv::Id position_v3 = builder_->createNoContractionBinOp(
        spv::OpFAdd, type_float4_,
        builder_->createNoContractionBinOp(spv::OpFSub, type_float4_, position_v1, position_v0),
        position_v2);
    spv::Id position_final =
        select_rect_list_value(position_v0, position_v1, position_v2, position_v3, type_float4_);
    position_final = builder_->createTriOp(
        spv::OpSelect, type_float4_,
        builder_->smearScalar(spv::NoPrecision, rect_positions_have_nan, type_bool4_),
        builder_->smearScalar(spv::NoPrecision,
                              builder_->createNoContractionBinOp(spv::OpFDiv, type_float_,
                                                                 const_float_0_, const_float_0_),
                              type_float4_),
        position_final);
    builder_->createStore(position_final, position_ptr);

    uint32_t interpolators_remaining = GetModificationInterpolatorMask();
    uint32_t interpolator_index;
    while (rex::bit_scan_forward(interpolators_remaining, &interpolator_index)) {
      interpolators_remaining &= ~(UINT32_C(1) << interpolator_index);
      spv::Id rect_list_interpolator_array =
          var_main_rect_list_guest_interpolators_[interpolator_index];
      assert_true(rect_list_interpolator_array != spv::NoResult);
      spv::Id interpolator_v0 =
          load_rect_list_interpolator(rect_list_interpolator_array, vertex_indices[0]);
      spv::Id interpolator_v1 =
          load_rect_list_interpolator(rect_list_interpolator_array, vertex_indices[1]);
      spv::Id interpolator_v2 =
          load_rect_list_interpolator(rect_list_interpolator_array, vertex_indices[2]);
      spv::Id interpolator_v3 = builder_->createNoContractionBinOp(
          spv::OpFAdd, type_float4_,
          builder_->createNoContractionBinOp(spv::OpFSub, type_float4_, interpolator_v1,
                                             interpolator_v0),
          interpolator_v2);
      builder_->createStore(select_rect_list_value(interpolator_v0, interpolator_v1,
                                                   interpolator_v2, interpolator_v3, type_float4_),
                            input_output_interpolators_[interpolator_index]);
    }
  }
  spv::Id guest_position = builder_->createLoad(position_ptr, spv::NoPrecision);

  spv::Id position_w = builder_->createCompositeExtract(guest_position, type_float_, 3);
  spv::Id is_w_not_reciprocal = builder_->createBinOp(
      spv::OpINotEqual, type_bool_,
      builder_->createBinOp(
          spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
          builder_->makeUintConstant(static_cast<unsigned int>(kSysFlag_WNotReciprocal))),
      const_uint_0_);
  spv::Id guest_position_w_inv =
      builder_->createNoContractionBinOp(spv::OpFDiv, type_float_, const_float_1_, position_w);
  position_w = builder_->createTriOp(spv::OpSelect, type_float_, is_w_not_reciprocal, position_w,
                                     guest_position_w_inv);

  spv::Id position_xyz;

  {
    uint_vector_temp_.clear();
    uint_vector_temp_.push_back(0);
    uint_vector_temp_.push_back(1);
    spv::Id position_xy = builder_->createRvalueSwizzle(spv::NoPrecision, type_float2_,
                                                        guest_position, uint_vector_temp_);
    spv::Id is_xy_divided_by_w = builder_->createBinOp(
        spv::OpINotEqual, type_bool_,
        builder_->createBinOp(
            spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
            builder_->makeUintConstant(static_cast<unsigned int>(kSysFlag_XYDividedByW))),
        const_uint_0_);
    spv::Id guest_position_xy_mul_w = builder_->createNoContractionBinOp(
        spv::OpVectorTimesScalar, type_float2_, position_xy, position_w);
    position_xy = builder_->createTriOp(
        spv::OpSelect, type_float2_,
        builder_->smearScalar(spv::NoPrecision, is_xy_divided_by_w, type_bool2_),
        guest_position_xy_mul_w, position_xy);

    spv::Id position_z = builder_->createCompositeExtract(guest_position, type_float_, 2);
    spv::Id is_z_divided_by_w = builder_->createBinOp(
        spv::OpINotEqual, type_bool_,
        builder_->createBinOp(
            spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
            builder_->makeUintConstant(static_cast<unsigned int>(kSysFlag_ZDividedByW))),
        const_uint_0_);
    spv::Id guest_position_z_mul_w =
        builder_->createNoContractionBinOp(spv::OpFMul, type_float_, position_z, position_w);
    position_z = builder_->createTriOp(spv::OpSelect, type_float_, is_z_divided_by_w,
                                       guest_position_z_mul_w, position_z);

    {
      std::unique_ptr<spv::Instruction> composite_construct_op = std::make_unique<spv::Instruction>(
          builder_->getUniqueId(), type_float3_, spv::OpCompositeConstruct);
      composite_construct_op->addIdOperand(position_xy);
      composite_construct_op->addIdOperand(position_z);
      position_xyz = composite_construct_op->getResultId();
      builder_->getBuildPoint()->addInstruction(std::move(composite_construct_op));
    }
  }

  uint32_t user_clip_plane_count = shader_modification.vertex.user_clip_plane_count;
  if (user_clip_plane_count > 0) {
    spv::Id clip_space_position;
    {
      std::unique_ptr<spv::Instruction> composite_construct_op = std::make_unique<spv::Instruction>(
          builder_->getUniqueId(), type_float4_, spv::OpCompositeConstruct);
      composite_construct_op->addIdOperand(position_xyz);
      composite_construct_op->addIdOperand(position_w);
      clip_space_position = composite_construct_op->getResultId();
      builder_->getBuildPoint()->addInstruction(std::move(composite_construct_op));
    }

    bool user_clip_plane_cull = shader_modification.vertex.user_clip_plane_cull;
    unsigned int clip_cull_distance_member_index =
        user_clip_plane_cull ? output_per_vertex_cull_distance_member_index_
                             : output_per_vertex_clip_distance_member_index_;

    for (uint32_t i = 0; i < user_clip_plane_count; ++i) {
      id_vector_temp_.clear();
      id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantUserClipPlanes));
      id_vector_temp_.push_back(builder_->makeIntConstant(int(i)));
      spv::Id clip_plane = builder_->createLoad(
          builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                      id_vector_temp_),
          spv::NoPrecision);

      spv::Id distance =
          builder_->createBinOp(spv::OpDot, type_float_, clip_space_position, clip_plane);

      id_vector_temp_.clear();
      id_vector_temp_.push_back(builder_->makeIntConstant(clip_cull_distance_member_index));
      id_vector_temp_.push_back(builder_->makeIntConstant(int(i)));
      spv::Id distance_ptr =
          builder_->createAccessChain(spv::StorageClassOutput, output_per_vertex_, id_vector_temp_);
      builder_->createStore(distance, distance_ptr);
    }
  }

  id_vector_temp_.clear();
  id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantNdcScale));
  spv::Id ndc_scale =
      builder_->createLoad(builder_->createAccessChain(spv::StorageClassUniform,
                                                       uniform_system_constants_, id_vector_temp_),
                           spv::NoPrecision);
  position_xyz =
      builder_->createNoContractionBinOp(spv::OpFMul, type_float3_, position_xyz, ndc_scale);
  id_vector_temp_.clear();
  id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantNdcOffset));
  spv::Id ndc_offset =
      builder_->createLoad(builder_->createAccessChain(spv::StorageClassUniform,
                                                       uniform_system_constants_, id_vector_temp_),
                           spv::NoPrecision);
  spv::Id ndc_offset_mul_w = builder_->createNoContractionBinOp(
      spv::OpVectorTimesScalar, type_float3_, ndc_offset, position_w);
  position_xyz =
      builder_->createNoContractionBinOp(spv::OpFAdd, type_float3_, position_xyz, ndc_offset_mul_w);

  if (current_shader().writes_point_size_edge_flag_kill_vertex() & 0b100) {
    assert_true(var_main_point_size_edge_flag_kill_vertex_ != spv::NoResult);
    id_vector_temp_.clear();

    id_vector_temp_.push_back(builder_->makeIntConstant(2));
    spv::Id kill_value = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassFunction,
                                    var_main_point_size_edge_flag_kill_vertex_, id_vector_temp_),
        spv::NoPrecision);

    spv::Id vertex_killed = builder_->createBinOp(
        spv::OpINotEqual, type_bool_,
        builder_->createBinOp(spv::OpBitwiseAnd, type_uint_,
                              builder_->createUnaryOp(spv::OpBitcast, type_uint_, kill_value),
                              builder_->makeUintConstant(UINT32_C(0x7FFFFFFF))),
        const_uint_0_);
    if (shader_modification.vertex.vertex_kill_and) {
      uint32_t vertex_kill_cull_distance_index =
          shader_modification.vertex.user_clip_plane_cull ? user_clip_plane_count : 0;
      id_vector_temp_.clear();
      id_vector_temp_.push_back(
          builder_->makeIntConstant(int(output_per_vertex_cull_distance_member_index_)));
      id_vector_temp_.push_back(builder_->makeIntConstant(int(vertex_kill_cull_distance_index)));
      builder_->createStore(
          builder_->createTriOp(spv::OpSelect, type_float_, vertex_killed,
                                builder_->makeFloatConstant(-1.0f), const_float_0_),
          builder_->createAccessChain(spv::StorageClassOutput, output_per_vertex_,
                                      id_vector_temp_));
    } else {
      position_w = builder_->createTriOp(
          spv::OpSelect, type_float_, vertex_killed,
          builder_->createUnaryOp(spv::OpBitcast, type_float_,
                                  builder_->makeUintConstant(UINT32_C(0x7FC00000))),
          position_w);
    }
  }

  if (output_point_size_ != spv::NoResult) {
    spv::Id point_size;
    if (current_shader().writes_point_size_edge_flag_kill_vertex() & 0b001) {
      assert_true(var_main_point_size_edge_flag_kill_vertex_ != spv::NoResult);
      id_vector_temp_.clear();

      id_vector_temp_.push_back(const_int_0_);
      point_size = builder_->createLoad(
          builder_->createAccessChain(spv::StorageClassFunction,
                                      var_main_point_size_edge_flag_kill_vertex_, id_vector_temp_),
          spv::NoPrecision);
    } else {
      point_size = builder_->makeFloatConstant(-1.0f);
    }
    builder_->createStore(point_size, output_point_size_);
  }

  if (shader_modification.vertex.host_vertex_shader_type ==
      Shader::HostVertexShaderType::kPointListAsTriangleStrip) {
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeUintConstant(0b10));
    id_vector_temp_.push_back(builder_->makeUintConstant(0b01));
    spv::Id point_vertex_positive = builder_->createBinOp(
        spv::OpINotEqual, type_bool2_,
        builder_->createBinOp(
            spv::OpBitwiseAnd, type_uint2_,
            builder_->smearScalar(spv::NoPrecision,
                                  builder_->createUnaryOp(
                                      spv::OpBitcast, type_uint_,
                                      builder_->createLoad(input_vertex_index_, spv::NoPrecision)),
                                  type_uint2_),
            builder_->createCompositeConstruct(type_uint2_, id_vector_temp_)),
        SpirvSmearScalarResultOrConstant(const_uint_0_, type_uint2_));

    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantPointConstantDiameter));
    spv::Id point_guest_diameter = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                    id_vector_temp_),
        spv::NoPrecision);
    if (current_shader().writes_point_size_edge_flag_kill_vertex() & 0b001) {
      assert_true(var_main_point_size_edge_flag_kill_vertex_ != spv::NoResult);
      id_vector_temp_.clear();
      id_vector_temp_.push_back(const_int_0_);
      spv::Id point_vertex_diameter = builder_->createLoad(
          builder_->createAccessChain(spv::StorageClassFunction,
                                      var_main_point_size_edge_flag_kill_vertex_, id_vector_temp_),
          spv::NoPrecision);

      point_guest_diameter = builder_->createTriOp(
          spv::OpSelect, type_float2_,
          builder_->smearScalar(spv::NoPrecision,
                                builder_->createBinOp(spv::OpFOrdGreaterThanEqual, type_bool_,
                                                      point_vertex_diameter, const_float_0_),
                                type_bool2_),
          builder_->smearScalar(spv::NoPrecision, point_vertex_diameter, type_float2_),
          point_guest_diameter);
    }

    id_vector_temp_.clear();
    id_vector_temp_.push_back(
        builder_->makeIntConstant(kSystemConstantPointScreenDiameterToNdcRadius));
    spv::Id point_radius = builder_->createNoContractionBinOp(
        spv::OpFMul, type_float2_, point_guest_diameter,
        builder_->createLoad(
            builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                        id_vector_temp_),
            spv::NoPrecision));

    point_radius = builder_->createNoContractionBinOp(spv::OpVectorTimesScalar, type_float2_,
                                                      point_radius, position_w);

    uint_vector_temp_.clear();
    uint_vector_temp_.push_back(0);
    uint_vector_temp_.push_back(1);
    spv::Id point_position_xy = builder_->createNoContractionBinOp(
        spv::OpFAdd, type_float2_,
        builder_->createRvalueSwizzle(spv::NoPrecision, type_float2_, position_xyz,
                                      uint_vector_temp_),
        builder_->createTriOp(
            spv::OpSelect, type_float2_, point_vertex_positive, point_radius,
            builder_->createNoContractionUnaryOp(spv::OpFNegate, type_float2_, point_radius)));

    spv::Id position;
    {
      std::unique_ptr<spv::Instruction> composite_construct_op = std::make_unique<spv::Instruction>(
          builder_->getUniqueId(), type_float4_, spv::OpCompositeConstruct);
      composite_construct_op->addIdOperand(point_position_xy);
      composite_construct_op->addIdOperand(
          builder_->createCompositeExtract(position_xyz, type_float_, 2));
      composite_construct_op->addIdOperand(position_w);
      position = composite_construct_op->getResultId();
      builder_->getBuildPoint()->addInstruction(std::move(composite_construct_op));
    }
    builder_->createStore(position, position_ptr);

    if (output_point_coordinates_ != spv::NoResult) {
      builder_->createStore(
          builder_->createTriOp(spv::OpSelect, type_float2_, point_vertex_positive, const_float2_1_,
                                const_float2_0_),
          output_point_coordinates_);
    }

  } else {
    spv::Id position;
    {
      std::unique_ptr<spv::Instruction> composite_construct_op = std::make_unique<spv::Instruction>(
          builder_->getUniqueId(), type_float4_, spv::OpCompositeConstruct);
      composite_construct_op->addIdOperand(position_xyz);
      composite_construct_op->addIdOperand(position_w);
      position = composite_construct_op->getResultId();
      builder_->getBuildPoint()->addInstruction(std::move(composite_construct_op));
    }
    builder_->createStore(position, position_ptr);
  }
}

}
