if (!strcmp(status, "Success") 
#ifdef RTCONFIG_WPS_ENROLLEE
				|| !strcmp(status, "COMPLETED")
#endif
		) {
			dbG("\nWPS %s\n", status);
#ifdef RTCONFIG_WPS_LED
			nvram_set("wps_success", "1");
#endif
#if (defined(RTCONFIG_WPS_ENROLLEE) && defined(RTCONFIG_WIFI_CLONE))
			if (nvram_match("wps_enrollee", "1")) {
				nvram_set("wps_e_success", "1");
#if (defined(PLN12) || defined(PLAC56))
				set_wifiled(4);
#endif
				wifi_clone(i);
			}
#endif
			ret = 1;
		}
		else if (!strcmp(status, "Failed") 
#ifdef RTCONFIG_WPS_ENROLLEE
				|| !strcmp(status, "INACTIVE")
#endif
		) {
			dbG("\nWPS %s\n", status);
			ret = 1;
		}
		else
			ret = 0;
