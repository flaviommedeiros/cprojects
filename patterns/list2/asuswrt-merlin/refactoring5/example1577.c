#ifdef RTCONFIG_QTN
if (unit)
		{
			if (!rpc_qtn_ready())
				retval += websWrite(wp, "<wps_info>%s</wps_info>\n", "5 GHz radio is not ready");
			else
				retval += websWrite(wp, "<wps_info>%s</wps_info>\n", getWscStatusStr_qtn());
		}
		else
#endif
		retval += websWrite(wp, "<wps_info>%s</wps_info>\n", getWscStatusStr());
