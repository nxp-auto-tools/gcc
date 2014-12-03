#include <arm_neon.h>


void
f_vst2q_lane_u64 (uint64_t * p, uint64x2x2_t v)
{
  vst2q_lane_u64 (p, v, 2); /* { dg-error "lane 2 out of range 0 - 1" "" { target *-*-* } 0 } */
  vst2q_lane_u64 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 1" "" { target *-*-* } 0 } */
  return;
}
