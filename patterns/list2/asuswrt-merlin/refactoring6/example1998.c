if ((is_psta(nvram_get_int("wlc_band")) || is_psr(nvram_get_int("wlc_band")))
#if defined(RTCONFIG_BCM7) || defined(RTCONFIG_BCM_7114)
#ifdef RTCONFIG_GMAC3
		&& !nvram_match("gmac3_enable", "1")
#endif
		&& nvram_match("ctf_disable", "1")
#endif
	) setup_dnsmq(1);
