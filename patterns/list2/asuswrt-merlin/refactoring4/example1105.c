# if BRCTL_USE_INTERNAL
if (endptr == time_str)
# else
	if (sscanf(time_str, "%lf", &secs) != 1)
# endif
		bb_error_msg_and_die(bb_msg_invalid_arg, time_str, "timespec");
