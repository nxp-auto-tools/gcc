#include <arm_neon.h>

int8x16x4_t
f_vld4q_lane_s8 (int8_t * p, int8x16x4_t v)
{
  int8x16x4_t res;
  res = vld4q_lane_s8 (p, v, 16); /* { dg-error "lane 16 out of range 0 - 15" "" { target *-*-* } 0 } */
  res = vld4q_lane_s8 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 15" "" { target *-*-* } 0 } */
  return res;
}
