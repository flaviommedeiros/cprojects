#ifdef CONFIG_IOCTL_CFG80211
if(adapter_wdev_data(padapter)->p2p_enabled && pwdinfo->driver_interface == DRIVER_CFG80211 )
			{
				len = pmlmepriv->p2p_beacon_ie_len;
				if(pmlmepriv->p2p_beacon_ie && len>0)				
					_rtw_memcpy(pframe, pmlmepriv->p2p_beacon_ie, len);
			}
			else
#endif //CONFIG_IOCTL_CFG80211
			{
				len = build_beacon_p2p_ie(pwdinfo, pframe);
			}
