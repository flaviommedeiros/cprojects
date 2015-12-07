if (nvram_get_int("sw_mode") == SW_MODE_REPEATER
#if defined(RTCONFIG_BCM_7114) && defined(RTCONFIG_PROXYSTA)
			|| is_ure
#endif
		) {
			snprintf(prefix, sizeof(prefix), "wl%d_", nvram_get_int("wlc_band"));
			inet_aton(nvram_safe_get("lan_ipaddr"), (struct in_addr *)&ip);
#ifdef __CONFIG_DHDAP__
			is_dhd = !dhd_probe(nvram_safe_get(strcat_r(prefix, "ifname", tmp)));
			if (is_dhd) {
				dhd_iovar_setint(nvram_safe_get(strcat_r(prefix, "ifname", tmp)), "wet_host_ipv4", ip);
			} else
#endif /* __CONFIG_DHDAP__ */
			wl_iovar_setint(nvram_safe_get(strcat_r(prefix, "ifname", tmp)), "wet_host_ipv4", ip);
		}
