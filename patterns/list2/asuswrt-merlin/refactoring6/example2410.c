if(sw_mode == SW_MODE_ROUTER
#ifdef RTCONFIG_WIRELESSREPEATER
				|| sw_mode == SW_MODE_HOTSPOT
#endif
				){
			// To check the phy connection of the standby line. 
			for(wan_unit = WAN_UNIT_FIRST; wan_unit < WAN_UNIT_MAX; ++wan_unit)
				conn_state[wan_unit] = if_wan_phyconnected(wan_unit);

			current_wan_unit = wan_primary_ifunit();
			other_wan_unit = get_next_unit(current_wan_unit);

			current_state[current_wan_unit] = nvram_get_int(nvram_state[current_wan_unit]);

			if(current_state[current_wan_unit] == WAN_STATE_DISABLED){
				//record_wan_state_nvram(current_wan_unit, WAN_STATE_STOPPED, WAN_STOPPED_REASON_MANUAL, -1);
				update_wan_leds(current_wan_unit);

				disconn_case[current_wan_unit] = CASE_OTHERS;
				conn_state[current_wan_unit] = DISCONN;
				set_disconn_count(current_wan_unit, S_IDLE);
			}
#ifdef RTCONFIG_USB_MODEM
			else if(dualwan_unit__usbif(current_wan_unit)
					&& (modem_act_reset == 1 || modem_act_reset == 2)
					){
_dprintf("wanduck(%d): detect the modem to be reset...\n", current_wan_unit);
				disconn_case[current_wan_unit] = CASE_OTHERS;
				conn_state[current_wan_unit] = DISCONN;
				set_disconn_count(current_wan_unit, S_IDLE);
			}
#endif
			else{
#if !defined(RTN14U) && !defined(RTAC1200GP)			  
				conn_state[current_wan_unit] = if_wan_phyconnected(current_wan_unit);
#endif				
				if(conn_state[current_wan_unit] == CONNED){
#ifdef RTCONFIG_USB_MODEM
					if(!(dualwan_unit__usbif(current_wan_unit) && current_state[current_wan_unit] == WAN_STATE_INITIALIZING))
#endif
						conn_state[current_wan_unit] = if_wan_connected(current_wan_unit, current_state[current_wan_unit]);
				}
			}

			if(conn_state[current_wan_unit] == PHY_RECONN){
				conn_changed_state[current_wan_unit] = PHY_RECONN;

				conn_state_old[current_wan_unit] = DISCONN;

				// When the current line is re-plugged and the other line has plugged, the count has to be reset.
				if(link_wan[other_wan_unit]){
					csprintf("# wanduck: set S_COUNT: PHY_RECONN.\n");
					set_disconn_count(current_wan_unit, S_COUNT);
				}
			}
#ifdef RTCONFIG_USB_MODEM
			else if(conn_state[current_wan_unit] == SET_PIN){
				conn_changed_state[current_wan_unit] = SET_PIN;

				conn_state_old[current_wan_unit] = DISCONN;
				// The USB modem needs the PIN code to unlock.
				set_disconn_count(current_wan_unit, S_IDLE);
			}
			else if(conn_state[current_wan_unit] == SET_USBSCAN){
				conn_changed_state[current_wan_unit] = C2D;

				conn_state_old[current_wan_unit] = DISCONN;
				// The USB modem is scanning the stations.
				set_disconn_count(current_wan_unit, S_IDLE);
			}
#if (defined(RTCONFIG_JFFS2) || defined(RTCONFIG_BRCM_NAND_JFFS2) || defined(RTCONFIG_UBIFS))
			else if(dualwan_unit__usbif(current_wan_unit) && nvram_get_int(nvram_sbstate[current_wan_unit]) == WAN_STOPPED_REASON_DATALIMIT){
				if(conn_state_old[current_wan_unit] == CONNED){
					csprintf("wanduck(usb): detect the data limit.\n");
					conn_changed_state[current_wan_unit] = C2D;
				}
				else
					conn_changed_state[current_wan_unit] = DISCONN;

				conn_state_old[current_wan_unit] = DISCONN;
				set_disconn_count(current_wan_unit, max_disconn_count[current_wan_unit]);
			}
#endif
#endif
			else if(conn_state[current_wan_unit] == CONNED){
				if(conn_state_old[current_wan_unit] == DISCONN)
					conn_changed_state[current_wan_unit] = D2C;
				else
					conn_changed_state[current_wan_unit] = CONNED;

				conn_state_old[current_wan_unit] = conn_state[current_wan_unit];

#ifdef RTCONFIG_DSL /* Paul add 2013/7/29, for Non-DualWAN 3G/4G WAN -> DSL WAN, auto Fail-Back feature */
				if (nvram_match("dsltmp_adslsyncsts","up") && current_wan_unit == WAN_UNIT_SECOND){
					csprintf("\n# wanduck: adslsync up.\n");
					set_disconn_count(current_wan_unit, S_IDLE);
					link_wan[current_wan_unit] = DISCONN;
					conn_state[current_wan_unit] = DISCONN;
					usb_switched_back_dsl = 1;
					max_disconn_count[current_wan_unit] = 1;
				}
				else
					set_disconn_count(current_wan_unit, S_IDLE);
#else
				set_disconn_count(current_wan_unit, S_IDLE);
#endif
			}
			else if(conn_state[current_wan_unit] == DISCONN){
				if(conn_state_old[current_wan_unit] == CONNED)
					conn_changed_state[current_wan_unit] = C2D;
				else
					conn_changed_state[current_wan_unit] = DISCONN;

				conn_state_old[current_wan_unit] = conn_state[current_wan_unit];

				if(disconn_case[current_wan_unit] == CASE_THESAMESUBNET){
					csprintf("# wanduck: set S_IDLE: CASE_THESAMESUBNET.\n");
					set_disconn_count(current_wan_unit, S_IDLE);
				}
#ifdef RTCONFIG_USB_MODEM
				// when the other line is modem and not plugged, the current disconnected line would not count.
				else if(!link_wan[other_wan_unit] && dualwan_unit__usbif(other_wan_unit))
					set_disconn_count(current_wan_unit, S_IDLE);
				else if(get_disconn_count(current_wan_unit) == S_IDLE && current_state[current_wan_unit] != WAN_STATE_DISABLED)
					set_disconn_count(current_wan_unit, S_COUNT);
#else
				else
					set_disconn_count(current_wan_unit, S_IDLE);
#endif
			}

			if(get_disconn_count(current_wan_unit) != S_IDLE){
				if(get_disconn_count(current_wan_unit) < max_disconn_count[current_wan_unit]){
					set_disconn_count(current_wan_unit, get_disconn_count(current_wan_unit)+1);
					csprintf("# wanduck(%d): wait time for switching: %d/%d.\n", current_wan_unit, get_disconn_count(current_wan_unit)*scan_interval, max_wait_time[current_wan_unit]);
				}
				else{
					csprintf("# wanduck(%d): set S_COUNT: changed_count[] >= max_disconn_count.\n", current_wan_unit);
					set_disconn_count(current_wan_unit, S_COUNT);
				}
			}

			record_conn_status(current_wan_unit);
		}
		else{ // sw_mode == SW_MODE_AP, SW_MODE_REPEATER.
			current_wan_unit = WAN_UNIT_FIRST;
			conn_state[current_wan_unit] = if_wan_phyconnected(current_wan_unit);

			if(conn_state[current_wan_unit] == DISCONN){
				if(conn_state_old[current_wan_unit] == CONNED)
					conn_changed_state[current_wan_unit] = C2D;
				else
					conn_changed_state[current_wan_unit] = DISCONN;
			}
			else{
				if(conn_state_old[current_wan_unit] == DISCONN)
					conn_changed_state[current_wan_unit] = D2C;
				else
					conn_changed_state[current_wan_unit] = CONNED;
			}

			conn_state_old[current_wan_unit] = conn_state[current_wan_unit];
		}
