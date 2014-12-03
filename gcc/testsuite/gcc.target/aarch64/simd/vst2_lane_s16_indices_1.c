#include <arm_neon.h>


void
f_vst2_lane_s16 (int16_t * p, int16x4x2_t v)
{
  vst2_lane_s16 (p, v, 4); /* { dg-error "lane 4 out of range 0 - 3" "" { target *-*-* } 0 } */
  vst2_lane_s16 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 3" "" { target *-*-* } 0 } */
  return;
}
