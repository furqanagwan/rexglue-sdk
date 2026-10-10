#include "xenos_draw.hlsli"

struct XeHSConstantDataOutput {
  float edges[4] : SV_TessFactor;
  float inside[2] : SV_InsideTessFactor;
};

XeHSConstantDataOutput XePatchConstant(
    InputPatch<XeHSControlPointInputAdaptive, 4> xe_input_patch) {
  XeHSConstantDataOutput output = (XeHSConstantDataOutput)0;
  uint i;



















  [unroll] for (i = 0u; i < 4u; ++i) {
    output.edges[i] = xe_input_patch[(i + 3u) & 3u].edge_factor;
  }






  output.inside[0u] = min(output.edges[1u], output.edges[3u]);
  output.inside[1u] = min(output.edges[0u], output.edges[2u]);

  return output;
}

[domain("quad")]
[partitioning("fractional_even")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(1)]
[patchconstantfunc("XePatchConstant")]
XeHSControlPointOutput main(
    InputPatch<XeHSControlPointInputAdaptive, 4> xe_input_patch,
    uint xe_primitive_id : SV_PrimitiveID) {
  XeHSControlPointOutput output;



  output.index =
      float(clamp((xe_primitive_id + xe_vertex_index_offset) & 0xFFFFFFu,
                  xe_vertex_index_min_max.x, xe_vertex_index_min_max.y));
  return output;
}
