#include <arm_neon.h>

int64x1x3_t
f_vld3_lane_s64 (int64_t * p, int64x1x3_t v)
{
  int64x1x3_t res;
  res = vld3_lane_s64 (p, v, 1); /* { dg-error "lane 1 out of range 0 - 0" "" { target *-*-* } 0 } */
  res = vld3_lane_s64 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 0" "" { target *-*-* } 0 } */
  return res;
}
