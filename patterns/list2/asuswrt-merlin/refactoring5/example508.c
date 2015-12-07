#ifdef RTCONFIG_QTN
if (unit)
	{
		if (!rpc_qtn_ready())
			retval += websWrite(wp, "<wps_info>%s</wps_info>\n", "");
		else
			retval += websWrite(wp, "<wps_info>%s</wps_info>\n", get_WPSConfiguredStr_qtn());
	}
	else
#endif
	if (!wps_is_oob())
		retval += websWrite(wp, "<wps_info>%s</wps_info>\n", "Yes");
	else
		retval += websWrite(wp, "<wps_info>%s</wps_info>\n", "No");
