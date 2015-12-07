#ifdef RTCONFIG_QTN
if (unit)
	{
		if (!rpc_qtn_ready())
			retval += websWrite(wp, "<wps_info>%s</wps_info>\n", "");
		else
		{
			if (!strlen(key_passphrase))
				retval += websWrite(wp, "<wps_info>None</wps_info>\n");
			else
			{
				memset(tmpstr, 0, sizeof(tmpstr));
				char_to_ascii(tmpstr, key_passphrase);
				retval += websWrite(wp, "<wps_info>%s</wps_info>\n", tmpstr);
			}
		}
	}
	else
#endif
	if (!strlen(nvram_safe_get(strcat_r(prefix, "wpa_psk", tmp))))
	{
		retval += websWrite(wp, "<wps_info>None</wps_info>\n");
	}
	else
	{
		memset(tmpstr, 0, sizeof(tmpstr));
		char_to_ascii(tmpstr, nvram_safe_get(strcat_r(prefix, "wpa_psk", tmp)));
		retval += websWrite(wp, "<wps_info>%s</wps_info>\n", tmpstr);
	}
