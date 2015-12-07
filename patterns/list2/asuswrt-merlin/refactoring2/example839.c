#if defined(RTCONFIG_BCMWL6) && defined(RTCONFIG_PROXYSTA)
if (!is_psta(nvram_get_int("wlc_band")) && !is_psr(nvram_get_int("wlc_band")))
#endif
		eval("iptables", "-t", "nat", "-I", "PREROUTING", "-p", "tcp", "-d", "10.0.0.1", "--dport", "80", "-j", "DNAT", "--to-destination", strcat_r(nvram_safe_get("lan_ipaddr"), ":80", tmp));
