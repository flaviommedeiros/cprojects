if(nvram_match("stop_gmac3", "1")	// disable gmac3
	//|| (nvram_get("switch_wantag") && !nvram_match("switch_wantag", "") && !nvram_match("switch_wantag", "none"))
	//|| (is_psta(nvram_get_int("wlc_band")) && (nvram_get_int("wlc_psta") == 3))
#if defined(RTAC88U) || defined(RTAC3100)
	//|| nvram_get_int("sw_mode") == SW_MODE_ROUTER
#endif
	)
		gmac3_restore_nvram();
	else
		gmac3_override_nvram();
