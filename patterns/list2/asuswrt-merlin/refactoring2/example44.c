#if !(defined(RTCONFIG_TIMEMACHINE) || defined(RTCONFIG_MDNS))
if (is_routing_enabled())
#endif
	{
		eval("mt-daapd", "-m");
#if defined(RTCONFIG_TIMEMACHINE) || defined(RTCONFIG_MDNS)
		restart_mdns();
#else
		doSystem("mDNSResponder %s thehost %s _daap._tcp. 3689 &", nvram_safe_get("lan_ipaddr"), servername);
#endif
	}
#if !(defined(RTCONFIG_TIMEMACHINE) || defined(RTCONFIG_MDNS))
	else
		eval("mt-daapd");
