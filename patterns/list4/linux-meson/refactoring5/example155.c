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
