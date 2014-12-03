#include <arm_neon.h>

uint8x8x3_t
f_vld3_lane_u8 (uint8_t * p, uint8x8x3_t v)
{
  uint8x8x3_t res;
  res = vld3_lane_u8 (p, v, 8); /* { dg-error "lane 8 out of range 0 - 7" "" { target *-*-* } 0 } */
  res = vld3_lane_u8 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 7" "" { target *-*-* } 0 } */
  return res;
}
