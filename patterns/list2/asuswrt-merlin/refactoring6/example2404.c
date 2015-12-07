if (pids("watchdog")
#if defined(RTAC68U) || defined(RTCONFIG_FORCE_AUTO_UPGRADE)
		&& !nvram_get_int("auto_upgrade")
#endif
	)
		killall_tk("watchdog");
