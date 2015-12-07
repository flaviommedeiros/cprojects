#ifdef RTCONFIG_DHCP_OVERRIDE
if(nvram_match("lan_proto", "static") || nvram_get_int("sw_mode") == SW_MODE_AP)
#else
	if(nvram_match("lan_proto", "static"))
#endif
		ifconfig(lan_ifname, IFUP, nvram_safe_get("lan_ipaddr"), nvram_safe_get("lan_netmask"));
	else
		ifconfig(lan_ifname, IFUP, nvram_default_get("lan_ipaddr"), nvram_default_get("lan_netmask"));
