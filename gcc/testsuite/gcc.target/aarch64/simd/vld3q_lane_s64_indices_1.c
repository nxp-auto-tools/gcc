#include <arm_neon.h>

int64x2x3_t
f_vld3q_lane_s64 (int64_t * p, int64x2x3_t v)
{
  int64x2x3_t res;
  res = vld3q_lane_s64 (p, v, 2); /* { dg-error "lane 2 out of range 0 - 1" "" { target *-*-* } 0 } */
  res = vld3q_lane_s64 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 1" "" { target *-*-* } 0 } */
  return res;
}
