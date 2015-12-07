if (step_over_calls == STEP_OVER_UNDEBUGGABLE
#ifdef IN_SOLIB_DYNSYM_RESOLVE_CODE
      && IN_SOLIB_DYNSYM_RESOLVE_CODE (stop_pc)
#else
      && in_solib_dynsym_resolve_code (stop_pc)
#endif
      )
    {
      CORE_ADDR pc_after_resolver =
	gdbarch_skip_solib_resolver (current_gdbarch, stop_pc);

      if (debug_infrun)
	 fprintf_unfiltered (gdb_stdlog, "infrun: stepped into dynsym resolve code\n");

      if (pc_after_resolver)
	{
	  /* Set up a step-resume breakpoint at the address
	     indicated by SKIP_SOLIB_RESOLVER.  */
	  struct symtab_and_line sr_sal;
	  init_sal (&sr_sal);
	  sr_sal.pc = pc_after_resolver;

	  insert_step_resume_breakpoint_at_sal (sr_sal, null_frame_id);
	}

      keep_going (ecs);
      return;
    }
