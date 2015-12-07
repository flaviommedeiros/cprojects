if (!nvram_match(strcat_r(prefix, "mode", tmp), "psta") &&
	    !nvram_match(strcat_r(prefix, "mode", tmp2), "psr")
#ifdef RTCONFIG_BCM_7114
	    && !(is_psta(nvram_get_int("wlc_band")) && (nvram_get_int("wlc_psta") == 3))
#endif
	) goto PSTA_ERR;
