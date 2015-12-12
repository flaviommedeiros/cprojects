switch (info_element->id) {
		case MFIE_TYPE_SSID:
			if (ieee80211_is_empty_essid(info_element->data,
						     info_element->len)) {
				network->flags |= NETWORK_EMPTY_ESSID;
				break;
			}

			network->ssid_len = min(info_element->len,
						(u8) IW_ESSID_MAX_SIZE);
			memcpy(network->ssid, info_element->data, network->ssid_len);
			if (network->ssid_len < IW_ESSID_MAX_SIZE)
				memset(network->ssid + network->ssid_len, 0,
				       IW_ESSID_MAX_SIZE - network->ssid_len);

			IEEE80211_DEBUG_MGMT("MFIE_TYPE_SSID: '%s' len=%d.\n",
					     network->ssid, network->ssid_len);
			break;

		case MFIE_TYPE_RATES:
#ifdef CONFIG_IEEE80211_DEBUG
			p = rates_str;
#endif
			network->rates_len = min(info_element->len,
						 MAX_RATES_LENGTH);
			for (i = 0; i < network->rates_len; i++) {
				network->rates[i] = info_element->data[i];
#ifdef CONFIG_IEEE80211_DEBUG
				p += snprintf(p, sizeof(rates_str) -
					      (p - rates_str), "%02X ",
					      network->rates[i]);
#endif
				if (ieee80211_is_ofdm_rate
				    (info_element->data[i])) {
					network->flags |= NETWORK_HAS_OFDM;
					if (info_element->data[i] &
					    IEEE80211_BASIC_RATE_MASK)
						network->flags &=
						    ~NETWORK_HAS_CCK;
				}
			}

			IEEE80211_DEBUG_MGMT("MFIE_TYPE_RATES: '%s' (%d)\n",
					     rates_str, network->rates_len);
			break;

		case MFIE_TYPE_RATES_EX:
#ifdef CONFIG_IEEE80211_DEBUG
			p = rates_str;
#endif
			network->rates_ex_len = min(info_element->len,
						    MAX_RATES_EX_LENGTH);
			for (i = 0; i < network->rates_ex_len; i++) {
				network->rates_ex[i] = info_element->data[i];
#ifdef CONFIG_IEEE80211_DEBUG
				p += snprintf(p, sizeof(rates_str) -
					      (p - rates_str), "%02X ",
					      network->rates[i]);
#endif
				if (ieee80211_is_ofdm_rate
				    (info_element->data[i])) {
					network->flags |= NETWORK_HAS_OFDM;
					if (info_element->data[i] &
					    IEEE80211_BASIC_RATE_MASK)
						network->flags &=
						    ~NETWORK_HAS_CCK;
				}
			}

			IEEE80211_DEBUG_MGMT("MFIE_TYPE_RATES_EX: '%s' (%d)\n",
					     rates_str, network->rates_ex_len);
			break;

		case MFIE_TYPE_DS_SET:
			IEEE80211_DEBUG_MGMT("MFIE_TYPE_DS_SET: %d\n",
					     info_element->data[0]);
			network->channel = info_element->data[0];
			break;

		case MFIE_TYPE_FH_SET:
			IEEE80211_DEBUG_MGMT("MFIE_TYPE_FH_SET: ignored\n");
			break;

		case MFIE_TYPE_CF_SET:
			IEEE80211_DEBUG_MGMT("MFIE_TYPE_CF_SET: ignored\n");
			break;

		case MFIE_TYPE_TIM:
			if(info_element->len < 4)
				break;

			network->tim.tim_count = info_element->data[0];
			network->tim.tim_period = info_element->data[1];

                        network->dtim_period = info_element->data[1];
                        if(ieee->state != IEEE80211_LINKED)
                                break;
#if 0
                        network->last_dtim_sta_time[0] = stats->mac_time[0];
#else
			//we use jiffies for legacy Power save
			network->last_dtim_sta_time[0] = jiffies;
#endif
                        network->last_dtim_sta_time[1] = stats->mac_time[1];

                        network->dtim_data = IEEE80211_DTIM_VALID;

                        if(info_element->data[0] != 0)
                                break;

                        if(info_element->data[2] & 1)
                                network->dtim_data |= IEEE80211_DTIM_MBCAST;

                        offset = (info_element->data[2] >> 1)*2;

                        //printk("offset1:%x aid:%x\n",offset, ieee->assoc_id);

                        if(ieee->assoc_id < 8*offset ||
                                ieee->assoc_id > 8*(offset + info_element->len -3))

                                break;

                        offset = (ieee->assoc_id / 8) - offset;// + ((aid % 8)? 0 : 1) ;

                        if(info_element->data[3+offset] & (1<<(ieee->assoc_id%8)))
                                network->dtim_data |= IEEE80211_DTIM_UCAST;

			//IEEE80211_DEBUG_MGMT("MFIE_TYPE_TIM: partially ignored\n");
			break;

		case MFIE_TYPE_ERP:
			network->erp_value = info_element->data[0];
			network->flags |= NETWORK_HAS_ERP_VALUE;
			IEEE80211_DEBUG_MGMT("MFIE_TYPE_ERP_SET: %d\n",
					     network->erp_value);
			break;
		case MFIE_TYPE_IBSS_SET:
			network->atim_window = info_element->data[0];
			IEEE80211_DEBUG_MGMT("MFIE_TYPE_IBSS_SET: %d\n",
					     network->atim_window);
			break;

		case MFIE_TYPE_CHALLENGE:
			IEEE80211_DEBUG_MGMT("MFIE_TYPE_CHALLENGE: ignored\n");
			break;

		case MFIE_TYPE_GENERIC:
			IEEE80211_DEBUG_MGMT("MFIE_TYPE_GENERIC: %d bytes\n",
					     info_element->len);
			if (!ieee80211_parse_qos_info_param_IE(info_element,
							       network))
				break;

			if (info_element->len >= 4 &&
			    info_element->data[0] == 0x00 &&
			    info_element->data[1] == 0x50 &&
			    info_element->data[2] == 0xf2 &&
			    info_element->data[3] == 0x01) {
				network->wpa_ie_len = min(info_element->len + 2,
							  MAX_WPA_IE_LEN);
				memcpy(network->wpa_ie, info_element,
				       network->wpa_ie_len);
				break;
			}

#ifdef THOMAS_TURBO
                        if (info_element->len == 7 &&
                            info_element->data[0] == 0x00 &&
                            info_element->data[1] == 0xe0 &&
                            info_element->data[2] == 0x4c &&
                            info_element->data[3] == 0x01 &&
                            info_element->data[4] == 0x02) {
                                network->Turbo_Enable = 1;
                        }
#endif

                        //for HTcap and HTinfo parameters
			if(tmp_htcap_len == 0){
				if(info_element->len >= 4 &&
				   info_element->data[0] == 0x00 &&
				   info_element->data[1] == 0x90 &&
				   info_element->data[2] == 0x4c &&
				   info_element->data[3] == 0x033){

						tmp_htcap_len = min(info_element->len,(u8)MAX_IE_LEN);
				   		if(tmp_htcap_len != 0){
				   			network->bssht.bdHTSpecVer = HT_SPEC_VER_EWC;
							network->bssht.bdHTCapLen = tmp_htcap_len > sizeof(network->bssht.bdHTCapBuf)?\
								sizeof(network->bssht.bdHTCapBuf):tmp_htcap_len;
							memcpy(network->bssht.bdHTCapBuf,info_element->data,network->bssht.bdHTCapLen);
				   		}
				}
				if(tmp_htcap_len != 0)
					network->bssht.bdSupportHT = true;
				else
					network->bssht.bdSupportHT = false;
			}


			if(tmp_htinfo_len == 0){
				if(info_element->len >= 4 &&
					info_element->data[0] == 0x00 &&
				   	info_element->data[1] == 0x90 &&
				   	info_element->data[2] == 0x4c &&
				   	info_element->data[3] == 0x034){

						tmp_htinfo_len = min(info_element->len,(u8)MAX_IE_LEN);
						if(tmp_htinfo_len != 0){
							network->bssht.bdHTSpecVer = HT_SPEC_VER_EWC;
							if(tmp_htinfo_len){
								network->bssht.bdHTInfoLen = tmp_htinfo_len > sizeof(network->bssht.bdHTInfoBuf)?\
									sizeof(network->bssht.bdHTInfoBuf):tmp_htinfo_len;
								memcpy(network->bssht.bdHTInfoBuf,info_element->data,network->bssht.bdHTInfoLen);
							}

						}

				}
			}

			if(ieee->aggregation){
				if(network->bssht.bdSupportHT){
					if(info_element->len >= 4 &&
						info_element->data[0] == 0x00 &&
						info_element->data[1] == 0xe0 &&
						info_element->data[2] == 0x4c &&
						info_element->data[3] == 0x02){

						ht_realtek_agg_len = min(info_element->len,(u8)MAX_IE_LEN);
						memcpy(ht_realtek_agg_buf,info_element->data,info_element->len);

					}
					if(ht_realtek_agg_len >= 5){
						network->bssht.bdRT2RTAggregation = true;

						if((ht_realtek_agg_buf[4] == 1) && (ht_realtek_agg_buf[5] & 0x02))
						network->bssht.bdRT2RTLongSlotTime = true;
					}
				}

			}

			//if(tmp_htcap_len !=0  ||  tmp_htinfo_len != 0)
			{
				if((info_element->len >= 3 &&
					 info_element->data[0] == 0x00 &&
					 info_element->data[1] == 0x05 &&
					 info_element->data[2] == 0xb5) ||
					 (info_element->len >= 3 &&
					 info_element->data[0] == 0x00 &&
					 info_element->data[1] == 0x0a &&
					 info_element->data[2] == 0xf7) ||
					 (info_element->len >= 3 &&
					 info_element->data[0] == 0x00 &&
					 info_element->data[1] == 0x10 &&
					 info_element->data[2] == 0x18)){

						network->broadcom_cap_exist = true;

				}
			}
#if 0
			if (tmp_htcap_len !=0)
				{
					u16 cap_ext = ((PHT_CAPABILITY_ELE)&info_element->data[0])->ExtHTCapInfo;
					if ((cap_ext & 0x0c00) == 0x0c00)
						{
							network->ralink_cap_exist = true;
						}
				}
#endif
			if(info_element->len >= 3 &&
				info_element->data[0] == 0x00 &&
				info_element->data[1] == 0x0c &&
				info_element->data[2] == 0x43)
			{
				network->ralink_cap_exist = true;
			}
			else
				network->ralink_cap_exist = false;
			//added by amy for atheros AP
			if((info_element->len >= 3 &&
				info_element->data[0] == 0x00 &&
				info_element->data[1] == 0x03 &&
				info_element->data[2] == 0x7f) ||
				(info_element->len >= 3 &&
				info_element->data[0] == 0x00 &&
				info_element->data[1] == 0x13 &&
				info_element->data[2] == 0x74))
			{
				printk("========>%s(): athros AP is exist\n",__FUNCTION__);
				network->atheros_cap_exist = true;
			}
			else
				network->atheros_cap_exist = false;

			if(info_element->len >= 3 &&
				info_element->data[0] == 0x00 &&
				info_element->data[1] == 0x40 &&
				info_element->data[2] == 0x96)
			{
				network->cisco_cap_exist = true;
			}
			else
				network->cisco_cap_exist = false;
			//added by amy for LEAP of cisco
			if(info_element->len > 4 &&
				info_element->data[0] == 0x00 &&
				info_element->data[1] == 0x40 &&
				info_element->data[2] == 0x96 &&
				info_element->data[3] == 0x01)
			{
				if(info_element->len == 6)
				{
					memcpy(network->CcxRmState, &info_element[4], 2);
					if(network->CcxRmState[0] != 0)
					{
						network->bCcxRmEnable = true;
					}
					else
						network->bCcxRmEnable = false;
					//
					// CCXv4 Table 59-1 MBSSID Masks.
					//
					network->MBssidMask = network->CcxRmState[1] & 0x07;
					if(network->MBssidMask != 0)
					{
						network->bMBssidValid = true;
						network->MBssidMask = 0xff << (network->MBssidMask);
						cpMacAddr(network->MBssid, network->bssid);
						network->MBssid[5] &= network->MBssidMask;
					}
					else
					{
						network->bMBssidValid = false;
					}
				}
				else
				{
					network->bCcxRmEnable = false;
				}
			}
			if(info_element->len > 4  &&
				info_element->data[0] == 0x00 &&
				info_element->data[1] == 0x40 &&
				info_element->data[2] == 0x96 &&
				info_element->data[3] == 0x03)
			{
				if(info_element->len == 5)
				{
					network->bWithCcxVerNum = true;
					network->BssCcxVerNumber = info_element->data[4];
				}
				else
				{
					network->bWithCcxVerNum = false;
					network->BssCcxVerNumber = 0;
				}
			}
			break;

		case MFIE_TYPE_RSN:
			IEEE80211_DEBUG_MGMT("MFIE_TYPE_RSN: %d bytes\n",
					     info_element->len);
			network->rsn_ie_len = min(info_element->len + 2,
						  MAX_WPA_IE_LEN);
			memcpy(network->rsn_ie, info_element,
			       network->rsn_ie_len);
			break;

                        //HT related element.
		case MFIE_TYPE_HT_CAP:
			IEEE80211_DEBUG_SCAN("MFIE_TYPE_HT_CAP: %d bytes\n",
					     info_element->len);
			tmp_htcap_len = min(info_element->len,(u8)MAX_IE_LEN);
			if(tmp_htcap_len != 0){
				network->bssht.bdHTSpecVer = HT_SPEC_VER_EWC;
				network->bssht.bdHTCapLen = tmp_htcap_len > sizeof(network->bssht.bdHTCapBuf)?\
					sizeof(network->bssht.bdHTCapBuf):tmp_htcap_len;
				memcpy(network->bssht.bdHTCapBuf,info_element->data,network->bssht.bdHTCapLen);

				//If peer is HT, but not WMM, call QosSetLegacyWMMParamWithHT()
				// windows driver will update WMM parameters each beacon received once connected
                                // Linux driver is a bit different.
				network->bssht.bdSupportHT = true;
			}
			else
				network->bssht.bdSupportHT = false;
			break;


		case MFIE_TYPE_HT_INFO:
			IEEE80211_DEBUG_SCAN("MFIE_TYPE_HT_INFO: %d bytes\n",
					     info_element->len);
			tmp_htinfo_len = min(info_element->len,(u8)MAX_IE_LEN);
			if(tmp_htinfo_len){
				network->bssht.bdHTSpecVer = HT_SPEC_VER_IEEE;
				network->bssht.bdHTInfoLen = tmp_htinfo_len > sizeof(network->bssht.bdHTInfoBuf)?\
					sizeof(network->bssht.bdHTInfoBuf):tmp_htinfo_len;
				memcpy(network->bssht.bdHTInfoBuf,info_element->data,network->bssht.bdHTInfoLen);
			}
			break;

		case MFIE_TYPE_AIRONET:
			IEEE80211_DEBUG_SCAN("MFIE_TYPE_AIRONET: %d bytes\n",
					     info_element->len);
			if(info_element->len >IE_CISCO_FLAG_POSITION)
			{
				network->bWithAironetIE = true;

				// CCX 1 spec v1.13, A01.1 CKIP Negotiation (page23):
				// "A Cisco access point advertises support for CKIP in beacon and probe response packets,
				//  by adding an Aironet element and setting one or both of the CKIP negotiation bits."
				if(	(info_element->data[IE_CISCO_FLAG_POSITION]&SUPPORT_CKIP_MIC)	||
					(info_element->data[IE_CISCO_FLAG_POSITION]&SUPPORT_CKIP_PK)	)
				{
		 			network->bCkipSupported = true;
				}
				else
				{
					network->bCkipSupported = false;
				}
			}
			else
			{
				network->bWithAironetIE = false;
		 		network->bCkipSupported = false;
			}
			break;
		case MFIE_TYPE_QOS_PARAMETER:
			printk(KERN_ERR
			       "QoS Error need to parse QOS_PARAMETER IE\n");
			break;

#ifdef ENABLE_DOT11D
		case MFIE_TYPE_COUNTRY:
			IEEE80211_DEBUG_SCAN("MFIE_TYPE_COUNTRY: %d bytes\n",
					     info_element->len);
			//printk("=====>Receive <%s> Country IE\n",network->ssid);
			ieee80211_extract_country_ie(ieee, info_element, network, network->bssid);//addr2 is same as addr3 when from an AP
			break;
#endif
/* TODO */
#if 0
			/* 802.11h */
		case MFIE_TYPE_POWER_CONSTRAINT:
			network->power_constraint = info_element->data[0];
			network->flags |= NETWORK_HAS_POWER_CONSTRAINT;
			break;

		case MFIE_TYPE_CSA:
			network->power_constraint = info_element->data[0];
			network->flags |= NETWORK_HAS_CSA;
			break;

		case MFIE_TYPE_QUIET:
			network->quiet.count = info_element->data[0];
			network->quiet.period = info_element->data[1];
			network->quiet.duration = info_element->data[2];
			network->quiet.offset = info_element->data[3];
			network->flags |= NETWORK_HAS_QUIET;
			break;

		case MFIE_TYPE_IBSS_DFS:
			if (network->ibss_dfs)
				break;
			network->ibss_dfs = kmemdup(info_element->data,
						    info_element->len,
						    GFP_ATOMIC);
			if (!network->ibss_dfs)
				return 1;
			network->flags |= NETWORK_HAS_IBSS_DFS;
			break;

		case MFIE_TYPE_TPC_REPORT:
			network->tpc_report.transmit_power =
			    info_element->data[0];
			network->tpc_report.link_margin = info_element->data[1];
			network->flags |= NETWORK_HAS_TPC_REPORT;
			break;
#endif
		default:
			IEEE80211_DEBUG_MGMT
			    ("Unsupported info element: %s (%d)\n",
			     get_info_element_string(info_element->id),
			     info_element->id);
			break;
		}
