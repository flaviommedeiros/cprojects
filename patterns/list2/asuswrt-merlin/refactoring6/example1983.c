if (connflag
#ifdef RTCONFIG_WIRELESSREPEATER
			&& nvram_get_int("sw_mode")!=SW_MODE_REPEATER
#endif
	) {
		p = nvram_safe_get("ct_udp_timeout");
		if (sscanf(p, "%u%u", &v[0], &v[1]) == 2) {
			write_udp_timeout(NULL, v[0]);
			write_udp_timeout("stream", v[1]);
		}
		else {
			v[0] = read_udp_timeout(NULL);
			v[1] = read_udp_timeout("stream");
			sprintf(buf, "%u %u", v[0], v[1]);
			nvram_set("ct_udp_timeout", buf);
		}
	}
	else {
		write_udp_timeout(NULL, 1);
		write_udp_timeout("stream", 6);
	}
