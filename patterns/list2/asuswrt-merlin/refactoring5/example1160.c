#ifdef RTCONFIG_WIRELESSREPEATER
if (sw_mode == SW_MODE_REPEATER && wlc_band == band)
	{
		ssid_num = 1;
		fprintf(fp, "BssidNum=%d\n", ssid_num);
		if(band == 0)
			sprintf(tmpstr, "SSID1=%s\n",  nvram_safe_get("wl0.1_ssid"));
		else
			sprintf(tmpstr, "SSID1=%s\n",  nvram_safe_get("wl1.1_ssid"));
		fprintf(fp, "%s", tmpstr);
	}
	else
#endif	/* RTCONFIG_WIRELESSREPEATER */
	{   
		fprintf(fp, "BssidNum=%d\n", ssid_num);
		//SSID
		for (i = 0, j = 0; i < MAX_NO_MSSID; i++)
		{
			if (i)
			{
				sprintf(prefix_mssid, "wl%d.%d_", band, i);
				if (!nvram_match(strcat_r(prefix_mssid, "bss_enabled", temp), "1"))
					continue;
				else
					j++;
			}
			else
				sprintf(prefix_mssid, "wl%d_", band);

			if (strlen(nvram_safe_get(strcat_r(prefix_mssid, "ssid", temp))))
				sprintf(tmpstr, "SSID%d=%s\n", j + 1, nvram_safe_get(strcat_r(prefix_mssid, "ssid", temp)));
			else
			{
				warning = 5;
				sprintf(tmpstr, "SSID%d=%s%d\n", j + 1, "ASUS", j + 1);
			}
			fprintf(fp, "%s", tmpstr);
		}
	}
