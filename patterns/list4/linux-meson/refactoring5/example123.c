#ifndef CONFIG_IOCTL_CFG80211
if(pext->alg == IW_ENCODE_ALG_SM4)
			_rtw_memcpy(param->u.crypt.seq, pext->rx_seq, 16);
		else
#endif //CONFIG_IOCTL_CFG80211
#endif //CONFIG_WAPI_SUPPORT
		_rtw_memcpy(param->u.crypt.seq, pext->rx_seq, 8);
