#ifdef RTCONFIG_WIRELESSREPEATER
if(nvram_get_int("sw_mode") == SW_MODE_REPEATER && !nvram_match("lan_proto", "static")){
		lan_ipaddr_t = nvram_default_get("lan_ipaddr");
		lan_netmask_t = nvram_default_get("lan_netmask");
	}
	else
#endif
	{
		lan_ipaddr_t = nvram_safe_get("lan_ipaddr");
		lan_netmask_t = nvram_safe_get("lan_netmask");
	}
