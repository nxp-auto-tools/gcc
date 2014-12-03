#include <arm_neon.h>


void
f_vst2_lane_u16 (uint16_t * p, uint16x4x2_t v)
{
  vst2_lane_u16 (p, v, 4); /* { dg-error "lane 4 out of range 0 - 3" "" { target *-*-* } 0 } */
  vst2_lane_u16 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 3" "" { target *-*-* } 0 } */
  return;
}
