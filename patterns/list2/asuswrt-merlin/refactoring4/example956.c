#if defined (VI_MODE)
if (!func || func == rl_do_lowercase_version || func == rl_vi_movement_mode)
#else
      if (!func || func == rl_do_lowercase_version)
#endif
	return (rl_bind_keyseq_in_map (keyseq, default_func, kmap));
      else
	return 1;
