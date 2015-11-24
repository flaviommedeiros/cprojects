if (options.verbosity > 3 && !(options.flags & FLG_SHOW_CHK))
		fprintf(stderr,
		        "Local worksize (LWS) "Zu", global worksize (GWS) "Zu"\n",
		        local_work_size, global_work_size);
#ifdef DEBUG
	else if (!(options.flags & FLG_SHOW_CHK))
		fprintf(stderr, "{"Zu"/"Zu"} ", global_work_size, local_work_size);
#endif
