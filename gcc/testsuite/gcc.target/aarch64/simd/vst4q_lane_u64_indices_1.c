#include <arm_neon.h>


void
f_vst4q_lane_u64 (uint64_t * p, uint64x2x4_t v)
{
  vst4q_lane_u64 (p, v, 2); /* { dg-error "lane 2 out of range 0 - 1" "" { target *-*-* } 0 } */
  vst4q_lane_u64 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 1" "" { target *-*-* } 0 } */
  return;
}
