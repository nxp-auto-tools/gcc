/* Test __builtin_{add,sub,mul}_overflow.  */
/* { dg-do run } */
/* { dg-skip-if "" { ! run_expensive_tests }  { "*" } { "-O0" "-O2" } } */
int v;

__attribute__ ((noinline, noclone))
     void bar (void)
{
  v++;
}

unsigned long long t156_1sub (unsigned long long x, signed long long y)
{
  unsigned long long r;
  if (__builtin_sub_overflow (x, y, &r))
    bar ();
  return r;
}

__attribute__ ((noinline, noclone))
     unsigned long long t156_2sub (signed long long y)
{
  unsigned long long x = ((unsigned long long) 0x7fffffffffffffffLL + 1);
  unsigned long long r;
  if (__builtin_sub_overflow (x, y, &r))
    bar ();
  return r;
}

__attribute__ ((noinline, noclone))
     unsigned long long t156_3sub (signed long long y)
{
  unsigned long long r;
  if (__builtin_sub_overflow
      ((unsigned long long) ((unsigned long long) 0x7fffffffffffffffLL + 1),
       y, &r))
    bar ();
  return r;
}

__attribute__ ((noinline, noclone))
     unsigned long long t156_4sub (unsigned long long x)
{
  signed long long y = ((-0x7fffffffffffffffLL - 1));
  unsigned long long r;
  if (__builtin_sub_overflow (x, y, &r))
    bar ();
  return r;
}

__attribute__ ((noinline, noclone))
     unsigned long long t156_5sub (unsigned long long x)
{
  unsigned long long r;
  if (__builtin_sub_overflow
      (x, (signed long long) ((-0x7fffffffffffffffLL - 1)), &r))
    bar ();
  return r;
}

__attribute__ ((noinline, noclone))
     void t156sub (void)
{
  unsigned long long x = ((unsigned long long) 0x7fffffffffffffffLL + 1);
  signed long long y = ((-0x7fffffffffffffffLL - 1));
  unsigned long long r1, r2;
  v = 0;
  if (t156_1sub (x, y) != (unsigned long long) (0)
      || t156_2sub (y) != (unsigned long long) (0)
      || t156_3sub (y) != (unsigned long long) (0)
      || t156_4sub (x) != (unsigned long long) (0)
      || t156_5sub (x) != (unsigned long long) (0))
    __builtin_abort ();
  if (__builtin_sub_overflow (x, y, &r1))
    bar ();
  if (r1 != (unsigned long long) (0))
    __builtin_abort ();
  if (__builtin_sub_overflow
      ((unsigned long long) ((unsigned long long) 0x7fffffffffffffffLL + 1),
       (signed long long) ((-0x7fffffffffffffffLL - 1)), &r2))
    bar ();
  if (r2 != (unsigned long long) (0) || v != 7 * 1)
    __builtin_abort ();
}

int
main ()
{
  t156sub ();
  return 0;
}
