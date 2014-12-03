#include <arm_neon.h>


void
f_vst4_lane_u8 (uint8_t * p, uint8x8x4_t v)
{
  vst4_lane_u8 (p, v, 8); /* { dg-error "lane 8 out of range 0 - 7" "" { target *-*-* } 0 } */
  vst4_lane_u8 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 7" "" { target *-*-* } 0 } */
  return;
}
