#ifdef RTCONFIG_WIRELESSREPEATER
if(disconn_case[wan_unit] == CASE_AP_DISCONN){
			if(disconn_case_old[wan_unit] == CASE_AP_DISCONN)
				return;
			disconn_case_old[wan_unit] = CASE_AP_DISCONN;

			logmessage(log_title, "Don't connect the AP yet.");
		}
		else
#endif
		if(disconn_case[wan_unit] == CASE_DISWAN){
			if(disconn_case_old[wan_unit] == CASE_DISWAN)
				return;
			disconn_case_old[wan_unit] = CASE_DISWAN;

			logmessage(log_title, "Ethernet link down.");
		}
		else if(disconn_case[wan_unit] == CASE_PPPFAIL){
			if(disconn_case_old[wan_unit] == CASE_PPPFAIL)
				return;
			disconn_case_old[wan_unit] = CASE_PPPFAIL;

			if(ppp_fail_state == WAN_STOPPED_REASON_PPP_AUTH_FAIL)
				logmessage(log_title, "VPN authentication failed.");
			else if(ppp_fail_state == WAN_STOPPED_REASON_PPP_NO_ACTIVITY)
				logmessage(log_title, "No response from ISP.");
			else
				logmessage(log_title, "Fail to connect with some issues.");
		}
		else if(disconn_case[wan_unit] == CASE_DHCPFAIL){
			if(disconn_case_old[wan_unit] == CASE_DHCPFAIL)
				return;
			disconn_case_old[wan_unit] = CASE_DHCPFAIL;

			if(!strcmp(wan_proto, "dhcp")
#ifdef RTCONFIG_WIRELESSREPEATER
					|| sw_mode == SW_MODE_HOTSPOT
#endif
					)
				logmessage(log_title, "ISP's DHCP did not function properly.");
#if 0
			else
				logmessage(log_title, "Detected that the WAN Connection Type was PPPoE. But the PPPoE Setting was not complete.");
#endif
		}
		else if(disconn_case[wan_unit] == CASE_MISROUTE){
			if(disconn_case_old[wan_unit] == CASE_MISROUTE)
				return;
			disconn_case_old[wan_unit] = CASE_MISROUTE;

			logmessage(log_title, "The router's ip was the same as gateway's ip. It led to your packages couldn't dispatch to internet correctly.");
		}
		else if(disconn_case[wan_unit] == CASE_THESAMESUBNET){
			if(disconn_case_old[wan_unit] == CASE_THESAMESUBNET)
				return;
			disconn_case_old[wan_unit] = CASE_THESAMESUBNET;

			logmessage(log_title, "The LAN's subnet may be the same with the WAN's subnet.");
		}
#ifdef RTCONFIG_USB_MODEM
#if (defined(RTCONFIG_JFFS2) || defined(RTCONFIG_BRCM_NAND_JFFS2) || defined(RTCONFIG_UBIFS))
		else if(disconn_case[wan_unit] == CASE_DATALIMIT){
			if(disconn_case_old[wan_unit] == CASE_DATALIMIT)
				return;
			disconn_case_old[wan_unit] = CASE_DATALIMIT;

			logmessage(log_title, "The Data is at limit.");
		}
#endif
#endif
		else{	// disconn_case[wan_unit] == CASE_OTHERS
			if(disconn_case_old[wan_unit] == CASE_OTHERS)
				return;
			disconn_case_old[wan_unit] = CASE_OTHERS;

			logmessage(log_title, "WAN was exceptionally disconnected.");
		}
