if(check_fwstate(pmlmepriv, WIFI_STATION_STATE)
			&& check_fwstate(pmlmepriv, _FW_LINKED)
#ifdef CONFIG_P2P
			&& rtw_p2p_chk_state(pwdinfo, P2P_STATE_NONE)
#endif // CONFIG_P2P
			)
		{
			DBG_871X("%s %s(" MAC_FMT "), length:%d assoc_ssid.length:%d\n",__FUNCTION__,
					pmlmepriv->cur_network.network.Ssid.Ssid,
					MAC_ARG(pmlmepriv->cur_network.network.MacAddress),
					pmlmepriv->cur_network.network.Ssid.SsidLength,
					pmlmepriv->assoc_ssid.SsidLength);
			rtw_set_to_roam(padapter, 1);
		}
