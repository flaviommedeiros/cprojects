return (istate->timestamp.sec &&
#ifdef USE_NSEC
		 /* nanosecond timestamped files can also be racy! */
		(istate->timestamp.sec < sd->sd_mtime.sec ||
		 (istate->timestamp.sec == sd->sd_mtime.sec &&
		  istate->timestamp.nsec <= sd->sd_mtime.nsec))
#else
		istate->timestamp.sec <= sd->sd_mtime.sec
#endif
		);
