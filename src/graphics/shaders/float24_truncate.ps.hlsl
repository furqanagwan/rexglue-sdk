#include "pixel_formats.xesli"
#include "xenos_draw.hlsli"

struct XePSInput {
  XeVertexPrePS pre_ps;
  sample float4 position : SV_Position;
};

precise float main(XePSInput xe_input) : SV_DepthLessEqual {













  precise uint depth = asuint(saturate(xe_input.position.z * 2.0f));


  if (depth >= 0x2E800000u) {



    uint exponent = (depth >> 23u) & 0xFFu;



    uint shift = asuint(max(116 - asint(exponent), 3));
    depth = depth >> shift << shift;
  } else {

    depth = 0u;
  }
  return asfloat(depth) * 0.5f;
}
