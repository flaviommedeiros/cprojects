if(nvram_get_int("sw_mode") != SW_MODE_REPEATER
#ifdef RTCONFIG_WIRELESSREPEATER
			|| (nvram_get_int("sw_mode") == SW_MODE_REPEATER && nvram_get_int("wlc_state") == WLC_STATE_CONNECTED)
#endif
			) {
		route_add(lan_ifname, 0, "0.0.0.0", nvram_safe_get("lan_gateway"), "0.0.0.0");

		/* Sync time */
		if (!pids("ntp"))
		{
			stop_ntpc();
			start_ntpc();
		}
		else
			kill_pidfile_s("/var/run/ntp.pid", SIGALRM);
	}
