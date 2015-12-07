#ifdef RTCONFIG_QTN
if (unit && !rpc_qtn_ready())
	{
		ret += websWrite(wp, "dataarray5 = [];wificlients5 = [];");
		return ret;
	}
	else
#endif
	if (val)
	{
		if (unit == 1)
			ret += websWrite(wp, "dataarray5 = [];wificlients5 = [];");
		else if (unit == 2)
			ret += websWrite(wp, "dataarray52 = [];wificlients52 = [];");
		else
			ret += websWrite(wp, "dataarray24 = [];wificlients24 = [];");
		return ret;
	}
