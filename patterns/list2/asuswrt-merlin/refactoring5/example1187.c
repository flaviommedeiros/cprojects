#ifdef BTN_SETUP
if (btn_pressed_setup == BTNSETUP_NONE)
	{
#endif
#ifndef RTCONFIG_N56U_SR2
	if (button_pressed(BTN_RESET))
#else
	if (0)
#endif
	{
		TRACE_PT("button RESET pressed\n");

	/*--------------- Add BTN_RST MFG test ------------------------*/
#ifndef RTCONFIG_WPS_RST_BTN
#ifdef RTCONFIG_DSL /* Paul add 2013/4/2 */
			if((btn_count % 2)==0)
				led_control(0, 1);
			else
				led_control(0, 0);
#endif
#endif	/* ! RTCONFIG_WPS_RST_BTN */
			if (!btn_pressed)
			{
				btn_pressed = 1;
				btn_count = 0;
				alarmtimer(0, URGENT_PERIOD);
			}
			else
			{	/* Whenever it is pushed steady */
#ifdef RTCONFIG_WPS_RST_BTN
				btn_count++;
#else	/* ! RTCONFIG_WPS_RST_BTN */
				if (++btn_count > RESET_WAIT_COUNT)
				{
					fprintf(stderr, "You can release RESET button now!\n");
#if (defined(PLN12) || defined(PLAC56))
					if (btn_pressed == 1)
						set_wifiled(5);
#endif
					btn_pressed = 2;
				}
				if (btn_pressed == 2)
				{
#ifdef RTCONFIG_DSL /* Paul add 2013/4/2 */
					led_control(0, 0);
					alarmtimer(0, 0);
					nvram_set("restore_defaults", "1");
					if (notify_rc_after_wait("resetdefault")) {
						/* Send resetdefault rc_service failed. */
						alarmtimer(NORMAL_PERIOD, 0);
					}
#else
				/* 0123456789 */
				/* 0011100111 */
					if ((btn_count % 10) < 2 || ((btn_count % 10) > 4 && (btn_count % 10) < 7))
						led_control(LED_POWER, LED_OFF);
					else
						led_control(LED_POWER, LED_ON);
#endif
				}
#endif	/* ! RTCONFIG_WPS_RST_BTN */
			}
	}
#if defined(RTCONFIG_WIRELESS_SWITCH) && defined(RTCONFIG_DSL)
	else if (button_pressed(BTN_WIFI_SW))
	{
		//TRACE_PT("button BTN_WIFI_SW pressed\n");
			if(wlan_sw_init == 0)
			{
				wlan_sw_init = 1;
/*
				eval("iwpriv", "ra0", "set", "RadioOn=1");
				eval("iwpriv", "rai0", "set", "RadioOn=1");
				TRACE_PT("Radio On\n");
				nvram_set("wl0_radio", "1");
				nvram_set("wl1_radio", "1");
				nvram_commit();
*/
			}
			else
			{
				// if wlan switch on , btn reset routine goes here
				if (btn_pressed==2)
				{
					// IT MUST BE SAME AS BELOW CODE
					led_control(LED_POWER, LED_OFF);
					alarmtimer(0, 0);
					nvram_set("restore_defaults", "1");
					if(notify_rc_after_wait("resetdefault")) {
						/* Send resetdefault rc_service failed. */
						alarmtimer(NORMAL_PERIOD, 0);
					}
				}

				if(nvram_match("wl0_HW_switch", "0") || nvram_match("wl1_HW_switch", "0")){
					//Ever apply the Wireless-Professional Web GU.
					//Not affect the status of WiFi interface, so do nothing
				}
				else{	//trun on WiFi by HW slash, make sure both WiFi interface enable.
					if(nvram_match("wl0_radio", "0") || nvram_match("wl1_radio", "0")){
						eval("iwpriv", "ra0", "set", "RadioOn=1");
						eval("iwpriv", "rai0", "set", "RadioOn=1");
						TRACE_PT("Radio On\n");
						nvram_set("wl0_radio", "1");
						nvram_set("wl1_radio", "1");

						nvram_set("wl0_HW_switch", "0");
						nvram_set("wl1_HW_switch", "0");
						nvram_commit();
					}
				}
			}
	}
#endif	/* RTCONFIG_WIRELESS_SWITCH && RTCONFIG_DSL */
	else
	{
#ifdef RTCONFIG_WPS_RST_BTN
		if (btn_pressed == 0)
			;
		else if (btn_count < WPS_RST_DO_RESTORE_COUNT)
		{
			if (btn_count < WPS_RST_DO_RESTORE_COUNT && btn_count >= WPS_RST_DO_WPS_COUNT && nvram_match("btn_ez_radiotoggle", "1"))
			{
				radio_switch(0);
			}

			if (btn_count < WPS_RST_DO_RESTORE_COUNT && btn_count >= WPS_RST_DO_WPS_COUNT
			   && !no_need_to_start_wps()
			   && !wps_band_radio_off(get_radio_band(0))
			   && !wps_band_ssid_broadcast_off(get_radio_band(0))
			   && nvram_match("btn_ez_radiotoggle", "0")
			   && !nvram_match("wps_ign_btn", "1")
			)
			{
				btn_pressed_setup = BTNSETUP_DETECT;
				btn_count_setup = WPS_WAIT_COUNT;	//to trigger WPS
				alarmtimer(0, RUSHURGENT_PERIOD);
			}
			else
			{
				btn_pressed_setup = BTNSETUP_NONE;
				btn_count_setup = 0;
				alarmtimer(NORMAL_PERIOD, 0);
			}

			btn_count = 0;
			btn_pressed = 0;
			led_control(LED_POWER, LED_ON);
		}
		else if (btn_count >= WPS_RST_DO_RESTORE_COUNT)	// to do restore
#else	/* ! RTCONFIG_WPS_RST_BTN */
		if (btn_pressed == 1)
		{
			btn_count = 0;
			btn_pressed = 0;
			led_control(LED_POWER, LED_ON);
			alarmtimer(NORMAL_PERIOD, 0);
		}
		else if (btn_pressed == 2)
#endif	/* ! RTCONFIG_WPS_RST_BTN */
		{
			led_control(LED_POWER, LED_OFF);
#if (defined(PLN12) || defined(PLAC56))
			set_wifiled(2);
#endif
			alarmtimer(0, 0);
			nvram_set("restore_defaults", "1");
			if (notify_rc_after_wait("resetdefault")) {
				/* Send resetdefault rc_service failed. */
				alarmtimer(NORMAL_PERIOD, 0);
			}
		}
#if defined(RTCONFIG_WIRELESS_SWITCH) && defined(RTCONFIG_DSL)
		else
		{
			// no button is pressed or released
			if(wlan_sw_init == 0)
			{
				wlan_sw_init = 1;
				eval("iwpriv", "ra0", "set", "RadioOn=0");
				eval("iwpriv", "rai0", "set", "RadioOn=0");
				TRACE_PT("Radio Off\n");
				nvram_set("wl0_radio", "0");
				nvram_set("wl1_radio", "0");

				nvram_set("wl0_HW_switch", "1");
				nvram_set("wl1_HW_switch", "1");

				nvram_commit();
			}
			else
			{
				if(nvram_match("wl0_radio", "1") || nvram_match("wl1_radio", "1")){
					eval("iwpriv", "ra0", "set", "RadioOn=0");
					eval("iwpriv", "rai0", "set", "RadioOn=0");
					TRACE_PT("Radio Off\n");
					nvram_set("wl0_radio", "0");
					nvram_set("wl1_radio", "0");

					nvram_set("wl0_timesched", "0");
					nvram_set("wl1_timesched", "0");
				}

				//indicate use switch HW slash manually.
				if(nvram_match("wl0_HW_switch", "0") || nvram_match("wl1_HW_switch", "0")){
					nvram_set("wl0_HW_switch", "1");
					nvram_set("wl1_HW_switch", "1");
				}
			}
		}
#endif	/* RTCONFIG_WIRELESS_SWITCH && RTCONFIG_DSL */
	}

#ifdef BTN_SETUP
	}
