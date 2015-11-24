#if WATCHDOG_CONF_TIMEOUT >= 0
if(!stopped)
#endif
		wdt_reset();
