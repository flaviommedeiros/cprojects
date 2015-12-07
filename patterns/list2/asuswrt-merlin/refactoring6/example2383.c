if ((CPU_CRIS_MISC_PROFILE (current_cpu)->flags
       & FLAG_CRIS_MISC_PROFILE_XSIM_TRACE)
#ifdef GET_H_INSN_PREFIXED_P
      /* For versions with prefixed insns, trace the combination as
	 one insn.  */
      && !GET_H_INSN_PREFIXED_P ()
#endif
      && 1)
  {
    int i;
    char flags[7];
    unsigned64 cycle_count;

    SIM_DESC sd = CPU_STATE (current_cpu);

    cris_trace_printf (sd, current_cpu, "%lx ",
		       0xffffffffUL & (unsigned long) (CPU (h_pc)));

    for (i = 0; i < 15; i++)
      cris_trace_printf (sd, current_cpu, "%lx ",
			 0xffffffffUL
			 & (unsigned long) (XCONCAT3(crisv,BASENUM,
						     f_h_gr_get) (current_cpu,
								  i)));
    flags[0] = GET_H_IBIT () != 0 ? 'I' : 'i';
    flags[1] = GET_H_XBIT () != 0 ? 'X' : 'x';
    flags[2] = GET_H_NBIT () != 0 ? 'N' : 'n';
    flags[3] = GET_H_ZBIT () != 0 ? 'Z' : 'z';
    flags[4] = GET_H_VBIT () != 0 ? 'V' : 'v';
    flags[5] = GET_H_CBIT () != 0 ? 'C' : 'c';
    flags[6] = 0;

    /* For anything else than basic tracing we'd add stall cycles for
       e.g. unaligned accesses.  FIXME: add --cris-trace=x options to
       match --cris-cycles=x.  */
    cycle_count
      = (CPU_CRIS_MISC_PROFILE (current_cpu)->basic_cycle_count
	 - CPU_CRIS_PREV_MISC_PROFILE (current_cpu)->basic_cycle_count);

    /* Emit ACR after flags and cycle count for this insn.  */
    if (BASENUM == 32)
      cris_trace_printf (sd, current_cpu, "%s %d %lx\n", flags,
			 (int) cycle_count,
			 0xffffffffUL
			 & (unsigned long) (XCONCAT3(crisv,BASENUM,
						     f_h_gr_get) (current_cpu,
								  15)));
    else
      cris_trace_printf (sd, current_cpu, "%s %d\n", flags,
			 (int) cycle_count);

    CPU_CRIS_PREV_MISC_PROFILE (current_cpu)[0]
      = CPU_CRIS_MISC_PROFILE (current_cpu)[0];
  }
