if((conn_changed_state[current_wan_unit] == C2D)
#ifdef RTCONFIG_DUALWAN
						&& strcmp(dualwan_mode, "off")
#endif
						){
#ifdef RTCONFIG_USB_MODEM
					// the current line is USB and be plugged off.
					if(!link_wan[current_wan_unit] && dualwan_unit__usbif(current_wan_unit)){
						clean_modem_state(2);
						if(get_dualwan_by_unit(other_wan_unit) != WANS_DUALWAN_IF_NONE){
							csprintf("\n# wanduck(C2D): Modem was plugged off and try to Switch the other line.\n");
							switch_wan_line(other_wan_unit, 0);
						}
						else if(current_state[current_wan_unit] != WAN_STATE_INITIALIZING){
							csprintf("wanduck3: stop_wan_if %d.\n", current_wan_unit);
							snprintf(cmd, 32, "stop_wan_if %d", current_wan_unit);
							notify_rc(cmd);
						}

#ifdef RTCONFIG_DSL /* Paul add 2013/7/29, for Non-DualWAN 3G/4G WAN -> DSL WAN, auto Fail-Back feature */
#ifndef RTCONFIG_DUALWAN
						if(nvram_match("dsltmp_adslsyncsts","up") && usb_switched_back_dsl == 1){
							csprintf("\n# wanduck: usb_switched_back_dsl: 1.\n");
							link_wan[WAN_UNIT_SECOND] = CONNED; 
							max_disconn_count[WAN_UNIT_SECOND] = max_wait_time[WAN_UNIT_SECOND]/scan_interval;
							usb_switched_back_dsl = 0;
						}
#endif
#endif
					}
					else
#endif
					// C2D: Try to prepare the backup line.
					if(link_wan[other_wan_unit] == 1 && get_wan_state(other_wan_unit) != WAN_STATE_CONNECTED){
						csprintf("\n# wanduck(C2D): Try to prepare the backup line.\n");
						memset(cmd, 0, 32);
						sprintf(cmd, "restart_wan_if %d", other_wan_unit);
						notify_rc_and_wait(cmd);
					}
				}
