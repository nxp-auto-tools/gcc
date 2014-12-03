#include <arm_neon.h>


void
f_vst2_lane_u64 (uint64_t * p, uint64x1x2_t v)
{
  vst2_lane_u64 (p, v, 1); /* { dg-error "lane 1 out of range 0 - 0" "" { target *-*-* } 0 } */
  vst2_lane_u64 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 0" "" { target *-*-* } 0 } */
  return;
}
