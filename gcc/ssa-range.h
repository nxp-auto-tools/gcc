/* Header file for ssa-range generator.
   Copyright (C) 2017-2018 Free Software Foundation, Inc.
   Contributed by Andrew MacLeod <amacleod@redhat.com>.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#ifndef GCC_SSA_RANGE_H
#define GCC_SSA_RANGE_H

#include "ssa-range-bb.h"

/* This class utilizes the basic block GORI map and is used to query the range
   of SSA_NAMEs across multiple basic blocks and edges.  It builds a cache
   of range on entry to blocks.  ALL work is done
   on-demand so it is relatively lightweight until used.
   
   There is a global ssa-name table implemented within path_ranger via 
   a set of protected global_ssa_name routines.  These are here until such
   time that there is a global irange table for real.  
   */

class path_ranger : public block_ranger
{
public:
  enum path_range_direction { FORWARD, REVERSE };
  path_ranger ();
  ~path_ranger ();

  /* What is the known range of name from its DEF point to edge E.  */
  bool path_range_edge (irange& r, tree name, edge e);
  bool path_range_entry (irange& r, tree name, basic_block bb);
  // Get the range of the LHS of the statement.
  bool path_range_stmt (irange& r, gimple *g);
  // get the value of NAME as it would be used on this stmt.
  bool path_range_on_stmt (irange&r, tree name, gimple *g);

  bool path_range_list (irange &r, tree name, const vec<basic_block> &bbs,
		        enum path_range_direction, edge start_edge = NULL);

  void dump (FILE *f);
  void exercise (FILE *f);   /* do a full mapping pass, dump if provided.  */
protected:
  virtual bool get_operand_range (irange &r, tree op, gimple *s = NULL);
private:
  class block_range_cache *m_block_cache;
  class ssa_global_cache *m_globals;
  class non_null_ref *m_non_null;

  void range_for_bb (irange &r, tree name, basic_block bb, basic_block def_bb);
  void determine_block (tree name, basic_block bb, basic_block def_bb);
  bool path_range_list_reverse (irange &r, tree name, const vec<basic_block> &);
  bool process_phi (irange &r, gimple *g);
  bool process_call (irange &r, gimple *call);
  bool non_null_deref_in_block (irange &r, tree name, basic_block bb);

  void dump_global_ssa_range (FILE *f);
  bool has_global_ssa_range (irange& r, tree name);
  bool get_global_ssa_range (irange& r, tree name);
  void set_global_ssa_range (tree name, const irange&r);
  void clear_global_ssa_range (tree name);
};

/* Like path_ranger::path_range_on_stmt(), but make an on-the-fly ranger.

   Return TRUE if SSA as seen from within STMT has a known range.  Set
   the known range in R.

   NOTE: There is a small overhead involved with this function, so it
   should only be used for very lightweight or unrelated range
   queries.  This function is mostly meant for range queries that
   don't need caching in subsequent calls.  */

static inline bool
on_demand_get_range_on_stmt (irange &r, tree ssa, gimple *stmt)
{
  path_ranger ranger;
  return ranger.path_range_on_stmt (r, ssa, stmt);
}

#endif /* GCC_SSA_RANGE_H */
