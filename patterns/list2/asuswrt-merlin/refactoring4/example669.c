#if defined(dragonfly) && __DragonFly_version >= 190000
if (proc_table[LowProcIndex].kp_flags & P_SYSTEM)
      #else
        if (proc_table[LowProcIndex].kp_proc.p_flag & P_SYSTEM)
      #endif
	    long_return = 2;	/* operatingSystem */
	else
	    long_return = 4;
