#include <arm_neon.h>

int64x1x2_t
f_vld2_lane_s64 (int64_t * p, int64x1x2_t v)
{
  int64x1x2_t res;
  res = vld2_lane_s64 (p, v, 1); /* { dg-error "lane 1 out of range 0 - 0" "" { target *-*-* } 0 } */
  res = vld2_lane_s64 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 0" "" { target *-*-* } 0 } */
  return res;
}
