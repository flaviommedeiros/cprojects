switch(pattrib->encrypt){
		case _WEP40_:
		case _WEP104_:
			rtw_wep_encrypt(padapter, (u8 *)pxmitframe);
			break;
		case _TKIP_:
			rtw_tkip_encrypt(padapter, (u8 *)pxmitframe);
			break;
		case _AES_:
			rtw_aes_encrypt(padapter, (u8 * )pxmitframe);
			break;
#ifdef CONFIG_WAPI_SUPPORT
		case _SMS4_:
			rtw_sms4_encrypt(padapter, (u8 * )pxmitframe);
#endif
		default:
				break;
		}
