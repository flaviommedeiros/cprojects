switch(prxattrib->encrypt){
		case _WEP40_:
		case _WEP104_:
			DBG_COUNTER(padapter->rx_logs.core_rx_post_decrypt_wep);
			rtw_wep_decrypt(padapter, (u8 *)precv_frame);
			break;
		case _TKIP_:
			DBG_COUNTER(padapter->rx_logs.core_rx_post_decrypt_tkip);
			res = rtw_tkip_decrypt(padapter, (u8 *)precv_frame);
			break;
		case _AES_:
			DBG_COUNTER(padapter->rx_logs.core_rx_post_decrypt_aes);
			res = rtw_aes_decrypt(padapter, (u8 * )precv_frame);
			break;
#ifdef CONFIG_WAPI_SUPPORT
		case _SMS4_:
			DBG_COUNTER(padapter->rx_logs.core_rx_post_decrypt_wapi);
			rtw_sms4_decrypt(padapter, (u8 * )precv_frame);
			break;
#endif
		default:
				break;
		}
