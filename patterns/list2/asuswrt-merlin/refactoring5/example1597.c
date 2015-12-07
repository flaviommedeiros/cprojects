#ifdef RTCONFIG_USB
if (dualwan_unit__usbif(unit))
		type = "USB Modem";
	else
#endif
		type = wan_proto;
