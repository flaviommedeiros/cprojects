#ifdef RTCONFIG_WPS_DUALBAND
if (1)
#else
	if (wps_band)
#endif
	{
		if (strlen(wps_sta_pin) && strcmp(wps_sta_pin, "00000000") && (wl_wpsPincheck(wps_sta_pin) == 0))
		{
			retval = rpc_qcsapi_wps_registrar_report_pin(WIFINAME, wps_sta_pin);
			if (retval < 0)
				dbG("rpc_qcsapi_wps_registrar_report_pin %s error, return: %d\n", WIFINAME, retval);
		}
		else
		{
			retval = rpc_qcsapi_wps_registrar_report_button_press(WIFINAME);
			if (retval < 0)
				dbG("rpc_qcsapi_wps_registrar_report_button_press %s error, return: %d\n", WIFINAME, retval);
		}

#ifdef RTCONFIG_WPS_DUALBAND
		// return 0;
#else
		return 0;
#endif
	}
