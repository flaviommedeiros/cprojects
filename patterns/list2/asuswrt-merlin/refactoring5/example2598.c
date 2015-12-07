#ifdef WEB_REDIRECT
if(nvram_get_int("freeze_duck")){
			_dprintf("\n<****>freeze the duck, %ds left!\n", nvram_get_int("freeze_duck"));	// don't check conn state during inner events period
			goto WANDUCK_SELECT;
		}
		else
#endif
#ifdef RTCONFIG_DUALWAN
		if(sw_mode == SW_MODE_ROUTER && !strcmp(dualwan_mode, "lb")){
			cross_state = DISCONN;
			for(wan_unit = WAN_UNIT_FIRST; wan_unit < WAN_UNIT_MAX; ++wan_unit){
#if 0
#ifdef RTCONFIG_USB_MODEM
				if(dualwan_unit__usbif(wan_unit) && !link_wan[wan_unit]){
					if_wan_phyconnected(wan_unit);
					continue;
				}
#endif
#endif

				current_state[wan_unit] = nvram_get_int(nvram_state[wan_unit]);

				if(current_state[wan_unit] == WAN_STATE_DISABLED){
					//record_wan_state_nvram(wan_unit, WAN_STATE_STOPPED, WAN_STOPPED_REASON_MANUAL, -1);

					disconn_case[wan_unit] = CASE_OTHERS;
					conn_state[wan_unit] = DISCONN;
				}
#ifdef RTCONFIG_USB_MODEM
				else if(dualwan_unit__usbif(wan_unit)
						&& (modem_act_reset == 1 || modem_act_reset == 2)
						){
_dprintf("wanduck(%d): detect the modem to be reset...\n", wan_unit);
					disconn_case[wan_unit] = CASE_OTHERS;
					conn_state[wan_unit] = DISCONN;
					set_disconn_count(wan_unit, S_IDLE);
				}
#endif
				else{
					conn_state[wan_unit] = if_wan_phyconnected(wan_unit);
					if(conn_state[wan_unit] == CONNED){
#ifdef RTCONFIG_USB_MODEM
						if(!(dualwan_unit__usbif(wan_unit) && current_state[wan_unit] == WAN_STATE_INITIALIZING))
#endif
							conn_state[wan_unit] = if_wan_connected(wan_unit, current_state[wan_unit]);
					}
				}

				if(conn_state[wan_unit] == CONNED && cross_state != CONNED)
					cross_state = CONNED;

#ifdef RTCONFIG_USB_MODEM
				if(dualwan_unit__usbif(wan_unit)){
					if(link_wan[wan_unit] == 1 && current_state[wan_unit] == WAN_STATE_INITIALIZING && boot_end == 1){
						csprintf("wanduck: start_wan_if %d.\n", wan_unit);
						snprintf(cmd, 32, "start_wan_if %d", wan_unit);
						notify_rc(cmd);
						continue;
					}
					else if(!link_wan[wan_unit] && current_state[wan_unit] != WAN_STATE_INITIALIZING){
						csprintf("wanduck2: stop_wan_if %d.\n", wan_unit);
						snprintf(cmd, 32, "stop_wan_if %d", wan_unit);
						notify_rc(cmd);
						continue;
					}
				}

				if(conn_state[wan_unit] == SET_PIN){
					conn_changed_state[wan_unit] = SET_PIN;
					set_disconn_count(wan_unit, S_IDLE);
				}
				else if(conn_state[wan_unit] == SET_USBSCAN){
					conn_changed_state[wan_unit] = SET_USBSCAN;
					set_disconn_count(wan_unit, S_IDLE);
				}
				else
#if (defined(RTCONFIG_JFFS2) || defined(RTCONFIG_BRCM_NAND_JFFS2) || defined(RTCONFIG_UBIFS))
				if(dualwan_unit__usbif(wan_unit) && nvram_get_int(nvram_sbstate[wan_unit]) == WAN_STOPPED_REASON_DATALIMIT){
					csprintf("wanduck(%d)(lb): detect the data limit.\n", wan_unit);
					conn_changed_state[wan_unit] = C2D;
					set_disconn_count(wan_unit, max_disconn_count[wan_unit]);
				}
				else
#endif
#endif
				if(conn_state[wan_unit] != conn_state_old[wan_unit]){
					if(conn_state[wan_unit] == PHY_RECONN){
						conn_changed_state[wan_unit] = PHY_RECONN;
					}
					else if(conn_state[wan_unit] == DISCONN){
						conn_changed_state[wan_unit] = C2D;

#ifdef RTCONFIG_USB_MODEM
						if (dualwan_unit__usbif(wan_unit))
							set_disconn_count(wan_unit, max_disconn_count[wan_unit]);
						else
#endif
							set_disconn_count(wan_unit, S_COUNT);
					}
					else if(conn_state[wan_unit] == CONNED){
						conn_changed_state[wan_unit] = D2C;
						set_disconn_count(wan_unit, S_IDLE);
					}
					else
						conn_changed_state[wan_unit] = CONNED;

					conn_state_old[wan_unit] = conn_state[wan_unit];

					record_conn_status(wan_unit);
				}

				if(get_disconn_count(wan_unit) != S_IDLE){
					if(conn_state[wan_unit] == PHY_RECONN)
						set_disconn_count(wan_unit, max_disconn_count[wan_unit]);

					if(get_disconn_count(wan_unit) >= max_disconn_count[wan_unit]){
						set_disconn_count(wan_unit, S_IDLE);

#ifdef RTCONFIG_USB_MODEM
						csprintf("\n# wanduck(usb): type=%s.\n", modem_type);
						if(dualwan_unit__usbif(wan_unit) &&
								(!strcmp(modem_type, "ecm") || !strcmp(modem_type, "ncm") || !strcmp(modem_type, "rndis") || !strcmp(modem_type, "asix") || !strcmp(modem_type, "qmi") || !strcmp(modem_type, "gobi"))
								){
							csprintf("\n# wanduck(usb): skip to run restart_wan_if %d.\n", wan_unit);
							if(!link_wan[wan_unit] && strlen(modem_type) > 0)
								memset(modem_type, 0, 32);		
						}
						else
#endif
						{
							csprintf("\n# wanduck(%d): run restart_wan_if.\n", wan_unit);
							memset(cmd, 0, 32);
							sprintf(cmd, "restart_wan_if %d", wan_unit);
							notify_rc_and_period_wait(cmd, 30);
						}

						if(get_wan_state(get_next_unit(wan_unit)) == WAN_STATE_CONNECTED){
							memset(cmd, 0, 32);
							sprintf(cmd, "restart_wan_line %d", get_next_unit(wan_unit));
							notify_rc(cmd);
						}
					}
					else
						set_disconn_count(wan_unit, get_disconn_count(wan_unit)+1);

					csprintf("%s: wan(%d) disconn count = %d/%d ...\n", __FUNCTION__, wan_unit, get_disconn_count(wan_unit), max_disconn_count[wan_unit]);
				}
			}
if(test_log)
_dprintf("wanduck(%d)(lb change): state %d, state_old %d, changed %d, cross_state=%d, wan_state %d.\n"
		, current_wan_unit, conn_state[current_wan_unit], conn_state_old[current_wan_unit], conn_changed_state[current_wan_unit], cross_state, current_state[current_wan_unit]);
		}
		else if(sw_mode == SW_MODE_ROUTER && !strcmp(dualwan_mode, "fo")){
			if(delay_detect == 1 && wandog_delay > 0){
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

			current_state[current_wan_unit] = nvram_get_int(nvram_state[current_wan_unit]);
if(test_log)
_dprintf("wanduck(%d)(fo    phy): state %d, state_old %d, changed %d, wan_state %d.\n"
		, current_wan_unit, conn_state[current_wan_unit], conn_state_old[current_wan_unit], conn_changed_state[current_wan_unit], current_state[current_wan_unit]);

			if(current_state[current_wan_unit] == WAN_STATE_DISABLED){
				//record_wan_state_nvram(current_wan_unit, WAN_STATE_STOPPED, WAN_STOPPED_REASON_MANUAL, -1);

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
				if(conn_state[current_wan_unit] == CONNED){
#ifdef RTCONFIG_USB_MODEM
					if(!(dualwan_unit__usbif(current_wan_unit) && current_state[current_wan_unit] == WAN_STATE_INITIALIZING))
#endif
						conn_state[current_wan_unit] = if_wan_connected(current_wan_unit, current_state[current_wan_unit]);
if(test_log)
_dprintf("wanduck(%d)(fo   conn): state %d, state_old %d, changed %d, wan_state %d.\n"
		, current_wan_unit, conn_state[current_wan_unit], conn_state_old[current_wan_unit], conn_changed_state[current_wan_unit], current_state[current_wan_unit]);
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
					csprintf("wanduck(%d)(fo): detect the data limit.\n", current_wan_unit);
					conn_changed_state[current_wan_unit] = C2D;
				}
				else
					conn_changed_state[current_wan_unit] = DISCONN;

				conn_state_old[current_wan_unit] = DISCONN;
				//set_disconn_count(current_wan_unit, max_disconn_count[current_wan_unit]);
				set_disconn_count(current_wan_unit, S_IDLE);
			}
#endif
#endif
			else if(conn_state[current_wan_unit] == CONNED){
				if(conn_state_old[current_wan_unit] == DISCONN)
					conn_changed_state[current_wan_unit] = D2C;
				else
					conn_changed_state[current_wan_unit] = CONNED;

				conn_state_old[current_wan_unit] = conn_state[current_wan_unit];
				set_disconn_count(current_wan_unit, S_IDLE);
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
#endif
				else if(get_disconn_count(current_wan_unit) == S_IDLE && current_state[current_wan_unit] != WAN_STATE_DISABLED
						&& get_dualwan_by_unit(other_wan_unit) != WANS_DUALWAN_IF_NONE
						)
					set_disconn_count(current_wan_unit, S_COUNT);
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
if(test_log)
_dprintf("wanduck(%d)(fo change): state %d, state_old %d, changed %d, wan_state %d.\n"
		, current_wan_unit, conn_state[current_wan_unit], conn_state_old[current_wan_unit], conn_changed_state[current_wan_unit], current_state[current_wan_unit]);
		}
		else if(sw_mode == SW_MODE_ROUTER && !strcmp(dualwan_mode, "fb")){
			if(delay_detect == 1 && wandog_delay > 0){
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

			current_state[current_wan_unit] = nvram_get_int(nvram_state[current_wan_unit]);

			if(current_state[current_wan_unit] == WAN_STATE_DISABLED){
				//record_wan_state_nvram(current_wan_unit, WAN_STATE_STOPPED, WAN_STOPPED_REASON_MANUAL, -1);

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
				if(conn_state[current_wan_unit] == CONNED){
#ifdef RTCONFIG_USB_MODEM
					if(!(dualwan_unit__usbif(current_wan_unit) && current_state[current_wan_unit] == WAN_STATE_INITIALIZING))
#endif
						conn_state[current_wan_unit] = if_wan_connected(current_wan_unit, current_state[current_wan_unit]);
				}

				if(other_wan_unit == WAN_FB_UNIT && conn_state[other_wan_unit] == CONNED){
					current_state[other_wan_unit] = nvram_get_int(nvram_state[other_wan_unit]);
#ifdef RTCONFIG_USB_MODEM
					if(!(dualwan_unit__usbif(other_wan_unit) && current_state[other_wan_unit] == WAN_STATE_INITIALIZING))
#endif
						conn_state[other_wan_unit] = if_wan_connected(other_wan_unit, current_state[other_wan_unit]);
					csprintf("wanduck: detect the fail-back line(%d)...\n", other_wan_unit);
if(test_log)
_dprintf("wanduck(%d) fail-back: state %d, state_old %d, changed %d, wan_state %d.\n"
		, other_wan_unit, conn_state[other_wan_unit], conn_state_old[other_wan_unit], conn_changed_state[other_wan_unit], current_state[other_wan_unit]);
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
					csprintf("wanduck(%d)(fb): detect the data limit.\n", current_wan_unit);
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
				set_disconn_count(current_wan_unit, S_IDLE);
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
#endif
				else if(get_disconn_count(current_wan_unit) == S_IDLE && current_state[current_wan_unit] != WAN_STATE_DISABLED
						&& get_dualwan_by_unit(other_wan_unit) != WANS_DUALWAN_IF_NONE
						)
					set_disconn_count(current_wan_unit, S_COUNT);
			}

			if(other_wan_unit == WAN_FB_UNIT){
				if(conn_state[other_wan_unit] == CONNED
						&& get_disconn_count(other_wan_unit) == S_IDLE
						)
					set_disconn_count(other_wan_unit, S_COUNT);
				else if(conn_state[other_wan_unit] == DISCONN)
					set_disconn_count(other_wan_unit, S_IDLE);
			}
			else
				set_disconn_count(other_wan_unit, S_IDLE);

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

			if(get_disconn_count(other_wan_unit) != S_IDLE){
				if(get_disconn_count(other_wan_unit) < max_fb_count){
					set_disconn_count(other_wan_unit, get_disconn_count(other_wan_unit)+1);
					csprintf("# wanduck: wait time for returning: %d/%d.\n", get_disconn_count(other_wan_unit)*scan_interval, max_fb_wait_time);
				}
				else{
					csprintf("# wanduck: set S_COUNT: changed_count[] >= max_fb_count.\n");
					set_disconn_count(other_wan_unit, S_COUNT);
				}
			}

			record_conn_status(current_wan_unit);
		}
		else
#endif // RTCONFIG_DUALWAN
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
