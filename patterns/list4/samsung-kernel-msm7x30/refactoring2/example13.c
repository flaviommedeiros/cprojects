#ifdef DHD_DEBUG
if (dhd_console_ms == 0)
#endif /* DHD_DEBUG */
		if (bus->poll == 0)
			dhd_os_wd_timer(bus->dhd, 0);
