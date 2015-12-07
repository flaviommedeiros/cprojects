#if defined(RTN14U) || defined(RTN11P) || defined(RTN300)
if (!mssid_mac_validate(macaddr))
#else
	if (!mssid_mac_validate(macaddr) || !mssid_mac_validate(macaddr2))
#endif
		nvram_set("wl_mssid", "0");
	else
		nvram_set("wl_mssid", "1");
