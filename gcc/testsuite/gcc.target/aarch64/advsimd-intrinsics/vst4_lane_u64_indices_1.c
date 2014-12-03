#include <arm_neon.h>

/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-fno-fat-lto-objects" } } */
/* { dg-xfail-if "" { arm-*-* } } */

void
f_vst4_lane_u64 (uint64_t * p, uint64x1x4_t v)
{
/* { dg-error "lane 1 out of range 0 - 0" "" { target *-*-* } 0 } */
  vst4_lane_u64 (p, v, 1);
/* { dg-error "lane -1 out of range 0 - 0" "" { target *-*-* } 0 } */
  vst4_lane_u64 (p, v, -1);
  return;
}
