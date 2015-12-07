if (!__need_to_start_wps_band("wl0")
#if defined(RTCONFIG_HAS_5G)
 && !__need_to_start_wps_band("wl1")
#endif	/* RTCONFIG_HAS_5G */
	   )
		return;
