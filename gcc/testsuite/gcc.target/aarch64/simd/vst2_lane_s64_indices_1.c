#include <arm_neon.h>


void
f_vst2_lane_s64 (int64_t * p, int64x1x2_t v)
{
  vst2_lane_s64 (p, v, 1); /* { dg-error "lane 1 out of range 0 - 0" "" { target *-*-* } 0 } */
  vst2_lane_s64 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 0" "" { target *-*-* } 0 } */
  return;
}
