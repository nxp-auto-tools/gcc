#include <arm_neon.h>

uint16x4x3_t
f_vld3_lane_u16 (uint16_t * p, uint16x4x3_t v)
{
  uint16x4x3_t res;
  res = vld3_lane_u16 (p, v, 4); /* { dg-error "lane 4 out of range 0 - 3" "" { target *-*-* } 0 } */
  res = vld3_lane_u16 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 3" "" { target *-*-* } 0 } */
  return res;
}
