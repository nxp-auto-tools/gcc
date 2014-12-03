#include <arm_neon.h>


void
f_vst4_lane_u16 (uint16_t * p, uint16x4x4_t v)
{
  vst4_lane_u16 (p, v, 4); /* { dg-error "lane 4 out of range 0 - 3" "" { target *-*-* } 0 } */
  vst4_lane_u16 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 3" "" { target *-*-* } 0 } */
  return;
}
