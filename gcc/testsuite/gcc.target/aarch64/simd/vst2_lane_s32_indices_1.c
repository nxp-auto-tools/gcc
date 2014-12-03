#include <arm_neon.h>


void
f_vst2_lane_s32 (int32_t * p, int32x2x2_t v)
{
  vst2_lane_s32 (p, v, 2); /* { dg-error "lane 2 out of range 0 - 1" "" { target *-*-* } 0 } */
  vst2_lane_s32 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 1" "" { target *-*-* } 0 } */
  return;
}
