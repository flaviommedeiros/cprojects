#ifdef RTCONFIG_PROXYSTA
if (is_psta(nvram_get_int("wlc_band")) || is_psr(nvram_get_int("wlc_band")))
			{
				snprintf(prefix, sizeof(prefix), "wl%d_", 1 - nvram_get_int("wlc_band"));
				strncpy(ssid_g, nvram_safe_get(strcat_r(prefix, "ssid", tmp)), 32);
			}
			else
#endif
#endif
		     strncpy(ssid_g, nvram_safe_get("wl0_ssid"), 32);
