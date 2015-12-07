#ifdef RTCONFIG_WIRELESSREPEATER
if(nvram_get_int("sw_mode") == SW_MODE_REPEATER && nvram_get_int("wlc_state") != WLC_STATE_CONNECTED){
		if(nvram_match("lan_proto", "static")) {
			in_addr_t lan_ipaddr, lan_netmask;
			char *p = buffer;
			unsigned char lan1[4], lan2[4];
			unsigned offset;

			inet_aton(nvram_safe_get("lan_ipaddr") , (struct in_addr*) &lan_ipaddr);
			inet_aton(nvram_safe_get("lan_netmask"), (struct in_addr*) &lan_netmask);
//			cprintf("#### lan_ipaddr(%08x) lan_netmask(%08x)\n", lan_ipaddr, lan_netmask);

			//start
			if ((ntohl(lan_ipaddr & lan_netmask) | 1 ) == ntohl(lan_ipaddr))
				offset = 2;
			else
				offset = 1;
			*(in_addr_t *) &lan1 = (lan_ipaddr & lan_netmask) | htonl(offset);
			*dhcp_start = p;
			p += sprintf(p, "%u.%u.%u.%u", lan1[0], lan1[1], lan1[2], lan1[3]);
			p += 1;

			//end
			if ((ntohl(lan_ipaddr & lan_netmask) | 254) == ntohl(lan_ipaddr))
				offset = 253;
			else
				offset = 254;
			*((in_addr_t *) &lan2) = (lan_ipaddr & lan_netmask) | htonl(offset);
			*dhcp_end = p;
			p += sprintf(p, "%u.%u.%u.%u", lan2[0], lan2[1], lan2[2], lan2[3]);
			p += 1;

//			cprintf("#### dhcp_start(%s) dhcp_end(%s)\n", *dhcp_start, *dhcp_end);
		} else {
			*dhcp_start = nvram_default_get("dhcp_start");
			*dhcp_end = nvram_default_get("dhcp_end");
		}
	}
	else
#endif
	{
		*dhcp_start = nvram_safe_get("dhcp_start");
		*dhcp_end = nvram_safe_get("dhcp_end");
	}
