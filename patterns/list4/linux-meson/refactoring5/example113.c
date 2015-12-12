#ifdef CONFIG_ARP_KEEP_ALIVE
if (rtw_gw_addr_query(padapter)==0) {
		SET_ARP_PKT_TARGET_MAC_ADDR(pARPRspPkt, pmlmepriv->gw_mac_addr);
		SET_ARP_PKT_TARGET_IP_ADDR(pARPRspPkt, pmlmepriv->gw_ip);
	}
	else
#endif
	{
		SET_ARP_PKT_TARGET_MAC_ADDR(pARPRspPkt,
				get_my_bssid(&(pmlmeinfo->network)));
		SET_ARP_PKT_TARGET_IP_ADDR(pARPRspPkt,
				pIPAddress);
		DBG_871X("%s Target Mac Addr:" MAC_FMT "\n", __FUNCTION__,
				MAC_ARG(get_my_bssid(&(pmlmeinfo->network))));
		DBG_871X("%s Target IP Addr" IP_FMT "\n", __FUNCTION__,
				IP_ARG(pIPAddress));
	}
