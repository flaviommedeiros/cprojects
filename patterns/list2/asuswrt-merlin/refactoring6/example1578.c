if(sw_mode == SW_MODE_ROUTER
#ifdef RTCONFIG_WIRELESSREPEATER
			|| sw_mode == SW_MODE_HOTSPOT
#endif
			){
		current_wan_unit = wan_primary_ifunit();
		other_wan_unit = get_next_unit(current_wan_unit);

		conn_state[current_wan_unit] = if_wan_phyconnected(current_wan_unit);
		if(conn_state[current_wan_unit] == CONNED){
#ifdef RTCONFIG_USB_MODEM
			current_state[current_wan_unit] = nvram_get_int(nvram_state[current_wan_unit]);
			if(!(dualwan_unit__usbif(current_wan_unit) && current_state[current_wan_unit] == WAN_STATE_INITIALIZING))
#endif
				conn_state[current_wan_unit] = if_wan_connected(current_wan_unit, nvram_get_int(nvram_state[current_wan_unit]));

			cross_state = conn_state[current_wan_unit];
		}
		else
			cross_state = DISCONN;

		conn_changed_state[current_wan_unit] = conn_state[current_wan_unit];

		conn_state_old[current_wan_unit] = conn_state[current_wan_unit];

		record_conn_status(current_wan_unit);
	}
	else{ // sw_mode == SW_MODE_AP, SW_MODE_REPEATER.
		current_wan_unit = WAN_UNIT_FIRST;

		conn_state[current_wan_unit] = if_wan_phyconnected(current_wan_unit);

		cross_state = conn_state[current_wan_unit];

		conn_state_old[current_wan_unit] = conn_state[current_wan_unit];

#ifdef RTCONFIG_WIRELESSREPEATER
		if(sw_mode == SW_MODE_REPEATER)
			record_conn_status(current_wan_unit);
#endif

		if(sw_mode == SW_MODE_AP){
#ifdef RTCONFIG_REDIRECT_DNAME
			if(cross_state == DISCONN){
				csprintf("\n# AP mode: Enable direct rule(DISCONN)\n");
				eval("ebtables", "-t", "broute", "-F");
				eval("ebtables", "-t", "filter", "-F");
				redirect_setting();
				eval("iptables-restore", "/tmp/redirect_rules");
			}
			else if(cross_state == CONNED){
				csprintf("\n# AP mode: Disable direct rule(CONNED)\n");
				eval("ebtables", "-t", "broute", "-F");
				eval("ebtables", "-t", "filter", "-F");
				eval("ebtables", "-t", "broute", "-I", "BROUTING", "-p", "ipv4", "--ip-proto", "udp", "--ip-dport", "53", "-j", "redirect", "--redirect-target", "DROP");
				redirect_nat_setting();
				eval("iptables-restore", NAT_RULES);
			}

#endif

#ifdef RTCONFIG_RESTRICT_GUI
			if(cross_state == CONNED){
				if(nvram_get_int("fw_restrict_gui")){
					char word[PATH_MAX], *next_word;

					foreach(word, nvram_safe_get("lan_ifnames"), next_word){
						if(!strncmp(word, "vlan", 4))
							continue;

						eval("ebtables", "-t", "broute", "-I", "BROUTING", "-i", word, "-j", "mark", "--mark-set", BIT_RES_GUI, "--mark-target", "CONTINUE");
					}

					repeater_filter_setting(0);
				}
			}
#endif
		}
	}
