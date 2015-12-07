#ifdef RTCONFIG_QTN
if (unit)
	{
		if (!rpc_qtn_ready())
			retval += websWrite(wp, "<wps_info>%s</wps_info>\n", "");
		else
		{
			memset(&ssid, 0, sizeof(qcsapi_SSID));
			ret = rpc_qcsapi_get_SSID(WIFINAME, &ssid);
			if (ret < 0)
				dbG("rpc_qcsapi_get_SSID %s error, return: %d\n", WIFINAME, ret);

			memset(tmpstr, 0, sizeof(tmpstr));
			char_to_ascii(tmpstr, ssid);
			retval += websWrite(wp, "<wps_info>%s</wps_info>\n", tmpstr);
		}
	}
	else
#endif
	{
		memset(tmpstr, 0, sizeof(tmpstr));
		char_to_ascii(tmpstr, nvram_safe_get(strcat_r(prefix, "ssid", tmp)));
		retval += websWrite(wp, "<wps_info>%s</wps_info>\n", tmpstr);
	}
