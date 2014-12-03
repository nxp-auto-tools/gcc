#include <arm_neon.h>

int32x4x4_t
f_vld4q_lane_s32 (int32_t * p, int32x4x4_t v)
{
  int32x4x4_t res;
  res = vld4q_lane_s32 (p, v, 4); /* { dg-error "lane 4 out of range 0 - 3" "" { target *-*-* } 0 } */
  res = vld4q_lane_s32 (p, v, -1); /* { dg-error "lane -1 out of range 0 - 3" "" { target *-*-* } 0 } */
  return res;
}
