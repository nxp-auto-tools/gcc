#include <arm_neon.h>

uint64x1x3_t
f_vld3_lane_u64 (uint64_t * p, uint64x1x3_t v)
{
  uint64x1x3_t res;
  res = vld3_lane_u64 (p, v, 1); /* { dg-error "lane 1 out of range 0 - 0" "" { target *-*-* } 0 } */
  res = vld3_lane_u64 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 0" "" { target *-*-* } 0 } */
  return res;
}
