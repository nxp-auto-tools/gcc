#include <arm_neon.h>

int16x8x3_t
f_vld3q_lane_s16 (int16_t * p, int16x8x3_t v)
{
  int16x8x3_t res;
  res = vld3q_lane_s16 (p, v, 8); /* { dg-error "lane 8 out of range 0 - 7" "" { target *-*-* } 0 } */
  res = vld3q_lane_s16 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 7" "" { target *-*-* } 0 } */
  return res;
}
