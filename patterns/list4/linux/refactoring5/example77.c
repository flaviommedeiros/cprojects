#ifdef CONFIG_8723AU_AP_MODE
if (check_fwstate(pmlmepriv, WIFI_AP_STATE)) {
		struct sta_info *psta;
		struct sta_priv *pstapriv = &padapter->stapriv;

		DBG_8723A_LEVEL(_drv_always_, "ap recv deauth reason code(%d) "
				"sta:%pM\n", reason, mgmt->sa);

		psta = rtw_get_stainfo23a(pstapriv, mgmt->sa);
		if (psta) {
			u8 updated = 0;

			spin_lock_bh(&pstapriv->asoc_list_lock);
			if (!list_empty(&psta->asoc_list)) {
				list_del_init(&psta->asoc_list);
				pstapriv->asoc_list_cnt--;
				updated = ap_free_sta23a(padapter, psta,
						      false, reason);
			}
			spin_unlock_bh(&pstapriv->asoc_list_lock);

			associated_clients_update23a(padapter, updated);
		}

		return _SUCCESS;
	} else
#endif
	{
		DBG_8723A_LEVEL(_drv_always_, "sta recv deauth reason code(%d) "
				"sta:%pM\n", reason, mgmt->bssid);

		receive_disconnect23a(padapter, mgmt->bssid, reason);
	}
