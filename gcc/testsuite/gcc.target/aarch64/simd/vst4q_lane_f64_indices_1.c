#include <arm_neon.h>


void
f_vst4q_lane_f64 (float64_t * p, float64x2x4_t v)
{
  vst4q_lane_f64 (p, v, 2); /* { dg-error "lane 2 out of range 0 - 1" "" { target *-*-* } 0 } */
  vst4q_lane_f64 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 1" "" { target *-*-* } 0 } */
  return;
}
