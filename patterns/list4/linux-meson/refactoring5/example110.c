#ifdef CONFIG_P2P
if(rtw_p2p_chk_role(pwdinfo, P2P_ROLE_GO))
		{
			u32 len;
#ifdef CONFIG_IOCTL_CFG80211
			if(pwdinfo->driver_interface == DRIVER_CFG80211 )
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

			pframe += len;
			pktlen += len;
#ifdef CONFIG_WFD
#ifdef CONFIG_IOCTL_CFG80211
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
#endif //CONFIG_IOCTL_CFG80211
			pframe += len;
			pktlen += len;
#endif //CONFIG_WFD
		}
