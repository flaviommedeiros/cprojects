#ifdef RTCONFIG_QTN
if (unit)
	{
		if (!rpc_qtn_ready())
			retval += websWrite(wp, "<wps_info>%s</wps_info>\n", "");
		else
			retval += websWrite(wp, "<wps_info>%s</wps_info>\n", getWPSEncrypType_qtn());
	}
	else
#endif
	{
		memset(tmpstr, 0, sizeof(tmpstr));
		getWPSEncrypType(unit, tmpstr);
		retval += websWrite(wp, "<wps_info>%s</wps_info>\n", tmpstr);
	}
