#ifdef RTCONFIG_USB_MODEM
if(!(dualwan_unit__usbif(other_wan_unit) && current_state[other_wan_unit] == WAN_STATE_INITIALIZING))
#endif
						conn_state[other_wan_unit] = if_wan_connected(other_wan_unit, current_state[other_wan_unit]);
