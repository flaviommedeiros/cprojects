#ifdef CONFIG_TDLS
if (rtw_check_tdls_established(padapter, pattrib) == _TRUE)
			_rtw_memcpy(pattrib->ra, pattrib->dst, ETH_ALEN);	/* For TDLS direct link Tx, set ra to be same to dst */
		else
#endif
		_rtw_memcpy(pattrib->ra, get_bssid(pmlmepriv), ETH_ALEN);
