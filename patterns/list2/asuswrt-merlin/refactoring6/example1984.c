if (connflag
#ifdef RTCONFIG_WIRELESSREPEATER
			&& nvram_get_int("sw_mode")!=SW_MODE_REPEATER
#endif
	) {
		p = nvram_safe_get("ct_timeout");
		if (sscanf(p, "%u%u", &v[0], &v[1]) == 2) {
//			write_ct_timeout("generic", NULL, v[0]);
			write_ct_timeout("icmp", NULL, v[1]);
		}
		else {
			v[0] = read_ct_timeout("generic", NULL);
			v[1] = read_ct_timeout("icmp", NULL);

			sprintf(buf, "%u %u", v[0], v[1]);
			nvram_set("ct_timeout", buf);
		}
	}
	else {
		for (i = 0; i < 3; i++)
		{
			if (scan_icmp_unreplied_conntrack() > 0)
			{
//				write_ct_timeout("generic", NULL, 0);
				write_ct_timeout("icmp", NULL, 0);
				sleep(2);
			}
		}
	}
