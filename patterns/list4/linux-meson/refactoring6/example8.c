if (input2pre
		#ifdef NEW_DI_V3
		&& di_pre_stru.cur_prog_flag
		#endif
		&& vdin_source_flag
		&& (bypass_state==0)) {

		return 1;
	}
