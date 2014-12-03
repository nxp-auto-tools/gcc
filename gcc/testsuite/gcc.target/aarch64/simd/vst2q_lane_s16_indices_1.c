#include <arm_neon.h>


void
f_vst2q_lane_s16 (int16_t * p, int16x8x2_t v)
{
  vst2q_lane_s16 (p, v, 8); /* { dg-error "lane 8 out of range 0 - 7" "" { target *-*-* } 0 } */
  vst2q_lane_s16 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 7" "" { target *-*-* } 0 } */
  return;
}
