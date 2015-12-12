if ( !rtw_mc2u_disable
		&& check_fwstate(pmlmepriv, WIFI_AP_STATE) == _TRUE
		&& ( IP_MCAST_MAC(pkt->data)
			|| ICMPV6_MCAST_MAC(pkt->data)
			#ifdef CONFIG_TX_BCAST2UNI
			|| is_broadcast_mac_addr(pkt->data)
			#endif
			)
		&& (padapter->registrypriv.wifi_spec == 0)
		)
	{
		if ( pxmitpriv->free_xmitframe_cnt > (NR_XMITFRAME/4) ) {
			res = rtw_mlcst2unicst(padapter, pkt);
			if (res == _TRUE) {
				goto exit;
			}
		} else {
			//DBG_871X("Stop M2U(%d, %d)! ", pxmitpriv->free_xmitframe_cnt, pxmitpriv->free_xmitbuf_cnt);
			//DBG_871X("!m2u );
			DBG_COUNTER(padapter->tx_logs.os_tx_m2u_stop);
		}
	}
