if ((nvram_get_int("sw_mode") == SW_MODE_AP) &&
		(nvram_get_int("wlc_psta") == 2) &&
		((nvram_get_int("wlc_band") == unit)
#ifdef PXYSTA_DUALBAND
		||  (nvram_match("exband", "1") && nvram_get_int("wlc_band_ex") == unit)
#endif
		))
		return 1;
