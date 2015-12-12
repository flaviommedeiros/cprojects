#ifdef CONFIG_P2P
if(rtw_p2p_chk_role(pwdinfo, P2P_ROLE_GO) /*&& is_valid_p2p_probereq*/)
	{
		u32 len;
#ifdef CONFIG_IOCTL_CFG80211
		if(adapter_wdev_data(padapter)->p2p_enabled && pwdinfo->driver_interface == DRIVER_CFG80211 )
		{
			//if pwdinfo->role == P2P_ROLE_DEVICE will call issue_probersp_p2p()
			len = pmlmepriv->p2p_go_probe_resp_ie_len;
			if(pmlmepriv->p2p_go_probe_resp_ie && len>0)
				_rtw_memcpy(pframe, pmlmepriv->p2p_go_probe_resp_ie, len);
		}
		else
#endif //CONFIG_IOCTL_CFG80211
		{
			len = build_probe_resp_p2p_ie(pwdinfo, pframe);
		}
	
		pframe += len;
		pktlen += len;
			
#ifdef CONFIG_WFD
#ifdef CONFIG_IOCTL_CFG80211
		if(_TRUE == pwdinfo->wfd_info->wfd_enable)
#endif //CONFIG_IOCTL_CFG80211
		{
			len = build_probe_resp_wfd_ie(pwdinfo, pframe, 0);
		}
#ifdef CONFIG_IOCTL_CFG80211
		else
		{	
			len = 0;
			if(pmlmepriv->wfd_probe_resp_ie && pmlmepriv->wfd_probe_resp_ie_len>0)
			{
				len = pmlmepriv->wfd_probe_resp_ie_len;
				_rtw_memcpy(pframe, pmlmepriv->wfd_probe_resp_ie, len); 
			}	
		}
#endif //CONFIG_IOCTL_CFG80211		
		pframe += len;
		pktlen += len;
#endif //CONFIG_WFD
	
	}
