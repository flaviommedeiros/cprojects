#ifdef RTCONFIG_QTN
if (unit && rpc_qtn_ready())
	{
		ret = qcsapi_wifi_rfstatus((qcsapi_unsigned_int *) &val);
		if (ret < 0)
			dbG("qcsapi_wifi_rfstatus error, return: %d\n", ret);
		else
			val = !val;
	}
	else
#endif
	{
		wl_ioctl(name, WLC_GET_RADIO, &val, sizeof(val));
		val &= WL_RADIO_SW_DISABLE | WL_RADIO_HW_DISABLE;
	}
