#ifdef RTCONFIG_BCM_7114
if (nvram_get_int("wlc_psta") != 3)
#endif
			nvram_set("ure_disable", "1");
