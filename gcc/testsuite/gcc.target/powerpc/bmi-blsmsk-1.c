/* { dg-do run } */
/* { dg-require-effective-target lp64 } */
/* { dg-options "-O3 -m64 -fno-inline" } */

#define NO_WARN_X86_INTRINSICS 1
#include <x86intrin.h>
#include "bmi-check.h"

/*  Trick compiler in order not to generate target insn here. */
long long calc_blsmsk_u64 (long long src1, long long src2)
{
  return (src1-1) ^ (src2);
}

static void
bmi_test ()
{
  unsigned i;
  long long src = 0xfacec0ffeefacec0;
  long long res, res_ref;

  for (i=0; i<5; ++i) {
    src = (i + src) << i;

    res_ref = calc_blsmsk_u64 (src, src);
    res = __blsmsk_u64 (src);

    if (res != res_ref)
      abort();
  }
}
