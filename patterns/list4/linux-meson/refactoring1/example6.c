if ( _TRUE == pwdinfo->wfd_info->wfd_enable )
#endif //CONFIG_IOCTL_CFG80211
	{
		wfdielen = build_probe_resp_wfd_ie(pwdinfo, pframe, 0);
		pframe += wfdielen;
		pattrib->pktlen += wfdielen;
	}
#ifdef CONFIG_IOCTL_CFG80211
	else if (pmlmepriv->wfd_probe_resp_ie != NULL && pmlmepriv->wfd_probe_resp_ie_len>0)
	{
		//WFD IE
		_rtw_memcpy(pframe, pmlmepriv->wfd_probe_resp_ie, pmlmepriv->wfd_probe_resp_ie_len);
		pattrib->pktlen += pmlmepriv->wfd_probe_resp_ie_len;
		pframe += pmlmepriv->wfd_probe_resp_ie_len;		
	}
#endif
