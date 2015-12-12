#ifdef CONFIG_TDLS
if (ptdlsinfo->link_established == _TRUE) {
			rtw_tdls_cmd(adapter, NULL, TDLS_RS_RCR);
			rtw_reset_tdls_info(adapter);
			rtw_free_all_stainfo(adapter);
			//_enter_critical_bh(&(pstapriv->sta_hash_lock), &irqL);
		}
		else
#endif //CONFIG_TDLS
		{
			//_enter_critical_bh(&(pstapriv->sta_hash_lock), &irqL);
			rtw_free_stainfo(adapter,  psta);
		}
