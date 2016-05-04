/* AArch64 support for -fsplit-stack.
 * Copyright (C) 2016 Free Software Foundation, Inc.
 *
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3, or (at your option) any
 * later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * Under Section 7 of GPL version 3, you are granted additional
 * permissions described in the GCC Runtime Library Exception, version
 * 3.1, as published by the Free Software Foundation.
 *
 * You should have received a copy of the GNU General Public License and
 * a copy of the GCC Runtime Library Exception along with this program;
 * see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef inhibit_libc

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include "generic-morestack.h"

/* This is based on GLIBC definition (version 2.24).  There is no need to
   keep it sync since new fields are added on the end of structure and do
   not change the '__private_ss' layout.  */
typedef struct
{
  void *dtv;
  void *private;
  void *__private_ss;
} tcbhead_t;

#define INITIAL_STACK_SIZE  0x4000
#define BACKOFF             0x1000

void __generic_morestack_set_initial_sp (void *sp, size_t len);
void *__morestack_get_guard (void);
void __morestack_set_guard (void *);
void *__morestack_make_guard (void *stack, size_t size);
void __morestack_load_mmap (void);

/* We declare is as weak so it fails either at stack linking or
   at runtime if the GLIBC does not have the required TCB field.  */
extern void __tcb_private_ss (void) __attribute__ ((weak));

/* Initialize the stack guard when the program starts or when a new
   thread.  This is called from a constructor using ctors section.  */
void
__stack_split_initialize (void)
{
  __tcb_private_ss ();

  register void* sp __asm__ ("sp");
  tcbhead_t *tcb = ((tcbhead_t *) __builtin_thread_pointer ());
  tcb->__private_ss = (void*)((uintptr_t)sp - INITIAL_STACK_SIZE);
  return __generic_morestack_set_initial_sp (sp, INITIAL_STACK_SIZE);
}

/* Return current __private_ss.  */
void *
__morestack_get_guard (void)
{
  tcbhead_t *tcb = ((tcbhead_t *) __builtin_thread_pointer ());
  return tcb->__private_ss;
}

/* Set __private_ss to ptr.  */
void
__morestack_set_guard (void *ptr)
{
  tcbhead_t *tcb = ((tcbhead_t *) __builtin_thread_pointer ());
  tcb->__private_ss = ptr;
}

/* Return the stack guard value for given stack.  */
void *
__morestack_make_guard (void *stack, size_t size)
{
  return (void*)((uintptr_t)stack - size + BACKOFF);
}

/* Make __stack_split_initialize a high priority constructor.  */
static void (*const ctors []) 
  __attribute__ ((used, section (".ctors.65535"), aligned (sizeof (void *))))
  = { __stack_split_initialize, __morestack_load_mmap };

#endif /* !defined (inhibit_libc) */
