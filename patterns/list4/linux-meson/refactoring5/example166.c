#ifdef CONFIG_SPCT_CH_SWITCH
if (1) {
				rtw_ap_inform_ch_switch(pbuddy_adapter, pmlmeext->cur_channel , pmlmeext->cur_ch_offset);
			} else
			#endif
			{
				//issue deauth to all stas if if2 is at ap mode
				rtw_sta_flush(pbuddy_adapter);
			}
