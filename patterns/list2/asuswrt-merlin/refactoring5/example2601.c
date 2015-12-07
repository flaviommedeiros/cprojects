#ifdef RTCONFIG_USB_MODEM
if(dualwan_unit__usbif(current_wan_unit)){
				if(current_state[current_wan_unit] == WAN_STATE_INITIALIZING){
					if(!strcmp(modem_type, "qmi")){
						csprintf("wanduck(%d): Sleep 1 seconds to wait QMI modem nodes.\n", current_wan_unit);
						sleep(1);
					}
					handle_wan_line(current_wan_unit, 0);
				}
				else
					csprintf("wanduck(%d): the modem had been run...\n", current_wan_unit);
			}
			else
#endif
				handle_wan_line(current_wan_unit, 0);
