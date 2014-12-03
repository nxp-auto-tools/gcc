#include <arm_neon.h>


void
f_vst3q_lane_s32 (int32_t * p, int32x4x3_t v)
{
  vst3q_lane_s32 (p, v, 4); /* { dg-error "lane 4 out of range 0 - 3" "" { target *-*-* } 0 } */
  vst3q_lane_s32 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 3" "" { target *-*-* } 0 } */
  return;
}
