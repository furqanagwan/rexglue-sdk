#include "pixel_formats.xesli"
#include "xenos_draw.hlsli"

struct XePSInput {
  XeVertexPrePS pre_ps;
  sample float4 position : SV_Position;
};

precise float main(XePSInput xe_input) : SV_Depth {




  return asfloat(XeFloat20e4To32(
      XeFloat32To20e4(asuint(saturate(xe_input.position.z * 2.0f)), true),
      true));
}
