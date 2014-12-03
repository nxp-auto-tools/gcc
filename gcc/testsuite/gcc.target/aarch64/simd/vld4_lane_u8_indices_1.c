#include <arm_neon.h>

uint8x8x4_t
f_vld4_lane_u8 (uint8_t * p, uint8x8x4_t v)
{
  uint8x8x4_t res;
  res = vld4_lane_u8 (p, v, 8); /* { dg-error "lane 8 out of range 0 - 7" "" { target *-*-* } 0 } */
  res = vld4_lane_u8 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 7" "" { target *-*-* } 0 } */
  return res;
}
