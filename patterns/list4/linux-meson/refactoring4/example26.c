#ifdef CONFIG_LPS
if ( (pattrib->ether_type == 0x88B4) || (pattrib->ether_type == 0x0806) || (pattrib->ether_type == 0x888e) || (pattrib->dhcp_pkt == 1) )
#else //!CONFIG_WAPI_SUPPORT
#if 0
	if ( (pattrib->ether_type == 0x0806) || (pattrib->ether_type == 0x888e) || (pattrib->dhcp_pkt == 1) )
#else // only ICMP/DHCP packets is as SPECIAL_PACKET, and leave LPS when tx IMCP/DHCP packets.
	//if ((pattrib->ether_type == 0x888e) || (pattrib->dhcp_pkt == 1) )
	if (pattrib->icmp_pkt==1)
	{
		rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_LEAVE, 1);
	}
	else if(pattrib->dhcp_pkt==1)
#endif 
#endif
	{
		DBG_COUNTER(padapter->tx_logs.core_tx_upd_attrib_active);
		rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_SPECIAL_PACKET, 1);
	}
