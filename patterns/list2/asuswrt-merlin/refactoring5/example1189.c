#ifndef RTCONFIG_WPS_RST_BTN
if (button_pressed(BTN_WPS) &&
			    !no_need_to_start_wps() &&
			    !wps_band_radio_off(get_radio_band(0)) &&
			    !wps_band_ssid_broadcast_off(get_radio_band(0)))
			{
				/* Whenever it is pushed steady, again... */
#if 0
				if (++btn_count_setup_second > WPS_WAIT_COUNT)
#else
				if (++btn_count_setup_second)
#endif
				{
					btn_pressed_setup = BTNSETUP_START;
					btn_count_setup_second = 0;
					nvram_set("wps_ign_btn", "1");
#if 0
					start_wps_pbc(0);	// always 2.4G
#else
					kill_pidfile_s("/var/run/wpsaide.pid", SIGTSTP);
#endif
					wsc_timeout = WPS_TIMEOUT_COUNT;
				}
			}
