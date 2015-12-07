if(wan_primary_ifunit() == wan_unit) // Already have no running modem.
		return 0;
#ifdef RTCONFIG_USB_MODEM
	else if (dualwan_unit__usbif(wan_unit)) {
		if(!link_wan[wan_unit]) {
			snprintf(prefix, sizeof(prefix), "wan%d_", wan_unit);
			nvram_set_int(strcat_r(prefix, "is_usb_modem_ready", tmp), link_wan[wan_unit]);
			return 0; // No modem in USB ports.
		}
	}
#endif
