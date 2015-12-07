#ifdef RTCONFIG_PROXYSTA
if (is_psta(unit))
		{
#ifdef RTCONFIG_BCM_7114
			if (nvram_get_int("wlc_psta") == 3)
				nvram_set(strcat_r(prefix, "mode", tmp), "wet");
			else
#endif
			nvram_set(strcat_r(prefix, "mode", tmp), "psta");
		}
		else if (is_psr(unit))
		{
			nvram_set(strcat_r(prefix, "mode", tmp), "psr");
		}
		else
#endif
#endif
		if (nvram_match(strcat_r(prefix, "mode_x", tmp), "1"))		// wds only
			nvram_set(strcat_r(prefix, "mode", tmp), "wds");

		else if (nvram_match(strcat_r(prefix, "mode_x", tmp), "3"))	// special defined for client
			nvram_set(strcat_r(prefix, "mode", tmp), "wet");
		else nvram_set(strcat_r(prefix, "mode", tmp), "ap");
