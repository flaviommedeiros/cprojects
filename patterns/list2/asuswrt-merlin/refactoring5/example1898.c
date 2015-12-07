#ifdef BCMWPSAPSTA
if (wps_pbc_apsta_enabled == TRUE) {
			/*
			 * For apsta mode (wps_pbc_apsta enabled),
			 * wps_monitor decide which interface to run WPS when HW PBC pressed
			 */
			if (wps_pbc_apsta_upstream_pushed == TRUE)
				strcpy(wps_ifname, wps_safe_get_conf("wps_pbc_sta_ifname"));
			else
				strcpy(wps_ifname, wps_safe_get_conf("wps_pbc_ap_ifname"));

			TUTRACE((TUTRACE_INFO, "wps_pbc_apsta mode enabled, wps_ifname = %s \n",
				wps_ifname));
		}
		else
#endif /* BCMWPSAPSTA */
			strcpy(wps_ifname, pb_ifname);
