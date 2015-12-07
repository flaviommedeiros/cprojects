if (
#ifdef IN_SOLIB_DYNSYM_RESOLVE_CODE
	  IN_SOLIB_DYNSYM_RESOLVE_CODE (ecs->stop_func_start)
#else
	  in_solib_dynsym_resolve_code (ecs->stop_func_start)
#endif
)
	{
	  struct symtab_and_line sr_sal;
	  init_sal (&sr_sal);
	  sr_sal.pc = ecs->stop_func_start;

	  insert_step_resume_breakpoint_at_sal (sr_sal, null_frame_id);
	  keep_going (ecs);
	  return;
	}
