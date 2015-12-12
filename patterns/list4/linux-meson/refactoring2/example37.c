#ifdef CONFIG_WFD
if(_TRUE == pwdinfo->wfd_info->wfd_enable)
#endif //CONFIG_IOCTL_CFG80211
			{
			len = build_beacon_wfd_ie( pwdinfo, pframe );
			}
#ifdef CONFIG_IOCTL_CFG80211
			else
			{	
				len = 0;
				if(pmlmepriv->wfd_beacon_ie && pmlmepriv->wfd_beacon_ie_len>0)
				{
					len = pmlmepriv->wfd_beacon_ie_len;
					_rtw_memcpy(pframe, pmlmepriv->wfd_beacon_ie, len);	
				}
			}
