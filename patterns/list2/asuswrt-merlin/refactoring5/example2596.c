#ifdef WEB_REDIRECT
if(nvram_get_int("freeze_duck"))
		_dprintf("\n<*>freeze the duck, %ds left!\n", nvram_get_int("freeze_duck"));	// don't check conn state during inner events period
	else
#endif
	if(sw_mode == SW_MODE_ROUTER && !strcmp(dualwan_mode, "lb")){
		cross_state = DISCONN;
		for(wan_unit = WAN_UNIT_FIRST; wan_unit < WAN_UNIT_MAX; ++wan_unit){
			conn_state[wan_unit] = if_wan_phyconnected(wan_unit);
			if(conn_state[wan_unit] == CONNED){
#ifdef RTCONFIG_USB_MODEM
				current_state[wan_unit] = nvram_get_int(nvram_state[wan_unit]);
				if(!(dualwan_unit__usbif(wan_unit) && current_state[wan_unit] == WAN_STATE_INITIALIZING))
#endif
					conn_state[wan_unit] = if_wan_connected(wan_unit, nvram_get_int(nvram_state[wan_unit]));
			}
			else
				conn_state[wan_unit] = DISCONN;

			conn_changed_state[wan_unit] = conn_state[wan_unit];

			if(conn_state[wan_unit] == CONNED && cross_state != CONNED)
				cross_state = CONNED;

			conn_state_old[wan_unit] = conn_state[wan_unit];

			record_conn_status(wan_unit);

			if(cross_state == CONNED)
				set_disconn_count(wan_unit, S_IDLE);
			else
				set_disconn_count(wan_unit, S_COUNT);
		}
	}
	else if(sw_mode == SW_MODE_ROUTER
			&& (!strcmp(dualwan_mode, "fo") || !strcmp(dualwan_mode, "fb"))
			){
		if(wandog_delay > 0){
			csprintf("wanduck: delay %d seconds...\n", wandog_delay);
			sleep(wandog_delay);
			delay_detect = 0;
		}

		// To check the phy connection of the standby line. 
		for(wan_unit = WAN_UNIT_FIRST; wan_unit < WAN_UNIT_MAX; ++wan_unit){
			if(get_dualwan_by_unit(wan_unit) != WANS_DUALWAN_IF_NONE)
				conn_state[wan_unit] = if_wan_phyconnected(wan_unit);
		}

		current_wan_unit = wan_primary_ifunit();
		other_wan_unit = get_next_unit(current_wan_unit);
if(test_log)
_dprintf("wanduck(%d)(first detect start): state %d, state_old %d, changed %d, wan_state %d.\n"
		, current_wan_unit, conn_state[current_wan_unit], conn_state_old[current_wan_unit], conn_changed_state[current_wan_unit], current_state[current_wan_unit]);

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
	else
#endif // RTCONFIG_DUALWAN
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
