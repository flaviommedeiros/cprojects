if (scan_env.backrefed_mem == 0
#ifdef USE_SUBEXP_CALL
      || scan_env.num_call == 0
#endif
      ) {
    setup_comb_exp_check(root, 0, &scan_env);
#ifdef USE_SUBEXP_CALL
    if (scan_env.has_recursion != 0) {
      scan_env.num_comb_exp_check = 0;
    }
    else
#endif
    if (scan_env.comb_exp_max_regnum > 0) {
      int i;
      for (i = 1; i <= scan_env.comb_exp_max_regnum; i++) {
	if (BIT_STATUS_AT(scan_env.backrefed_mem, i) != 0) {
	  scan_env.num_comb_exp_check = 0;
	  break;
	}
      }
    }
  }
