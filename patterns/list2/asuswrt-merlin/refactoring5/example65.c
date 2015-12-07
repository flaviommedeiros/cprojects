#ifdef RTCONFIG_WIRELESSREPEATER
if(sw_mode == SW_MODE_REPEATER){
			csprintf("# wanduck:   ipaddr=%s.\n", current_lan_ipaddr);
			csprintf("# wanduck:wlc_state=%d.\n", wlc_state);
		}
		else
#endif
		{
			csprintf("# wanduck:   ifname=%s.\n", current_lan_ifname);
			csprintf("# wanduck:    proto=%s.\n", current_lan_proto);
			csprintf("# wanduck:   ipaddr=%s.\n", current_lan_ipaddr);
			csprintf("# wanduck:  netmask=%s.\n", current_lan_netmask);
			csprintf("# wanduck:  gateway=%s.\n", current_lan_gateway);
			csprintf("# wanduck:      dns=%s.\n", current_lan_dns);
			csprintf("# wanduck:   subnet=%s.\n", current_lan_subnet);
		}
