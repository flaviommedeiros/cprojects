#ifdef GTP_RB
if (gtp_start || gtp_frame_current_num < 0 || gtp_replay_step_tpe)
#endif
		return -EINVAL;
