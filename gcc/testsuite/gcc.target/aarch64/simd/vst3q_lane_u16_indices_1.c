#include <arm_neon.h>


void
f_vst3q_lane_u16 (uint16_t * p, uint16x8x3_t v)
{
  vst3q_lane_u16 (p, v, 8); /* { dg-error "lane 8 out of range 0 - 7" "" { target *-*-* } 0 } */
  vst3q_lane_u16 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 7" "" { target *-*-* } 0 } */
  return;
}
