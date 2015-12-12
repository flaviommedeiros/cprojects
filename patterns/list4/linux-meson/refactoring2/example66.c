#ifdef CONFIG_CONCURRENT_MODE
if((check_buddy_fwstate(padapter, _FW_LINKED)) != _TRUE)
#endif //CONFIG_CONCURRENT_MODE	
	{

		//switch to the 20M Hz mode after disconnect
		pmlmeext->cur_bwmode = CHANNEL_WIDTH_20;
		pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

		set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);
	}


#ifdef CONFIG_FCS_MODE
	else
	{
		PADAPTER pbuddy_adapter;	
		struct mlme_ext_priv *pbuddy_mlmeext;

		if(EN_FCS(padapter))
		{			
			pbuddy_adapter = padapter->pbuddy_adapter;
			pbuddy_mlmeext = &pbuddy_adapter->mlmeextpriv;
		
			rtw_hal_set_hwreg(padapter, HW_VAR_STOP_FCS_MODE, NULL);

			//switch to buddy's channel setting if buddy is linked
			set_channel_bwmode(padapter, pbuddy_mlmeext->cur_channel, pbuddy_mlmeext->cur_ch_offset, pbuddy_mlmeext->cur_bwmode);
		}	
	}
