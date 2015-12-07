#ifdef RTCONFIG_QTN
if (unit)
	{
		if (!rpc_qtn_ready())
			retval += websWrite(wp, "<wps_info>%s</wps_info>\n", "");
		else
			retval += websWrite(wp, "<wps_info>%d</wps_info>\n", 1);
	}
	else
#endif
	{
		memset(tmpstr, 0, sizeof(tmpstr));
		sprintf(tmpstr, "%s", nvram_safe_get(strcat_r(prefix, "key", tmp)));
		retval += websWrite(wp, "<wps_info>%s</wps_info>\n", tmpstr);
	}
