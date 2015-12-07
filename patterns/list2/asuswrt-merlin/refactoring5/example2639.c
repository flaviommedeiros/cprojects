#ifdef RTCONFIG_WIRELESSREPEATER
if(nvram_get_int("sw_mode") == SW_MODE_REPEATER && nvram_get_int("wlc_state") != WLC_STATE_CONNECTED)
		fprintf(fp, "nameserver %s\n", nvram_default_get("lan_ipaddr"));
	else
#endif
	{
		foreach(word, lan_dns, next) {
			if (!strcmp(word, lan_gateway))
				dup_dns = 1;
			fprintf(fp, "nameserver %s\n", word);
		}
	}
