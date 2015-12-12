switch (pattrib->encrypt)
	{
		case _WEP40_:
		case _WEP104_:
			pattrib->iv_len = 4;
			pattrib->icv_len = 4;
			WEP_IV(pattrib->iv, psta->dot11txpn, pattrib->key_idx);
			break;

		case _TKIP_:
			pattrib->iv_len = 8;
			pattrib->icv_len = 4;

			if(psecuritypriv->busetkipkey==_FAIL)
			{				
				#ifdef DBG_TX_DROP_FRAME
				DBG_871X("DBG_TX_DROP_FRAME %s psecuritypriv->busetkipkey(%d)==_FAIL drop packet\n", __FUNCTION__, psecuritypriv->busetkipkey);
				#endif
				res =_FAIL;
				goto exit;
			}

			if(bmcast)
				TKIP_IV(pattrib->iv, psta->dot11txpn, pattrib->key_idx);
			else
				TKIP_IV(pattrib->iv, psta->dot11txpn, 0);


			_rtw_memcpy(pattrib->dot11tkiptxmickey.skey, psta->dot11tkiptxmickey.skey, 16);
			
			break;
			
		case _AES_:
			
			pattrib->iv_len = 8;
			pattrib->icv_len = 8;
			
			if(bmcast)
				AES_IV(pattrib->iv, psta->dot11txpn, pattrib->key_idx);
			else
				AES_IV(pattrib->iv, psta->dot11txpn, 0);
			
			break;

#ifdef CONFIG_WAPI_SUPPORT
		case _SMS4_:
			pattrib->iv_len = 18;
			pattrib->icv_len = 16;
			rtw_wapi_get_iv(padapter,pattrib->ra,pattrib->iv);			
			break;
#endif
		default:
			pattrib->iv_len = 0;
			pattrib->icv_len = 0;
			break;
	}
