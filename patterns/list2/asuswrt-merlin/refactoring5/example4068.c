#ifdef RTCONFIG_WPS_DUALBAND
if (nvram_get_int("wps_enable"))
#else
	if (nvram_get_int("wps_enable") && nvram_get_int("wps_band"))
#endif
	{
		retval = rpc_qcsapi_wps_get_state(WIFINAME, wps_state, sizeof(wps_state));
		if (retval < 0)
			dbG("rpc_qcsapi_wps_get_state %s error, return: %d\n", WIFINAME, retval);
		else
		{
			if (sscanf(wps_state, "%d %s", &state, state_str) != 2)
				dbG("prase wps state error!\n");

			switch (state) {
				case 0: /* WPS_INITIAL */
					dbg("QTN: WPS Init\n");
					break;
				case 1: /* WPS_START */
					dbg("QTN: Processing WPS start...\n");
					ret = 0;
#ifdef RTCONFIG_WPS_DUALBAND
					ret_qtn = 0;
#endif
					break;
				case 2: /* WPS_SUCCESS */
					dbg("QTN: WPS Success\n");
					break;
				case 3: /* WPS_ERROR */
					dbg("QTN: WPS Fail due to message exange error!\n");
					break;
				case 4: /* WPS_TIMEOUT */
					dbg("QTN: WPS Fail due to time out!\n");
					break;
				case 5: /* WPS_OVERLAP */
					dbg("QTN: WPS Fail due to PBC session overlap!\n");
					break;
				default:
					ret = 0;
#ifdef RTCONFIG_WPS_DUALBAND
					ret_qtn = 0;
#endif
					break;
			}
		}

#ifdef RTCONFIG_WPS_DUALBAND
		// return ret;
#else
		return ret;
#endif
	}
