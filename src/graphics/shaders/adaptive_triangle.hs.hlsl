#include "xenos_draw.hlsli"

struct XeHSConstantDataOutput {
  float edges[3] : SV_TessFactor;
  float inside : SV_InsideTessFactor;
};

XeHSConstantDataOutput XePatchConstant(
    InputPatch<XeHSControlPointInputAdaptive, 3> xe_input_patch) {
  XeHSConstantDataOutput output = (XeHSConstantDataOutput)0;
  uint i;




























  [unroll] for (i = 0u; i < 3u; ++i) {
    output.edges[i] = xe_input_patch[(i + 1u) % 3u].edge_factor;
  }


  output.inside =
      min(min(output.edges[0u], output.edges[1u]), output.edges[2u]);

  return output;
}

[domain("tri")]
[partitioning("fractional_even")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(1)]
[patchconstantfunc("XePatchConstant")]
XeHSControlPointOutput main(
    InputPatch<XeHSControlPointInputAdaptive, 3> xe_input_patch,
    uint xe_primitive_id : SV_PrimitiveID) {
  XeHSControlPointOutput output;



  output.index =
      float(clamp((xe_primitive_id + xe_vertex_index_offset) & 0xFFFFFFu,
                  xe_vertex_index_min_max.x, xe_vertex_index_min_max.y));
  return output;
}
