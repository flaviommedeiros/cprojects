#ifdef CONFIG_8723AU_AP_MODE
if ((pmlmeinfo->state & 0x03) == MSR_AP) {
		pwps_ie = cfg80211_find_vendor_ie(WLAN_OUI_MICROSOFT,
						  WLAN_OUI_TYPE_MICROSOFT_WPS,
						  cur_network->IEs,
						  cur_network->IELength);

		memcpy(pframe, cur_network->IEs, cur_network->IELength);
		pframe += cur_network->IELength;
		pattrib->pktlen += cur_network->IELength;

		/* retrieve SSID IE from cur_network->Ssid */

		ssid_ie = rtw_get_ie23a(mgmt->u.probe_resp.variable,
					WLAN_EID_SSID, &ssid_ielen,
					pframe - mgmt->u.probe_resp.variable);

		ssid_ielen_diff = cur_network->Ssid.ssid_len - ssid_ielen;

		if (ssid_ie && cur_network->Ssid.ssid_len) {
			uint remainder_ielen;
			u8 *remainder_ie;

			remainder_ie = ssid_ie + 2;

			remainder_ielen = pframe - remainder_ie;

			DBG_8723A_LEVEL(_drv_warning_, "%s(%s): "
					"remainder_ielen > MAX_IE_SZ\n",
					__func__, padapter->pnetdev->name);
			if (remainder_ielen > MAX_IE_SZ)
				remainder_ielen = MAX_IE_SZ;

			memcpy(buf, remainder_ie, remainder_ielen);
			memcpy(remainder_ie + ssid_ielen_diff, buf,
			       remainder_ielen);
			*(ssid_ie + 1) = cur_network->Ssid.ssid_len;
			memcpy(ssid_ie + 2, cur_network->Ssid.ssid,
			       cur_network->Ssid.ssid_len);

			pframe += ssid_ielen_diff;
			pattrib->pktlen += ssid_ielen_diff;
		}
	} else
#endif
	{
		/*  SSID */
		pframe = rtw_set_ie23a(pframe, WLAN_EID_SSID,
				       cur_network->Ssid.ssid_len,
				       cur_network->Ssid.ssid,
				       &pattrib->pktlen);

		/*  supported rates... */
		rate_len = rtw_get_rateset_len23a(cur_network->SupportedRates);
		pframe = rtw_set_ie23a(pframe, WLAN_EID_SUPP_RATES,
				       ((rate_len > 8)? 8: rate_len),
				       cur_network->SupportedRates,
				       &pattrib->pktlen);

		/*  DS parameter set */
		pframe = rtw_set_ie23a(pframe, WLAN_EID_DS_PARAMS, 1,
				       (unsigned char *)&cur_network->DSConfig,
				       &pattrib->pktlen);

		if ((pmlmeinfo->state & 0x03) == MSR_ADHOC) {
			u8 erpinfo = 0;
			u32 ATIMWindow;
			/*  IBSS Parameter Set... */
			/* ATIMWindow = cur->ATIMWindow; */
			ATIMWindow = 0;
			pframe = rtw_set_ie23a(pframe, WLAN_EID_IBSS_PARAMS, 2,
					       (unsigned char *)&ATIMWindow,
					       &pattrib->pktlen);

			/* ERP IE */
			pframe = rtw_set_ie23a(pframe, WLAN_EID_ERP_INFO, 1,
					       &erpinfo, &pattrib->pktlen);
		}

		/*  EXTERNDED SUPPORTED RATE */
		if (rate_len > 8)
			pframe = rtw_set_ie23a(pframe, WLAN_EID_EXT_SUPP_RATES,
					       rate_len - 8,
					       cur_network->SupportedRates + 8,
					       &pattrib->pktlen);

		/* todo:HT for adhoc */
	}
