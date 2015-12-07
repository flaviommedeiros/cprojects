#ifdef RTCONFIG_QTN
if (unit && !rpc_qtn_ready())
	{
		ret += websWrite(wp, "5 GHz radio is not ready\n");
		return ret;
	}
	else
#endif
	if (val)
	{
		ret += websWrite(wp, "%s radio is disabled\n",
			(wl_control_channel(unit) > 0) ?
			((wl_control_channel(unit) > CH_MAX_2G_CHANNEL) ? "5 GHz" : "2.4 GHz") :
			(nvram_match(strcat_r(prefix, "nband", tmp), "1") ? "5 GHz" : "2.4 GHz"));
		return ret;
	}
