# AArch64 support for -fsplit-stack.
# Copyright (C) 2016 Free Software Foundation, Inc.

# This file is part of GCC.

# GCC is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 3, or (at your option) any later
# version.

# GCC is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.

# Under Section 7 of GPL version 3, you are granted additional
# permissions described in the GCC Runtime Library Exception, version
# 3.1, as published by the Free Software Foundation.

# You should have received a copy of the GNU General Public License and
# a copy of the GCC Runtime Library Exception along with this program;
# see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
# <http://www.gnu.org/licenses/>.

/* Define an entry point visible from C.  */
#define ENTRY(name)						\
  .globl name;							\
  .type name,%function;						\
  .align 4;							\
  name##:

#define END(name)						\
  .size name,.-name


#define MORESTACK_FRAMESIZE	112
/* Offset based on function stack to get its argument from __morestack
   frame.  */
#define STACKFRAME_BASE		(-MORESTACK_FRAMESIZE - 16)
/* Offset from __morestack frame where the new stack size is saved and
   passed to __generic_morestack.  */
#define NEWSTACK_SAVE		88
/* Offset from __morestack frame where the arguments size saved and
   passed to __generic_morestack.  */
#define ARGS_SIZE_SAVE		80

#define BACKOFF			0x2000
# Large excess allocated when calling non-split-stack code.
#define NON_SPLIT_STACK		0x100000

# TCB offset of __private_ss
#define TCB_PRIVATE_SS		#16

	.text
ENTRY(__morestack_non_split)
	.cfi_startproc
# We use a cleanup to restore the tcbhead_t.__private_ss if
# an exception is thrown through this code.
	add	x11, x11, NON_SPLIT_STACK
	.cfi_endproc
END(__morestack_non_split)
# Fall through into __morestack

# This function is called with non-standard calling conventions.  On entry
# x10 is the requested stack pointer.  The split-stack prologue is in the
# form:
#
#	mrs    x9, tpidr_el0
#	mov    x10, -<required stack allocation>
#	add    x10, sp, x10
#	ldr    x9, [x9, 16]
#	cmp    x10, x9
#	bcs    enough
#	stp    x30, [sp, -16]!
#	mov    x11, <required arguments copy size>
#	bl     __morestack
#	ldp    x30, [sp], 16
#	ret
# enough:
#
# The normal function prologue follows here, with a small addition at the
# end to set up the argument pointer.  The argument pointer is setup with:
#
#	mov     x11, <required stack allocation>
#	sub	sp, sp, <required stack allocation>
#	add	x10, x29, x11
#	b.cs    function:
#	mov     x10, x28
# function:
#
# Note that all argument parameter registers and the x10 (the argument
# pointer) are saved.  The N bit is also saved and restores to indicate
# that the function is called (so the prologue addition can set up the
# argument pointer correctly).

ENTRY(__morestack)
.LFB1:
	.cfi_startproc

#ifdef __PIC__
	.cfi_personality 0x9b,DW.ref.__gcc_personality_v0
	.cfi_lsda 0x1b,.LLSDA1
#else
	.cfi_personality 0x3,__gcc_personality_v0
	.cfi_lsda 0x3,.LLSDA1
#endif

	# Calculate requested stack size.
	sub	x12, sp, x10
	# Save parameters
	stp	x29, x30, [sp, -MORESTACK_FRAMESIZE]!
	.cfi_def_cfa_offset MORESTACK_FRAMESIZE
	.cfi_offset 29, -MORESTACK_FRAMESIZE
	.cfi_offset 30, -MORESTACK_FRAMESIZE+8
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	# Adjust the requested stack size for the frame pointer save.
	add	x12, x12, 16
	stp	x0, x1, [sp, 16]
	stp	x2, x3, [sp, 32]
	add	x12, x12, BACKOFF
	stp	x4, x5, [sp, 48]
	stp	x6, x7, [sp, 64]
	stp	x11, x12, [sp, 80]
	str	x28, [sp, 96]

	# Setup on x28 the function initial frame pointer.  Its value will
	# copied to function argument pointer.
	add	x28, sp, MORESTACK_FRAMESIZE + 16

	# void __morestack_block_signals (void)
	bl	__morestack_block_signals

	# void *__generic_morestack (size_t *pframe_size,
	#			     void *old_stack,
	#			     size_t param_size)
	# pframe_size: is the size of the required stack frame (the function
	#	       amount of space remaining on the allocated stack).
	# old_stack: points at the parameters the old stack
	# param_size: size in bytes of parameters to copy to the new stack.
	add	x0, x28, STACKFRAME_BASE + NEWSTACK_SAVE
	mov	x1, x28
	ldr	x2, [sp, ARGS_SIZE_SAVE]
	bl	__generic_morestack

	# Start using new stack
	stp	x29, x30, [x0, -16]!
	mov	sp, x0

	# Set __private_ss stack guard for the new stack.
	ldr	x9, [x28, STACKFRAME_BASE + NEWSTACK_SAVE]
	add	x0, x0, BACKOFF
	sub	x0, x0, 16
	sub	x0, x0, x9
.LEHB0:
	mrs	x1, tpidr_el0
	str	x0, [x1, TCB_PRIVATE_SS]

	# void __morestack_unblock_signals (void)
	bl	__morestack_unblock_signals

	# Set up for a call to the target function.
	#ldp	x29, x30, [x28, STACKFRAME_BASE]
	ldr	x30, [x28, STACKFRAME_BASE + 8]
	ldp	x0, x1, [x28, STACKFRAME_BASE + 16]
	ldp	x2, x3, [x28, STACKFRAME_BASE + 32]
	ldp	x4, x5, [x28, STACKFRAME_BASE + 48]
	ldp	x6, x7, [x28, STACKFRAME_BASE + 64]
	add	x9, x30, 8
	cmp	x30, x9
	blr	x9

	stp	x0, x1, [x28, STACKFRAME_BASE + 16]
	stp	x2, x3, [x28, STACKFRAME_BASE + 32]
	stp	x4, x5, [x28, STACKFRAME_BASE + 48]
	stp	x6, x7, [x28, STACKFRAME_BASE + 64]

	bl	__morestack_block_signals

	# void *__generic_releasestack (size_t *pavailable)
	add	x0, x28, STACKFRAME_BASE + NEWSTACK_SAVE
	bl	__generic_releasestack

	# Reset __private_ss stack guard to value for old stack
	ldr	x9, [x28, STACKFRAME_BASE + NEWSTACK_SAVE]
	add	x0, x0, BACKOFF
	sub	x0, x0, x9

	# Update TCB split stack field
.LEHE0:
	mrs	x1, tpidr_el0
	str	x0, [x1, TCB_PRIVATE_SS]

	bl __morestack_unblock_signals

	# Use old stack again.
	sub	sp, x28, 16

	ldp	x0, x1, [x28, STACKFRAME_BASE + 16]
	ldp	x2, x3, [x28, STACKFRAME_BASE + 32]
	ldp	x4, x5, [x28, STACKFRAME_BASE + 48]
	ldp	x6, x7, [x28, STACKFRAME_BASE + 64]
	ldp	x29, x30, [x28, STACKFRAME_BASE]
	ldr	x28, [x28, STACKFRAME_BASE + 96]

	.cfi_remember_state
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0

	ret

# This is the cleanup code called by the stack unwinder when
# unwinding through code between .LEHB0 and .LEHE0 above.
cleanup:
	.cfi_restore_state
	str	x0, [x28, STACKFRAME_BASE]
	# size_t __generic_findstack (void *stack)
	mov	x0, x28
	bl	__generic_findstack
	sub	x0, x28, x0
	add	x0, x0, BACKOFF
	# Restore tcbhead_t.__private_ss
	mrs	x1, tpidr_el0
	str	x0, [x1, TCB_PRIVATE_SS]
	ldr	x0, [x28, STACKFRAME_BASE]
	b	_Unwind_Resume
        .cfi_endproc
END(__morestack)

	.section .gcc_except_table,"a",@progbits
	.align 4
.LLSDA1:
	# @LPStart format (omit)
        .byte   0xff
	# @TType format (omit)
        .byte   0xff
	# Call-site format (uleb128)
        .byte   0x1
	# Call-site table length
        .uleb128 .LLSDACSE1-.LLSDACSB1
.LLSDACSB1:
	# region 0 start
        .uleb128 .LEHB0-.LFB1
	# length
        .uleb128 .LEHE0-.LEHB0
	# landing pad
        .uleb128 cleanup-.LFB1
	# no action (ie a cleanup)
        .uleb128 0
.LLSDACSE1:


	.global __gcc_personality_v0
#ifdef __PIC__
	# Build a position independent reference to the personality function.
	.hidden DW.ref.__gcc_personality_v0
	.weak   DW.ref.__gcc_personality_v0
	.section .data.DW.ref.__gcc_personality_v0,"awG",@progbits,DW.ref.__gcc_personality_v0,comdat
	.type   DW.ref.__gcc_personality_v0, @object
	.align 3
DW.ref.__gcc_personality_v0:
	.size   DW.ref.__gcc_personality_v0, 8
	.quad   __gcc_personality_v0
#endif

	.section .note.GNU-stack,"",@progbits
	.section .note.GNU-split-stack,"",@progbits
	.section .note.GNU-no-split-stack,"",@progbits
