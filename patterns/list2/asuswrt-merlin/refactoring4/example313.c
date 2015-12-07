#ifndef RTCONFIG_WPS_RST_BTN
if (button_pressed(BTN_WIFI_TOG))
#else
	if (button_pressed(BTN_WPS) && nvram_match("btn_ez_radiotoggle", "1")
		&& (nvram_get_int("sw_mode") != SW_MODE_REPEATER)) // repeater mode not support HW radio
#endif
	{
		TRACE_PT("button WIFI_TOG pressed\n");
		if (btn_pressed_toggle_radio == 0){
			radio_switch(0);
			btn_pressed_toggle_radio = 1;
			return;
		}
	}
	else{
		btn_pressed_toggle_radio = 0;
	}
