#include <arm_neon.h>

uint32x2x4_t
f_vld4_lane_u32 (uint32_t * p, uint32x2x4_t v)
{
  uint32x2x4_t res;
  res = vld4_lane_u32 (p, v, 2); /* { dg-error "lane 2 out of range 0 - 1" "" { target *-*-* } 0 } */
  res = vld4_lane_u32 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 1" "" { target *-*-* } 0 } */
  return res;
}
