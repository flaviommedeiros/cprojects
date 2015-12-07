#ifdef RTCONFIG_INTERNAL_GOBI
if(nvram_get_int("usb_buildin") == port_num)
		; //skip this LED
	else
#endif	/* RTCONFIG_INTERNAL_GOBI */
	if (turn_on_led && strcmp(nvram_safe_get(nvram_usb_path), "1"))
		nvram_set(nvram_usb_path, "1");
