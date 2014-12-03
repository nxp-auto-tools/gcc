#include <arm_neon.h>


void
f_vst2q_lane_s8 (int8_t * p, int8x16x2_t v)
{
  vst2q_lane_s8 (p, v, 16); /* { dg-error "lane 16 out of range 0 - 15" "" { target *-*-* } 0 } */
  vst2q_lane_s8 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 15" "" { target *-*-* } 0 } */
  return;
}
