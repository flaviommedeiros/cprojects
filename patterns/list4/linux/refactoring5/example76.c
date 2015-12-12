#ifdef CONFIG_88EU_AP_MODE
if (check_fwstate(pmlmepriv, WIFI_AP_STATE)) {
		struct sta_info *psta;
		struct sta_priv *pstapriv = &padapter->stapriv;

		DBG_88E_LEVEL(_drv_always_, "ap recv disassoc reason code(%d) sta:%pM\n",
			      reason, GetAddr2Ptr(pframe));

		psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));
		if (psta) {
			u8 updated = 0;

			spin_lock_bh(&pstapriv->asoc_list_lock);
			if (!list_empty(&psta->asoc_list)) {
				list_del_init(&psta->asoc_list);
				pstapriv->asoc_list_cnt--;
				updated = ap_free_sta(padapter, psta, false, reason);
			}
			spin_unlock_bh(&pstapriv->asoc_list_lock);

			associated_clients_update(padapter, updated);
		}

		return _SUCCESS;
	} else
#endif
	{
		DBG_88E_LEVEL(_drv_always_, "ap recv disassoc reason code(%d) sta:%pM\n",
			      reason, GetAddr3Ptr(pframe));

		receive_disconnect(padapter, GetAddr3Ptr(pframe), reason);
	}
