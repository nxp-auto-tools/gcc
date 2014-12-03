#include <arm_neon.h>


void
f_vst3_lane_f64 (float64_t * p, float64x1x3_t v)
{
  vst3_lane_f64 (p, v, 1); /* { dg-error "lane 1 out of range 0 - 0" "" { target *-*-* } 0 } */
  vst3_lane_f64 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 0" "" { target *-*-* } 0 } */
  return;
}
