#include <arm_neon.h>

float64x2x2_t
f_vld2q_lane_f64 (float64_t * p, float64x2x2_t v)
{
  float64x2x2_t res;
  res = vld2q_lane_f64 (p, v, 2); /* { dg-error "lane 2 out of range 0 - 1" "" { target *-*-* } 0 } */
  res = vld2q_lane_f64 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 1" "" { target *-*-* } 0 } */
  return res;
}
