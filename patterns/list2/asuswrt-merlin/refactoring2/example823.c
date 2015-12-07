#ifdef RTCONFIG_USB_MODEM
if(!(dualwan_unit__usbif(wan_unit) && current_state[wan_unit] == WAN_STATE_INITIALIZING))
#endif
					conn_state[wan_unit] = if_wan_connected(wan_unit, nvram_get_int(nvram_state[wan_unit]));
