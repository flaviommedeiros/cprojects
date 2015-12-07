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
