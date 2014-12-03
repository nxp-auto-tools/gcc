#include <arm_neon.h>

int8x8x4_t
f_vld4_lane_s8 (int8_t * p, int8x8x4_t v)
{
  int8x8x4_t res;
  res = vld4_lane_s8 (p, v, 8); /* { dg-error "lane 8 out of range 0 - 7" "" { target *-*-* } 0 } */
  res = vld4_lane_s8 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 7" "" { target *-*-* } 0 } */
  return res;
}
