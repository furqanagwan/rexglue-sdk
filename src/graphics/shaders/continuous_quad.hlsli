#include "xenos_draw.hlsli"

struct XeHSConstantDataOutput {
  float edges[4] : SV_TessFactor;
  float inside[2] : SV_InsideTessFactor;
};

XeHSConstantDataOutput XePatchConstant() {
  XeHSConstantDataOutput output = (XeHSConstantDataOutput)0;
  uint i;








  [unroll] for (i = 0u; i < 4u; ++i) {
    output.edges[i] = xe_tessellation_factor_range.y;
  }




  [unroll] for (i = 0u; i < 2u; ++i) {
    output.inside[i] = xe_tessellation_factor_range.y;
  }

  return output;
}

[domain("quad")]
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
