if(
#ifdef ENABLE_NATPMP
        !GETFLAG(ENABLENATPMPMASK) &&
#endif
        !GETFLAG(ENABLEUPNPMASK) ) {
		syslog(LOG_ERR, "Why did you run me anyway?");
		return 0;
	}
