return (!S_ISGITLINK(ce->ce_mode) &&
		istate->timestamp.sec &&
#ifdef USE_NSEC
		 /* nanosecond timestamped files can also be racy! */
		(istate->timestamp.sec < ce->ce_stat_data.sd_mtime.sec ||
		 (istate->timestamp.sec == ce->ce_stat_data.sd_mtime.sec &&
		  istate->timestamp.nsec <= ce->ce_stat_data.sd_mtime.nsec))
#else
		istate->timestamp.sec <= ce->ce_stat_data.sd_mtime.sec
#endif
		 );
