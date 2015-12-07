#ifdef RTCONFIG_WIRELESSREPEATER
if (nvram_get_int("sw_mode") == SW_MODE_REPEATER && nvram_get_int("wlc_state") != WLC_STATE_CONNECTED && !nvram_match("lan_proto", "static")) {
		lan_ipaddr = nvram_default_get("lan_ipaddr");
	} else
#endif
	{
		lan_ipaddr = nvram_safe_get("lan_ipaddr");
	}
