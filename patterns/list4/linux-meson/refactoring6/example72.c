if(rtw_p2p_chk_role(pwdinfo, P2P_ROLE_GO)
#ifdef CONFIG_IOCTL_CFG80211		
		&& (_TRUE == pwdinfo->wfd_info->wfd_enable)
#endif //CONFIG_IOCTL_CFG80211	
	)
	{
		wfdielen = build_assoc_resp_wfd_ie(pwdinfo, pframe);
		pframe += wfdielen;
		pattrib->pktlen += wfdielen;
	}
