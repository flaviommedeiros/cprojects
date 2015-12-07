#ifdef RTCONFIG_BCM_7114
if (nvram_get_int("wlc_psta") == 3)
				nvram_set(strcat_r(prefix, "mode", tmp), "wet");
			else
#endif
			nvram_set(strcat_r(prefix, "mode", tmp), "psta");
