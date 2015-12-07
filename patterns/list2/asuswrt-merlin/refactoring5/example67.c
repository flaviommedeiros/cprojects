#ifdef RTCONFIG_USB_MODEM
if(dualwan_unit__usbif(wan_unit)){
				if(link_wan[wan_unit]){
					if(sim_lock){
						sim_lock = 0;
						record_wan_state_nvram(wan_unit, WAN_STATE_INITIALIZING, WAN_STOPPED_REASON_NONE, WAN_AUXSTATE_NONE);
					}

					csprintf("wanduck(%d): PHY_RECONN.\n", wan_unit);
					return PHY_RECONN;
				}
				else{
					record_wan_state_nvram(wan_unit, WAN_STATE_STOPPED, -1, WAN_AUXSTATE_NOPHY);
					csprintf("wanduck(%d): SIM or modem is pulled off.\n", wan_unit);
					return DISCONN;
				}
			}
			else
#endif
			// WAN port was disconnected, arm reconnect
			if(!link_setup[wan_unit] && !link_wan[wan_unit]){
				link_setup[wan_unit] = 1;
			}
			// WAN port was connected, fire reconnect if armed
			else if(link_setup[wan_unit]){
				link_setup[wan_unit] = 0;

				// Only handle this case when WAN proto is DHCP or Static
				if(!strcmp(wan_proto, "static")){
					disconn_case[wan_unit] = CASE_DISWAN;
					return PHY_RECONN;
				}
				else if(!strcmp(wan_proto, "dhcp")){
					disconn_case[wan_unit] = CASE_DHCPFAIL;
					return PHY_RECONN;
				}
			}
