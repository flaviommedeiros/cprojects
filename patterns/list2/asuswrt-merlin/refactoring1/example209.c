if (nvram_match(strcat_r(prefix, "enable", tmp), "0")) {
		update_wan_state(prefix, WAN_STATE_DISABLED, 0);
		return;
	}
#ifdef RTCONFIG_USB_MODEM
	else if(nvram_get_int("usb_modem_act_scanning") != 0){
_dprintf("start_wan_if: USB modem is scanning...\n");
		update_wan_state(prefix, WAN_STATE_STOPPED, WAN_STOPPED_REASON_USBSCAN);
		return;
	}
#endif
