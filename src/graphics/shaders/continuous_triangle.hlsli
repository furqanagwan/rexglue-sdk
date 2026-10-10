#include "xenos_draw.hlsli"

struct XeHSConstantDataOutput {
  float edges[3] : SV_TessFactor;
  float inside : SV_InsideTessFactor;
};

XeHSConstantDataOutput XePatchConstant() {
  XeHSConstantDataOutput output = (XeHSConstantDataOutput)0;
  uint i;








  [unroll] for (i = 0u; i < 3u; ++i) {
    output.edges[i] = xe_tessellation_factor_range.y;
  }

  output.inside = xe_tessellation_factor_range.y;

  return output;
}

[domain("tri")]
[partitioning("fractional_even")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(XE_TESSELLATION_CONTROL_POINT_COUNT)]
[patchconstantfunc("XePatchConstant")]
XeHSControlPointOutput main(
    InputPatch<XeHSControlPointInputIndexed,
               XE_TESSELLATION_CONTROL_POINT_COUNT> xe_input_patch,
    uint xe_control_point_id : SV_OutputControlPointID) {
  XeHSControlPointOutput output;
  output.index = xe_input_patch[xe_control_point_id].index;
  return output;
}
