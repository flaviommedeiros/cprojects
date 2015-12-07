#if defined(RTCONFIG_BCM7) || defined(RTCONFIG_BCM_7114) || (defined(RTCONFIG_BCMWL6) && defined(RTCONFIG_WIRELESSREPEATER))
if (is_psta(unit) || is_psr(unit))
#else
	if (is_ure(unit))
#endif
		eval("wl", "-i", ifname, "allmulti", "1");
