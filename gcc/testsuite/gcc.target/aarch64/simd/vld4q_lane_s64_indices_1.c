#include <arm_neon.h>

int64x2x4_t
f_vld4q_lane_s64 (int64_t * p, int64x2x4_t v)
{
  int64x2x4_t res;
  res = vld4q_lane_s64 (p, v, 2); /* { dg-error "lane 2 out of range 0 - 1" "" { target *-*-* } 0 } */
  res = vld4q_lane_s64 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 1" "" { target *-*-* } 0 } */
  return res;
}
