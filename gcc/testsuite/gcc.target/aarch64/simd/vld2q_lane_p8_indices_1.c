#include <arm_neon.h>

poly8x16x2_t
f_vld2q_lane_p8 (poly8_t * p, poly8x16x2_t v)
{
  poly8x16x2_t res;
  res = vld2q_lane_p8 (p, v, 16); /* { dg-error "lane 16 out of range 0 - 15" "" { target *-*-* } 0 } */
  res = vld2q_lane_p8 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 15" "" { target *-*-* } 0 } */
  return res;
}
