if(!pids("mt-daapd") &&
#if defined(RTCONFIG_TIMEMACHINE) || defined(RTCONFIG_MDNS)
			!pids("avahi-daemon")
#else
			!pids("mDNSResponder")
#endif
			)
		return;
