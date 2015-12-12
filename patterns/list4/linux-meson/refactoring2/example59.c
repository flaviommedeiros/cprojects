#ifdef CONFIG_SW_ANTENNA_DIVERSITY
if (GET_HAL_DATA(padapter)->odmpriv.RSSI_test == _FALSE)
#endif
	{
		precvframe->u.hdr.psta = NULL;
		if (pkt_info.bPacketMatchBSSID
			&& (check_fwstate(&padapter->mlmepriv, WIFI_AP_STATE) == _TRUE)
		) {
			if (psta) {
				precvframe->u.hdr.psta = psta;
				rx_process_phy_info(padapter, precvframe);
			}
		} else if (pkt_info.bPacketToSelf || pkt_info.bPacketBeacon) {
			if (check_fwstate(&padapter->mlmepriv, WIFI_ADHOC_STATE|WIFI_ADHOC_MASTER_STATE) == _TRUE) {
				if (psta)
					precvframe->u.hdr.psta = psta;
			}
			rx_process_phy_info(padapter, precvframe);
		}
	}
