#include <arm_neon.h>


void
f_vst4q_lane_f32 (float32_t * p, float32x4x4_t v)
{
  vst4q_lane_f32 (p, v, 4); /* { dg-error "lane 4 out of range 0 - 3" "" { target *-*-* } 0 } */
  vst4q_lane_f32 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 3" "" { target *-*-* } 0 } */
  return;
}
