if(	(rtw_get_wps_ie(buf, len, NULL, &wps_ielen) && (wps_ielen>0))
		#ifdef CONFIG_P2P
		|| (rtw_get_p2p_ie(buf, len, NULL, &p2p_ielen) && (p2p_ielen>0))
		#endif
	)		
	{	
		if (net != NULL) 
		{
			switch (type) 
			{
				case 0x1: //BEACON
				ret = rtw_cfg80211_set_beacon_wpsp2pie(net, buf, len);
				break;
				case 0x2: //PROBE_RESP
				ret = rtw_cfg80211_set_probe_resp_wpsp2pie(net, buf, len);
				break;
				case 0x4: //ASSOC_RESP
				ret = rtw_cfg80211_set_assoc_resp_wpsp2pie(net, buf, len);
				break;
			}		
		}
	}
