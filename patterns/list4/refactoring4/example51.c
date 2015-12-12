#ifdef GTP_FRAME_SIMPLE
if (gtp_start || !gtp_frame_current)
#endif
#ifdef GTP_FTRACE_RING_BUFFER
	if (gtp_start || gtp_frame_current_num < 0)
#endif
#ifdef GTP_RB
	/* For gtp_replay_step_tpe, the KGTP is in replay mode.  Send traceframe_info
	   will make GDB got error with access the memory.  So return -EINVAL.  */
	if (gtp_start || gtp_frame_current_num < 0 || gtp_replay_step_tpe)
#endif
		return -EINVAL;
