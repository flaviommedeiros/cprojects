switch(cmd_num) {

	case ANDROID_WIFI_CMD_STOP:
		//bytes_written = wl_android_wifi_off(net);
		break;
		
	case ANDROID_WIFI_CMD_SCAN_ACTIVE:
		//rtw_set_scan_mode((_adapter *)rtw_netdev_priv(net), SCAN_ACTIVE);
#ifdef CONFIG_PLATFORM_MSTAR
#ifdef CONFIG_IOCTL_CFG80211
		adapter_wdev_data((_adapter *)rtw_netdev_priv(net))->bandroid_scan = _TRUE;
#endif //CONFIG_IOCTL_CFG80211
#endif //CONFIG_PLATFORM_MSTAR
		break;
	case ANDROID_WIFI_CMD_SCAN_PASSIVE:
		//rtw_set_scan_mode((_adapter *)rtw_netdev_priv(net), SCAN_PASSIVE);
		break;
		
	case ANDROID_WIFI_CMD_RSSI:
		bytes_written = rtw_android_get_rssi(net, command, priv_cmd.total_len);
		break;
	case ANDROID_WIFI_CMD_LINKSPEED:
		bytes_written = rtw_android_get_link_speed(net, command, priv_cmd.total_len);
		break;

	case ANDROID_WIFI_CMD_MACADDR:
		bytes_written = rtw_android_get_macaddr(net, command, priv_cmd.total_len);
		break;

	case ANDROID_WIFI_CMD_BLOCK_SCAN:
		bytes_written = rtw_android_set_block_scan(net, command, priv_cmd.total_len);
		break;

	case ANDROID_WIFI_CMD_BLOCK:
		bytes_written = rtw_android_set_block(net, command, priv_cmd.total_len);
		break;
		
	case ANDROID_WIFI_CMD_RXFILTER_START:
		//bytes_written = net_os_set_packet_filter(net, 1);
		break;
	case ANDROID_WIFI_CMD_RXFILTER_STOP:
		//bytes_written = net_os_set_packet_filter(net, 0);
		break;
	case ANDROID_WIFI_CMD_RXFILTER_ADD:
		//int filter_num = *(command + strlen(CMD_RXFILTER_ADD) + 1) - '0';
		//bytes_written = net_os_rxfilter_add_remove(net, TRUE, filter_num);
		break;
	case ANDROID_WIFI_CMD_RXFILTER_REMOVE:
		//int filter_num = *(command + strlen(CMD_RXFILTER_REMOVE) + 1) - '0';
		//bytes_written = net_os_rxfilter_add_remove(net, FALSE, filter_num);
		break;
		
	case ANDROID_WIFI_CMD_BTCOEXSCAN_START:
		/* TBD: BTCOEXSCAN-START */
		break;
	case ANDROID_WIFI_CMD_BTCOEXSCAN_STOP:
		/* TBD: BTCOEXSCAN-STOP */
		break;
	case ANDROID_WIFI_CMD_BTCOEXMODE:
		#if 0
		uint mode = *(command + strlen(CMD_BTCOEXMODE) + 1) - '0';
		if (mode == 1)
			net_os_set_packet_filter(net, 0); /* DHCP starts */
		else
			net_os_set_packet_filter(net, 1); /* DHCP ends */
#ifdef WL_CFG80211
		bytes_written = wl_cfg80211_set_btcoex_dhcp(net, command);
#endif
		#endif
		break;
		
	case ANDROID_WIFI_CMD_SETSUSPENDOPT:
		//bytes_written = wl_android_set_suspendopt(net, command, priv_cmd.total_len);
		break;
		
	case ANDROID_WIFI_CMD_SETBAND:
		bytes_written = rtw_android_setband(net, command, priv_cmd.total_len);
		break;

	case ANDROID_WIFI_CMD_GETBAND:
		bytes_written = rtw_android_getband(net, command, priv_cmd.total_len);
		break;

	case ANDROID_WIFI_CMD_COUNTRY:
		bytes_written = rtw_android_set_country(net, command, priv_cmd.total_len);
		break;
		
#ifdef CONFIG_PNO_SUPPORT
	case ANDROID_WIFI_CMD_PNOSSIDCLR_SET:
		//bytes_written = dhd_dev_pno_reset(net);
		break;
	case ANDROID_WIFI_CMD_PNOSETUP_SET:
		bytes_written = rtw_android_pno_setup(net, command, priv_cmd.total_len);
		break;
	case ANDROID_WIFI_CMD_PNOENABLE_SET:
		cmdlen = strlen(android_wifi_cmd_str[ANDROID_WIFI_CMD_PNOENABLE_SET]);
		pno_enable = *(command + cmdlen + 1) - '0';
		bytes_written = rtw_android_pno_enable(net, pno_enable);
		break;
#endif

	case ANDROID_WIFI_CMD_P2P_DEV_ADDR:
		bytes_written = rtw_android_get_p2p_dev_addr(net, command, priv_cmd.total_len);
		break;
	case ANDROID_WIFI_CMD_P2P_SET_NOA:
		//int skip = strlen(CMD_P2P_SET_NOA) + 1;
		//bytes_written = wl_cfg80211_set_p2p_noa(net, command + skip, priv_cmd.total_len - skip);
		break;
	case ANDROID_WIFI_CMD_P2P_GET_NOA:
		//bytes_written = wl_cfg80211_get_p2p_noa(net, command, priv_cmd.total_len);
		break;
	case ANDROID_WIFI_CMD_P2P_SET_PS:
		//int skip = strlen(CMD_P2P_SET_PS) + 1;
		//bytes_written = wl_cfg80211_set_p2p_ps(net, command + skip, priv_cmd.total_len - skip);
		break;
		
#ifdef CONFIG_IOCTL_CFG80211
	case ANDROID_WIFI_CMD_SET_AP_WPS_P2P_IE:
	{
		int skip = strlen(android_wifi_cmd_str[ANDROID_WIFI_CMD_SET_AP_WPS_P2P_IE]) + 3;
		bytes_written = rtw_cfg80211_set_mgnt_wpsp2pie(net, command + skip, priv_cmd.total_len - skip, *(command + skip - 2) - '0');
		break;
	}
#endif //CONFIG_IOCTL_CFG80211

#ifdef CONFIG_WFD

	case ANDROID_WIFI_CMD_MIRACAST:
		bytes_written = rtw_android_set_miracast_mode(net, command, priv_cmd.total_len);
		break;

	case ANDROID_WIFI_CMD_WFD_ENABLE:
	{
		//	Commented by Albert 2012/07/24
		//	We can enable the WFD function by using the following command:
		//	wpa_cli driver wfd-enable

		pwfd_info = &padapter->wfd_info;
		if( padapter->wdinfo.driver_interface == DRIVER_CFG80211 )
			pwfd_info->wfd_enable = _TRUE;
		break;
	}

	case ANDROID_WIFI_CMD_WFD_DISABLE:
	{
		//	Commented by Albert 2012/07/24
		//	We can disable the WFD function by using the following command:
		//	wpa_cli driver wfd-disable

		pwfd_info = &padapter->wfd_info;
		if( padapter->wdinfo.driver_interface == DRIVER_CFG80211 )
			pwfd_info->wfd_enable = _FALSE;
		break;
	}
	case ANDROID_WIFI_CMD_WFD_SET_TCPPORT:
	{
		//	Commented by Albert 2012/07/24
		//	We can set the tcp port number by using the following command:
		//	wpa_cli driver wfd-set-tcpport = 554

		pwfd_info = &padapter->wfd_info;
		if( padapter->wdinfo.driver_interface == DRIVER_CFG80211 )
		{
			pwfd_info->rtsp_ctrlport = ( u16 ) get_int_from_command( priv_cmd.buf );
	}
		break;
	}
	case ANDROID_WIFI_CMD_WFD_SET_MAX_TPUT:
	{
		break;
	}
	case ANDROID_WIFI_CMD_WFD_SET_DEVTYPE:
	{
		//	Commented by Albert 2012/08/28
		//	Specify the WFD device type ( WFD source/primary sink )

		pwfd_info = &padapter->wfd_info;
		if( padapter->wdinfo.driver_interface == DRIVER_CFG80211 )
		{
			pwfd_info->wfd_device_type = ( u8 ) get_int_from_command( priv_cmd.buf );
			pwfd_info->wfd_device_type &= WFD_DEVINFO_DUAL;
		}
		break;
	}
#endif
	case ANDROID_WIFI_CMD_CHANGE_DTIM:
		{
#ifdef CONFIG_LPS
			u8 dtim;
			u8 *ptr =(u8 *) &priv_cmd.buf;
			
			ptr += 9;//string command length of  "SET_DTIM";

			dtim = rtw_atoi(ptr);

			DBG_871X("DTIM=%d\n", dtim);

			rtw_lps_change_dtim_cmd(padapter, dtim);			
#endif			
		}		
		break;
	case ANDROID_WIFI_CMD_HOSTAPD_SET_MACADDR_ACL:
	{
		padapter->stapriv.acl_list.mode = ( u8 ) get_int_from_command(command);
		DBG_871X("%s ANDROID_WIFI_CMD_HOSTAPD_SET_MACADDR_ACL mode:%d\n", __FUNCTION__, padapter->stapriv.acl_list.mode);
		break;
	}
	case ANDROID_WIFI_CMD_HOSTAPD_ACL_ADD_STA:
	{
		u8 addr[ETH_ALEN] = {0x00};
		macstr2num(addr, command+strlen("HOSTAPD_ACL_ADD_STA")+3);	// 3 is space bar + "=" + space bar these 3 chars
		rtw_acl_add_sta(padapter, addr);
		break;
	}
	case ANDROID_WIFI_CMD_HOSTAPD_ACL_REMOVE_STA:
	{
		u8 addr[ETH_ALEN] = {0x00};
		macstr2num(addr, command+strlen("HOSTAPD_ACL_REMOVE_STA")+3);	// 3 is space bar + "=" + space bar these 3 chars
		rtw_acl_remove_sta(padapter, addr);
		break;
	}
#if defined(CONFIG_GTK_OL) && (LINUX_VERSION_CODE < KERNEL_VERSION(3, 1, 0))
	case ANDROID_WIFI_CMD_GTK_REKEY_OFFLOAD:
		rtw_gtk_offload(net, (u8*)command);
		break;
#endif //CONFIG_GTK_OL		
	case ANDROID_WIFI_CMD_P2P_DISABLE:
	{
#ifdef CONFIG_P2P
		struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;	
		u8 channel, ch_offset;
		u16 bwmode;

		rtw_p2p_enable(padapter, P2P_ROLE_DISABLE);
#endif // CONFIG_P2P
		break;
	}
	default:
		DBG_871X("Unknown PRIVATE command %s - ignored\n", command);
		snprintf(command, 3, "OK");
		bytes_written = strlen("OK");
	}
