#include <arm_neon.h>

poly8x16x3_t
f_vld3q_lane_p8 (poly8_t * p, poly8x16x3_t v)
{
  poly8x16x3_t res;
  res = vld3q_lane_p8 (p, v, 16); /* { dg-error "lane 16 out of range 0 - 15" "" { target *-*-* } 0 } */
  res = vld3q_lane_p8 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 15" "" { target *-*-* } 0 } */
  return res;
}
