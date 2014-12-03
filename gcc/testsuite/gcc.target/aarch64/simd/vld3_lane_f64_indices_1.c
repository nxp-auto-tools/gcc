#include <arm_neon.h>

float64x1x3_t
f_vld3_lane_f64 (float64_t * p, float64x1x3_t v)
{
  float64x1x3_t res;
  res = vld3_lane_f64 (p, v, 1); /* { dg-error "lane 1 out of range 0 - 0" "" { target *-*-* } 0 } */
  res = vld3_lane_f64 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 0" "" { target *-*-* } 0 } */
  return res;
}
