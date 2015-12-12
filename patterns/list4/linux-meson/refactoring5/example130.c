#ifdef CONFIG_CONCURRENT_MODE
if (check_buddy_fwstate(padapter, _FW_LINKED )) {
		u8 co_channel=0xff;
		PADAPTER pbuddy_adapter = padapter->pbuddy_adapter;			
		struct mlme_ext_priv *pbuddy_mlmeext = &pbuddy_adapter->mlmeextpriv;	

		co_channel = rtw_get_oper_ch(padapter);

		if (tx_ch != pbuddy_mlmeext->cur_channel) {

			u16 ext_listen_period;
			
			if (ATOMIC_READ(&pwdev_priv->switch_ch_to)==1) {
				if (check_buddy_fwstate(padapter, WIFI_FW_STATION_STATE)) {
					DBG_8192C("%s, issue nulldata pwrbit=1\n", __func__);
					issue_nulldata(padapter->pbuddy_adapter, NULL, 1, 3, 500);
				}

				ATOMIC_SET(&pwdev_priv->switch_ch_to, 0);

				//DBG_8192C("%s, set switch ch timer, period=%d\n", __func__, pwdinfo->ext_listen_period);
				//_set_timer(&pwdinfo->ap_p2p_switch_timer, pwdinfo->ext_listen_period);
			}

			if (check_fwstate(&padapter->mlmepriv, _FW_LINKED ))
			{
				ext_listen_period = 500;// 500ms
			}	
			else
			{				
				ext_listen_period = pwdinfo->ext_listen_period;
			}

			DBG_8192C("%s, set switch ch timer, period=%d\n", __func__, ext_listen_period);
			_set_timer(&pwdinfo->ap_p2p_switch_timer, ext_listen_period);	
			
		}

		if (!check_fwstate(&padapter->mlmepriv, _FW_LINKED ))
			pmlmeext->cur_channel = tx_ch;

		if (tx_ch != co_channel)
			set_channel_bwmode(padapter, tx_ch, HAL_PRIME_CHNL_OFFSET_DONT_CARE, CHANNEL_WIDTH_20);
	}else 
#endif //CONFIG_CONCURRENT_MODE
	//if (tx_ch != pmlmeext->cur_channel) {
	if(tx_ch != rtw_get_oper_ch(padapter)) {
		if (!check_fwstate(&padapter->mlmepriv, _FW_LINKED ))
			pmlmeext->cur_channel = tx_ch;
		set_channel_bwmode(padapter, tx_ch, HAL_PRIME_CHNL_OFFSET_DONT_CARE, CHANNEL_WIDTH_20);
	}
