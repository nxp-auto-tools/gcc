/* Definitions for Intel IA-64 running FreeBSD using the ELF format
   Copyright (C) 2001 Free Software Foundation, Inc.
   Contributed by David E. O'Brien <obrien@FreeBSD.org> and BSDi.

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */


#undef  LINK_SPEC
#define LINK_SPEC							\
 "%{p:%e`-p' not supported; use `-pg' and gprof(1)}			\
  %{Wl,*:%*}								\
  %{assert*} %{R*} %{rpath*} %{defsym*}					\
  %{shared:-Bshareable %{h*} %{soname*}}				\
  %{symbolic:-Bsymbolic}						\
  %{!shared:								\
    %{!static:								\
      %{rdynamic:-export-dynamic}					\
      %{!dynamic-linker:-dynamic-linker /usr/libexec/ld-elf.so.1}}	\
    %{static:-Bstatic}}"

#undef  ASM_SPEC
#define ASM_SPEC "-x %{mconstant-gp} %{mauto-pic}"


/************************[  Target stuff  ]***********************************/

/* Define the actual types of some ANSI-mandated types.  
   Needs to agree with <machine/ansi.h>.  GCC defaults come from c-decl.c,
   c-common.c, and config/<arch>/<arch>.h.  */

/* alpha.h gets this wrong for FreeBSD.  We use the GCC defaults instead.  */
#undef WCHAR_TYPE

#undef  WCHAR_UNSIGNED
#define WCHAR_UNSIGNED 0

#undef  WCHAR_TYPE_SIZE
#define WCHAR_TYPE_SIZE 32

#undef  TARGET_VERSION
#define TARGET_VERSION fprintf (stderr, " (FreeBSD/IA-64 ELF)");

#define TARGET_ELF		1

#define DONT_USE_BUILTIN_SETJMP
#define JMP_BUF_SIZE  76

/* Output any profiling code before the prologue.  */

#undef  PROFILE_BEFORE_PROLOGUE
#define PROFILE_BEFORE_PROLOGUE 1

/* A C statement or compound statement to output to FILE some assembler code to
   call the profiling subroutine `mcount'.  */

#undef FUNCTION_PROFILER
#define FUNCTION_PROFILER(FILE, LABELNO)		\
do {							\
  char buf[20];						\
  ASM_GENERATE_INTERNAL_LABEL (buf, "LP", LABELNO);	\
  fputs ("\talloc out0 = ar.pfs, 8, 0, 4, 0\n", FILE);	\
  if (TARGET_AUTO_PIC)					\
    fputs ("\tmovl out3 = @gprel(", FILE);		\
  else							\
    fputs ("\taddl out3 = @ltoff(", FILE);		\
  assemble_name (FILE, buf);				\
  if (TARGET_AUTO_PIC)					\
    fputs (");;\n", FILE);				\
  else							\
    fputs ("), r1;;\n", FILE);				\
  fputs ("\tmov out1 = r1\n", FILE);			\
  fputs ("\tmov out2 = b0\n", FILE);			\
  fputs ("\tbr.call.sptk.many b0 = _mcount;;\n", FILE);	\
} while (0)
