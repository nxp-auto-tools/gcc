/* { dg-do compile { target { s390*-*-* } } } */
/* { dg-options "-O3 -mzarch -march=z13 -mzvector -fno-asynchronous-unwind-tables" } */

#include <vecintrin.h>

int __attribute__((noinline,noclone))
all_eq_double (vector double a, vector double b)
{
	return vec_all_eq (a, b);
}
/* { dg-final { scan-assembler-times all_eq_double:\n\tvfcedbs\t%v\[0-9\]*,%v24,%v26\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocre\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
all_ne_double (vector double a, vector double b)
{
	return vec_all_ne (a, b);
}
/* { dg-final { scan-assembler-times all_ne_double:\n\tvfcedbs\t%v\[0-9\]*,%v24,%v26\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocrnle\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
all_gt_double (vector double a, vector double b)
{
	return vec_all_gt (a, b);
}
/* { dg-final { scan-assembler-times all_gt_double:\n\tvfchdbs\t%v\[0-9\]*,%v24,%v26\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocre\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
all_lt_double (vector double a, vector double b)
{
	return vec_all_lt (a, b);
}
/* { dg-final { scan-assembler-times all_lt_double:\n\tvfchdbs\t%v\[0-9\]*,%v26,%v24\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocre\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
all_ge_double (vector double a, vector double b)
{
	return vec_all_ge (a, b);
}
/* { dg-final { scan-assembler-times all_ge_double:\n\tvfchedbs\t%v\[0-9\]*,%v24,%v26\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocre\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
all_le_double (vector double a, vector double b)
{
	return vec_all_le (a, b);
}
/* { dg-final { scan-assembler-times all_le_double:\n\tvfchedbs\t%v\[0-9\]*,%v26,%v24\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocre\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
any_eq_double (vector double a, vector double b)
{
	return vec_any_eq (a, b);
}
/* { dg-final { scan-assembler-times any_eq_double:\n\tvfcedbs\t%v\[0-9\]*,%v24,%v26\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocrle\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
any_ne_double (vector double a, vector double b)
{
	return vec_any_ne (a, b);
}
/* { dg-final { scan-assembler-times any_ne_double:\n\tvfcedbs\t%v\[0-9\]*,%v24,%v26\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocrne\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
any_gt_double (vector double a, vector double b)
{
	return vec_any_gt (a, b);
}
/* { dg-final { scan-assembler-times any_gt_double:\n\tvfchdbs\t%v\[0-9\]*,%v24,%v26\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocrle\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
any_lt_double (vector double a, vector double b)
{
	return vec_any_lt (a, b);
}
/* { dg-final { scan-assembler-times any_lt_double:\n\tvfchdbs\t%v\[0-9\]*,%v26,%v24\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocrle\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
any_ge_double (vector double a, vector double b)
{
	return vec_any_ge (a, b);
}
/* { dg-final { scan-assembler-times any_ge_double:\n\tvfchedbs\t%v\[0-9\]*,%v24,%v26\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocrle\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
any_le_double (vector double a, vector double b)
{
	return vec_any_le (a, b);
}
/* { dg-final { scan-assembler-times any_le_double:\n\tvfchedbs\t%v\[0-9\]*,%v26,%v24\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocrle\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
all_eq_int (vector int a, vector int b)
{
	return vec_all_eq (a, b);
}
/* { dg-final { scan-assembler-times all_eq_int:\n\tvceqfs\t%v\[0-9\]*,%v24,%v26\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocre\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
all_ne_int (vector int a, vector int b)
{
	return vec_all_ne (a, b);
}
/* { dg-final { scan-assembler-times all_ne_int:\n\tvceqfs\t%v\[0-9\]*,%v24,%v26\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocrnle\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
all_gt_int (vector int a, vector int b)
{
	return vec_all_gt (a, b);
}
/* { dg-final { scan-assembler-times all_gt_int:\n\tvchfs\t%v\[0-9\]*,%v24,%v26\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocre\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
all_lt_int (vector int a, vector int b)
{
	return vec_all_lt (a, b);
}
/* { dg-final { scan-assembler-times all_lt_int:\n\tvchfs\t%v\[0-9\]*,%v26,%v24\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocre\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
all_ge_int (vector int a, vector int b)
{
	return vec_all_ge (a, b);
}
/* { dg-final { scan-assembler-times all_ge_int:\n\tvchfs\t%v\[0-9\]*,%v26,%v24\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocrnle\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
all_le_int (vector int a, vector int b)
{
	return vec_all_le (a, b);
}
/* { dg-final { scan-assembler-times all_le_int:\n\tvchfs\t%v\[0-9\]*,%v24,%v26\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocrnle\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
any_eq_int (vector int a, vector int b)
{
	return vec_any_eq (a, b);
}
/* { dg-final { scan-assembler-times any_eq_int:\n\tvceqfs\t%v\[0-9\]*,%v24,%v26\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocrle\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
any_ne_int (vector int a, vector int b)
{
	return vec_any_ne (a, b);
}
/* { dg-final { scan-assembler-times any_ne_int:\n\tvceqfs\t%v\[0-9\]*,%v24,%v26\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocrne\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
any_gt_int (vector int a, vector int b)
{
	return vec_any_gt (a, b);
}
/* { dg-final { scan-assembler-times any_gt_int:\n\tvchfs\t%v\[0-9\]*,%v24,%v26\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocrle\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
any_lt_int (vector int a, vector int b)
{
	return vec_any_lt (a, b);
}
/* { dg-final { scan-assembler-times any_lt_int:\n\tvchfs\t%v\[0-9\]*,%v26,%v24\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocrle\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
any_ge_int (vector int a, vector int b)
{
	return vec_any_ge (a, b);
}
/* { dg-final { scan-assembler-times any_ge_int:\n\tvchfs\t%v\[0-9\]*,%v26,%v24\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocrne\t%r2,%r1 1 } } */

int __attribute__((noinline,noclone))
any_le_int (vector int a, vector int b)
{
	return vec_any_le (a, b);
}
/* { dg-final { scan-assembler-times any_le_int:\n\tvchfs\t%v\[0-9\]*,%v24,%v26\n\tlhi\t%r1,1\n\tlhi\t%r2,0\n\tlocrne\t%r2,%r1 1 } } */


