switch (params->cipher) {
	case IW_AUTH_CIPHER_NONE:
		//todo: remove key 
		//remove = 1;	
		alg_name = "none";
		break;
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
		alg_name = "WEP";
		break;
	case WLAN_CIPHER_SUITE_TKIP:
		alg_name = "TKIP";
		break;
	case WLAN_CIPHER_SUITE_CCMP:
		alg_name = "CCMP";
		break;
#ifdef CONFIG_IEEE80211W
	case WLAN_CIPHER_SUITE_AES_CMAC:
		alg_name = "BIP";
		break;
#endif //CONFIG_IEEE80211W
#ifdef CONFIG_WAPI_SUPPORT
	case WLAN_CIPHER_SUITE_SMS4:
		alg_name= "SMS4";
		if(pairwise == NL80211_KEYTYPE_PAIRWISE) {
			if (key_index != 0 && key_index != 1) {
				ret = -ENOTSUPP;
				goto addkey_end;
			}
			_rtw_memcpy((void*)param->sta_addr, (void*)mac_addr, ETH_ALEN);
		} else {
			DBG_871X("mac_addr is null \n");
		}
		DBG_871X("rtw_wx_set_enc_ext: SMS4 case \n");
		break;
#endif

	default:	
		ret = -ENOTSUPP;
		goto addkey_end;
	}
