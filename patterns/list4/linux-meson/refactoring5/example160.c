#ifdef CONFIG_P2P
if( (pwdinfo->driver_interface == DRIVER_WEXT) && (rtw_p2p_chk_state(pwdinfo, P2P_STATE_LISTEN)) )
				set_channel_bwmode(padapter, pwdinfo->listen_channel, HAL_PRIME_CHNL_OFFSET_DONT_CARE, CHANNEL_WIDTH_20);
			else
#endif //CONFIG_P2P
 				set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);
