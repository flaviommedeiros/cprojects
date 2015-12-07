#ifdef RTCONFIG_PROXYSTA
if (nvram_get_int("wlc_psta") == 0) {
#endif
	m = wl_mask & 0xFF;
	for (i = 0, unit = 0, sunit = 0, sidx = 0; m > 0; ++i, ++sunit, ++sidx, m >>= 1) {
		char *str;
		if (i == 4) {
			unit = 1;
			sunit = 0;
			sidx = 0;
		}
		if (!nvram_match(wl_nvname("bss_enabled", unit, sunit), "1"))
		{
			sidx--;
			continue;
		}

		__get_wlifname(unit, sidx, wif);
		tweak_wifi_ps(wif);

#ifdef RTCONFIG_WIRELESSREPEATER
		if(nvram_get_int("sw_mode") == SW_MODE_REPEATER)
			doSystem("iwpriv %s athnewind 1", wif);
#endif

		sprintf(path2, "/etc/Wireless/sh/postwifi_%s.sh", wif);
		if (!(fp = fopen(path2, "a")))
			continue;

		/* hostapd is not required if
		 * 1. Open system and WPS is disabled.
		 *    a. primary 2G/5G and WPS is disabled
		 *    b. guest 2G/5G
		 * 2. WEP
		 */
		if (!strcmp(nvram_safe_get(wl_nvname("auth_mode_x", unit, sunit)), "open") &&
		    ((!sunit && !nvram_get_int("wps_enable")) || sunit)) {
			fclose(fp);
			continue;
		} else if (!strcmp(nvram_safe_get(wl_nvname("auth_mode_x", unit, sunit)), "shared")) {
			fclose(fp);
			continue;
		}

		sprintf(conf_path, "/etc/Wireless/conf/hostapd_%s.conf", wif);
		sprintf(pid_path, "/var/run/hostapd_%s.pid", wif);
		sprintf(entropy_path, "/var/run/entropy_%s.bin", wif);
		fprintf(fp, "hostapd -d -B %s -P %s -e %s\n", conf_path, pid_path, entropy_path);

		str = nvram_safe_get(wl_nvname("radio", unit, 0));
		if (str && strlen(str)) {
			char vphy[10];
			char *updown = atoi(str)? "up" : "down";
			strcpy(vphy, get_vphyifname(unit));
			fprintf(fp, "ifconfig %s %s\n", vphy, updown);
			fprintf(fp, "ifconfig %s %s\n", wif, updown);

			/* Connect to peer WDS AP after VAP up */
			sprintf(path1, NAWDS_SH_FMT, wif);
			if (!sunit && atoi(str) && f_exists(path1)) {
				fprintf(fp, "%s\n", path1);
			}
		}

		fclose(fp);
	}

	argv[1]="4";
	_eval(argv, NULL, 0, &pid);
	//system("/tmp/postwifi.sh");
	//sleep(1);
#ifdef RTCONFIG_PROXYSTA
	}
