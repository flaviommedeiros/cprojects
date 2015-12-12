switch (cmd)
	{
		case RTL_IOCTL_WPA_SUPPLICANT:
			ret = wpa_supplicant_ioctl(dev, &wrq->u.data);
			break;
#ifdef CONFIG_AP_MODE
		case RTL_IOCTL_HOSTAPD:
			ret = rtw_hostapd_ioctl(dev, &wrq->u.data);
			break;
#ifdef CONFIG_WIRELESS_EXT
		case SIOCSIWMODE:
			ret = rtw_wx_set_mode(dev, NULL, &wrq->u, NULL);
			break;
#endif
#endif // CONFIG_AP_MODE
		case SIOCDEVPRIVATE:				
			 ret = rtw_ioctl_wext_private(dev, rq);
			break;
		case (SIOCDEVPRIVATE+1):
			ret = rtw_android_priv_cmd(dev, rq, cmd);
			break;
		default:
			ret = -EOPNOTSUPP;
			break;
	}
