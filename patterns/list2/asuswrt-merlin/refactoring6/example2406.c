if(
#ifdef RTCONFIG_DUALWAN
			strcmp(dualwan_mode, "lb") &&
#endif
			!found_default_route(wan_unit)
			)
		link_internet = DISCONN;
#ifndef NO_DETECT_INTERNET
	else if(!get_packets_of_net_dev(wan_ifname, &rx_packets, &tx_packets) || rx_packets <= RX_THRESHOLD)
		link_internet = DISCONN;
	else if(!isFirstUse && (!do_dns_detect() && !do_tcp_dns_detect(wan_unit) && !do_ping_detect(wan_unit)))
		link_internet = DISCONN;
#endif
#ifdef RTCONFIG_DUALWAN
	else if((!strcmp(dualwan_mode, "fo") || !strcmp(dualwan_mode, "fb"))
			&& wandog_enable == 1 && !isFirstUse && !do_ping_detect(wan_unit))
		link_internet = DISCONN;
#endif
	else
		link_internet = CONNED;
