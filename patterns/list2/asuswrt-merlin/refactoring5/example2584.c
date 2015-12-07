#ifdef RTCONFIG_DNSSEC
if (nvram_match("dnssec_enable", "1") && (!nvram_match("ntp_ready","1"))) {
		/* Don't reload, as it would prematurely enable timestamp validation */
		stop_dnsmasq();
		sleep(1);
		start_dnsmasq();
	}
	else
#endif

	/* notify dnsmasq */
	kill_pidfile_s("/var/run/dnsmasq.pid", SIGHUP);
