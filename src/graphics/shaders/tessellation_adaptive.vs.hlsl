#include "endian.xesli"
#include "xenos_draw.hlsli"

XeHSControlPointInputAdaptive main(uint xe_edge_factor : SV_VertexID) {
  XeHSControlPointInputAdaptive output;







  output.edge_factor = clamp(
      asfloat(XeEndianSwap32(xe_edge_factor, xe_vertex_index_endian)) + 1.0f,
      xe_tessellation_factor_range.x, xe_tessellation_factor_range.y);
  return output;
}
