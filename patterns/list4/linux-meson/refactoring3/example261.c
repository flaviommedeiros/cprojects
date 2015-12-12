switch (pext->alg) {
	case IW_ENCODE_ALG_NONE:
		//todo: remove key 
		//remove = 1;	
		alg_name = "none";
		break;
	case IW_ENCODE_ALG_WEP:
		alg_name = "WEP";
		break;
	case IW_ENCODE_ALG_TKIP:
		alg_name = "TKIP";
		break;
	case IW_ENCODE_ALG_CCMP:
		alg_name = "CCMP";
		break;
#ifdef CONFIG_IEEE80211W
	case IW_ENCODE_ALG_AES_CMAC:
		alg_name = "BIP";
		break;
#endif //CONFIG_IEEE80211W
#ifdef CONFIG_WAPI_SUPPORT
#ifndef CONFIG_IOCTL_CFG80211
	case IW_ENCODE_ALG_SM4:
		alg_name= "SMS4";
		_rtw_memcpy(param->sta_addr, pext->addr.sa_data, ETH_ALEN);
		DBG_871X("rtw_wx_set_enc_ext: SMS4 case \n");
		break;
#endif
#endif
	default:
		ret = -1;
		goto exit;
	}
