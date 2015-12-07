if (MAX_NR_PROCESSORS > 1
	  && (0
#if WITH_PROFILE_INSN_P
	      || PROFILE_FLAGS (data) [PROFILE_INSN_IDX]
#endif
#if WITH_PROFILE_MEMORY_P
	      || PROFILE_FLAGS (data) [PROFILE_MEMORY_IDX]
#endif
#if WITH_PROFILE_CORE_P
	      || PROFILE_FLAGS (data) [PROFILE_CORE_IDX]
#endif
#if WITH_PROFILE_MODEL_P
	      || PROFILE_FLAGS (data) [PROFILE_MODEL_IDX]
#endif
#if WITH_PROFILE_SCACHE_P && WITH_SCACHE
	      || PROFILE_FLAGS (data) [PROFILE_SCACHE_IDX]
#endif
#if WITH_PROFILE_PC_P
	      || PROFILE_FLAGS (data) [PROFILE_PC_IDX]
#endif
	      ))
	{
	  sim_io_printf (sd, "CPU %d\n\n", c);
	}
