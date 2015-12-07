#ifdef RTCONFIG_WIRELESSREPEATER
if(sw_mode == SW_MODE_HOTSPOT){
		if(wan_state == WAN_STATE_STOPPED) {
			if(wan_sbstate == WAN_STOPPED_REASON_INVALID_IPADDR)
				disconn_case[wan_unit] = CASE_THESAMESUBNET;
			else disconn_case[wan_unit] = CASE_DHCPFAIL;
			return DISCONN;
		}
		else if(wan_state == WAN_STATE_INITIALIZING){
			disconn_case[wan_unit] = CASE_DHCPFAIL;
			return DISCONN;
		}
		else if(wan_state == WAN_STATE_CONNECTING){
			disconn_case[wan_unit] = CASE_DHCPFAIL;
			return DISCONN;
		}
		else if(wan_state == WAN_STATE_DISCONNECTED){
			disconn_case[wan_unit] = CASE_DHCPFAIL;
			return DISCONN;
		}
	}
	else
#endif
	// Start chk_proto() in SW_MODE_ROUTER.
#ifdef RTCONFIG_USB_MODEM
	if (dualwan_unit__usbif(wan_unit)) {
#if (defined(RTCONFIG_JFFS2) || defined(RTCONFIG_BRCM_NAND_JFFS2) || defined(RTCONFIG_UBIFS))
		unsigned long long rx, tx;
		unsigned long long total, alert, limit;
		char buff[128];

		eval("modem_status.sh", "bytes");

		rx = strtoull(nvram_safe_get("modem_bytes_rx"), NULL, 10);
		tx = strtoull(nvram_safe_get("modem_bytes_tx"), NULL, 10);
		alert = strtoull(nvram_safe_get("modem_bytes_data_warning"), NULL, 10);
		limit = strtoull(nvram_safe_get("modem_bytes_data_limit"), NULL, 10);

		total = rx+tx;

		if(limit > 0 && total >= limit){
			if(wan_state != WAN_STATE_STOPPED || nvram_get_int(nvram_sbstate[wan_unit]) != WAN_STOPPED_REASON_DATALIMIT){
				csprintf("wanduck(%d): chk_proto() detect the data limit.\n", wan_unit);
				record_wan_state_nvram(wan_unit, WAN_STATE_STOPPED, WAN_STOPPED_REASON_DATALIMIT, -1);
			}

			if(nvram_get_int("modem_sms_limit") == 1 && nvram_get_int("modem_sms_limit_send") == 0){
				snprintf(buff, 128, "start_sendSMS limit");
				nvram_set("freeze_duck", "5");
				notify_rc(buff);
				nvram_set("modem_sms_limit_send", "1");
				// if send the limit SMS, the alert SMS is not needed.
				nvram_set("modem_sms_alert_send", "1");
			}

			return DISCONN;
		}

		if(alert > 0 && total >= alert){
			if(nvram_get_int("modem_sms_limit") == 1 && nvram_get_int("modem_sms_alert_send") == 0){
				snprintf(buff, 128, "start_sendSMS alert");
				nvram_set("freeze_duck", "5");
				notify_rc(buff);
				nvram_set("modem_sms_alert_send", "1");
			}
		}
#endif

		if(wan_state == WAN_STATE_INITIALIZING){
			disconn_case[wan_unit] = CASE_PPPFAIL;
			return DISCONN;
		}
		else if(wan_state == WAN_STATE_CONNECTING){
			ppp_fail_state = pppstatus();

			if(ppp_fail_state == WAN_STOPPED_REASON_PPP_AUTH_FAIL)
				record_wan_state_nvram(wan_unit, -1, -1, WAN_AUXSTATE_PPP_AUTH_FAIL);

			disconn_case[wan_unit] = CASE_PPPFAIL;
			return DISCONN;
		}
		else if(wan_state == WAN_STATE_DISCONNECTED){
			disconn_case[wan_unit] = CASE_PPPFAIL;
			return DISCONN;
		}
		else if(wan_state == WAN_STATE_STOPPED){
			if(wan_sbstate == WAN_STOPPED_REASON_INVALID_IPADDR)
				disconn_case[wan_unit] = CASE_THESAMESUBNET;
			else if(!strcmp(wan_proto, "dhcp"))
				disconn_case[wan_unit] = CASE_DHCPFAIL;
			else
				disconn_case[wan_unit] = CASE_PPPFAIL;
			return DISCONN;
		}
#if (defined(RTCONFIG_JFFS2) || defined(RTCONFIG_BRCM_NAND_JFFS2) || defined(RTCONFIG_UBIFS))
		else if(wan_sbstate == WAN_STOPPED_REASON_DATALIMIT){
			disconn_case[wan_unit] = CASE_DATALIMIT;
			return DISCONN;
		}
#endif
	}
	else
#endif
	if(!strcmp(wan_proto, "dhcp")
			|| !strcmp(wan_proto, "static")){
		if(wan_state == WAN_STATE_STOPPED) {
			if(wan_sbstate == WAN_STOPPED_REASON_INVALID_IPADDR)
				disconn_case[wan_unit] = CASE_THESAMESUBNET;
			else disconn_case[wan_unit] = CASE_DHCPFAIL;
			return DISCONN;
		}
		else if(wan_state == WAN_STATE_INITIALIZING){
			disconn_case[wan_unit] = CASE_DHCPFAIL;
			return DISCONN;
		}
		else if(wan_state == WAN_STATE_CONNECTING){
#if defined(RTCONFIG_WANRED_LED)
			int r = CASE_DHCPFAIL, v = DISCONN;

			if (!strcmp(wan_proto, "static") && link_wan[wan_unit]) {
				r = CASE_NONE;
				v = CONNED;
			}

			disconn_case[wan_unit] = r;
			return v;
#else
			disconn_case[wan_unit] = CASE_DHCPFAIL;
			return DISCONN;
#endif
		}
		else if(wan_state == WAN_STATE_DISCONNECTED){
			disconn_case[wan_unit] = CASE_DHCPFAIL;
			return DISCONN;
		}
	}
	else if(!strcmp(wan_proto, "pppoe")
			|| !strcmp(wan_proto, "pptp")
			|| !strcmp(wan_proto, "l2tp")
			){
		ppp_fail_state = pppstatus();

		if(wan_state != WAN_STATE_CONNECTED
				&& ppp_fail_state == WAN_STOPPED_REASON_PPP_LACK_ACTIVITY){
			// PPP is into the idle mode.
			if(wan_state == WAN_STATE_STOPPED) // Sometimes ip_down() didn't set it.
				record_wan_state_nvram(wan_unit, -1, WAN_STOPPED_REASON_PPP_LACK_ACTIVITY, -1);
		}
		else if(wan_state == WAN_STATE_INITIALIZING){
			disconn_case[wan_unit] = CASE_PPPFAIL;
			return DISCONN;
		}
		else if(wan_state == WAN_STATE_CONNECTING){
			if(ppp_fail_state == WAN_STOPPED_REASON_PPP_AUTH_FAIL)
				record_wan_state_nvram(wan_unit, -1, -1, WAN_AUXSTATE_PPP_AUTH_FAIL);

			disconn_case[wan_unit] = CASE_PPPFAIL;
			return DISCONN;
		}
		else if(wan_state == WAN_STATE_DISCONNECTED){
			disconn_case[wan_unit] = CASE_PPPFAIL;
			return DISCONN;
		}
		else if(wan_state == WAN_STATE_STOPPED){
			disconn_case[wan_unit] = CASE_PPPFAIL;
			return DISCONN;
		}
	}
