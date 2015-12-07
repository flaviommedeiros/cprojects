if (
		(is_routing_enabled() && nvram_get_int("dhcp_enable_x"))
#ifdef RTCONFIG_WIRELESSREPEATER
	 || (nvram_get_int("sw_mode") == SW_MODE_REPEATER && nvram_get_int("wlc_state") != WLC_STATE_CONNECTED)
#endif
	) {
		char *dhcp_start, *dhcp_end;
		int dhcp_lease;
		char buffer[64];
#if defined(RTCONFIG_TR069) && !defined(RTCONFIG_TR181)
		unsigned char hwaddr[6];
#endif

		have_dhcp |= 1; /* DHCPv4 */

		get_dhcp_pool(&dhcp_start, &dhcp_end, buffer);
#ifdef RTCONFIG_WIRELESSREPEATER
		if(nvram_get_int("sw_mode") == SW_MODE_REPEATER && nvram_get_int("wlc_state") != WLC_STATE_CONNECTED){
			dhcp_lease = atoi(nvram_default_get("dhcp_lease"));
		}
		else
#endif
		{
			dhcp_lease = nvram_get_int("dhcp_lease");
		}

		if (dhcp_lease <= 0)
			dhcp_lease = 86400;

		/* LAN range */
		if (*dhcp_start && *dhcp_end) {
			fprintf(fp, "dhcp-range=lan,%s,%s,%s,%ds\n",
				dhcp_start, dhcp_end, nvram_safe_get("lan_netmask"), dhcp_lease);
		} else {
			/* compatibility */
			char lan[24];
			int start = nvram_get_int("dhcp_start");
			int count = nvram_get_int("dhcp_num");

			strlcpy(lan, lan_ipaddr, sizeof(lan));
			if ((value = strrchr(lan, '.')) != NULL) *(value + 1) = 0;

			fprintf(fp, "dhcp-range=lan,%s%d,%s%d,%s,%ds\n",
				lan, start, lan, start + count - 1, nvram_safe_get("lan_netmask"), dhcp_lease);
		}

		/* Gateway, if not set, force use lan ipaddr to avoid repeater issue */
		value = nvram_safe_get("dhcp_gateway_x");
		value = (*value && inet_addr(value)) ? value : lan_ipaddr;
		fprintf(fp, "dhcp-option=lan,3,%s\n", value);

		/* DNS server and additional router address */
		value = nvram_safe_get("dhcp_dns1_x");
		if (*value && inet_addr(value)) {
			char *value2;

			value2 = nvram_safe_get("dhcp_dns2_x");
			fprintf(fp, "dhcp-option=lan,6,%s%s%s%s\n",
				     value,
				     (*value2 && inet_addr(value2) ? "," : ""),
				     (*value2 && inet_addr(value2) ? value2 : ""),
				     (nvram_match("dhcpd_dns_router","1") ? ",0.0.0.0" : ""));
		}

		/* LAN Domain */
		value = nvram_safe_get("lan_domain");
		if (*value)
			fprintf(fp, "dhcp-option=lan,15,%s\n", value);

		/* WINS server */
		value = nvram_safe_get("dhcp_wins_x");
		if (*value && inet_addr(value)) {
			fprintf(fp, "dhcp-option=lan,44,%s\n"
			/*	    "dhcp-option=lan,46,8\n"*/, value);
		}
#ifdef RTCONFIG_SAMBASRV
		/* Samba will serve as a WINS server */
		else if (nvram_invmatch("lan_domain", "") && nvram_get_int("smbd_wins")) {
			fprintf(fp, "dhcp-option=lan,44,%s\n"
			/*	    "dhcp-option=lan,46,8\n"*/, lan_ipaddr);
		}
#endif
		/* Shut up WPAD info requests */
		fprintf(fp, "dhcp-option=lan,252,\"\\n\"\n");

#if defined(RTCONFIG_TR069) && !defined(RTCONFIG_TR181)
		if (ether_atoe(get_lan_hwaddr(), hwaddr)) {
			snprintf(buffer, sizeof(buffer), "%02X%02X%02X", hwaddr[0], hwaddr[1], hwaddr[2]);
			fprintf(fp, "dhcp-option-force=cpewan-id,vi-encap:%d,%d,\"%s\"\n",
				3561, 4, buffer);
			snprintf(buffer, sizeof(buffer), "%02X%02X%02X%02X%02X%02X",
				 hwaddr[0], hwaddr[1], hwaddr[2], hwaddr[3], hwaddr[4], hwaddr[5]);
			fprintf(fp, "dhcp-option-force=cpewan-id,vi-encap:%d,%d,\"%s\"\n",
				3561, 5, buffer);
			fprintf(fp, "dhcp-option-force=cpewan-id,vi-encap:%d,%d,\"%s\"\n",
				3561, 6, nvram_safe_get("productid"));
		}
#endif
	}
