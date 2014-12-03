#include <arm_neon.h>


void
f_vst4_lane_f64 (float64_t * p, float64x1x4_t v)
{
  vst4_lane_f64 (p, v, 1); /* { dg-error "lane 1 out of range 0 - 0" "" { target *-*-* } 0 } */
  vst4_lane_f64 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 0" "" { target *-*-* } 0 } */
  return;
}
