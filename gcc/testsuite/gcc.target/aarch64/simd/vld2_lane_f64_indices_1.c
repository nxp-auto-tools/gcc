#include <arm_neon.h>

float64x1x2_t
f_vld2_lane_f64 (float64_t * p, float64x1x2_t v)
{
  float64x1x2_t res;
  res = vld2_lane_f64 (p, v, 1); /* { dg-error "lane 1 out of range 0 - 0" "" { target *-*-* } 0 } */
  res = vld2_lane_f64 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 0" "" { target *-*-* } 0 } */
  return res;
}
