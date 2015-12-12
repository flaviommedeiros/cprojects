switch (option) {
	case TDLS_ESTABLISHED:
	{
		/* As long as TDLS handshake success, we should set RCR_CBSSID_DATA bit to 0 */
		/* So we can receive all kinds of data frames. */
		u8 sta_band = 0;

		//leave ALL PS when TDLS is established
			rtw_pwr_wakeup(padapter);

		rtw_hal_set_hwreg(padapter, HW_VAR_TDLS_WRCR, 0);
		DBG_871X("Created Direct Link with "MAC_FMT"\n", MAC_ARG(ptdls_sta->hwaddr));

		pmlmeinfo->FW_sta_info[ptdls_sta->mac_id].psta = ptdls_sta;
		/* Set TDLS sta rate. */
		/* Update station supportRate */
		rtw_hal_update_sta_rate_mask(padapter, ptdls_sta);
		if (pmlmeext->cur_channel > 14) {
			if (ptdls_sta->ra_mask & 0xffff000)
				sta_band |= WIRELESS_11_5N ;

			if (ptdls_sta->ra_mask & 0xff0)
				sta_band |= WIRELESS_11A;

			/* 5G band */
			#ifdef CONFIG_80211AC_VHT
			if (ptdls_sta->vhtpriv.vht_option)
				sta_band = WIRELESS_11_5AC;
			#endif
			
		} else {
			if (ptdls_sta->ra_mask & 0xffff000)
				sta_band |= WIRELESS_11_24N;

			if (ptdls_sta->ra_mask & 0xff0)
				sta_band |= WIRELESS_11G;

			if (ptdls_sta->ra_mask & 0x0f)
				sta_band |= WIRELESS_11B;
		}
		ptdls_sta->wireless_mode = sta_band;
		ptdls_sta->raid = rtw_hal_networktype_to_raid(padapter,ptdls_sta);
		set_sta_rate(padapter, ptdls_sta);
		rtw_sta_media_status_rpt(padapter, ptdls_sta, 1);
		/* Sta mode */
		rtw_hal_set_odm_var(padapter, HAL_ODM_STA_INFO, ptdls_sta,_TRUE);
		break;
	}
	case TDLS_ISSUE_PTI:
		ptdls_sta->tdls_sta_state |= TDLS_WAIT_PTR_STATE;
		issue_tdls_peer_traffic_indication(padapter, ptdls_sta);
		_set_timer(&ptdls_sta->pti_timer, TDLS_PTI_TIME);
		break;
#ifdef CONFIG_TDLS_CH_SW		
	case TDLS_CH_SW_RESP:
		_rtw_memset(&txmgmt, 0x00, sizeof(struct tdls_txmgmt));
		txmgmt.status_code = 0;
		_rtw_memcpy(txmgmt.peer, ptdls_sta->hwaddr, ETH_ALEN);

		issue_nulldata(padapter, NULL, 1, 0, 0);

		DBG_871X("issue tdls channel switch response\n");
		issue_tdls_ch_switch_rsp(padapter, &txmgmt, _FALSE);
		resp_sleep = 5;
		rtw_msleep_os(resp_sleep);

		/* If we receive TDLS_CH_SW_REQ at off channel which it's target is AP's channel */
		/* then we just SelectChannel to AP's channel*/
		if (padapter->mlmeextpriv.cur_channel == pchsw_info->off_ch_num) {
			SelectChannel(padapter, padapter->mlmeextpriv.cur_channel);
			issue_nulldata(padapter, NULL, 0, 0, 0);
			pchsw_info->ch_sw_state &= ~(TDLS_PEER_AT_OFF_STATE);
			ATOMIC_SET(&pchsw_info->chsw_on, _FALSE);
			break;
		}

		_set_timer(&ptdls_sta->delay_timer, pmlmeinfo->bcn_interval - 40);

		/* Continue following actions */

	case TDLS_CH_SW:
		issue_nulldata(padapter, NULL, 1, 0, 0);
		_set_timer(&ptdls_sta->ch_sw_timer, (u32)(ptdls_sta->ch_switch_timeout)/1000);

		setchtime = rtw_systime_to_ms(rtw_get_current_time());
		SelectChannel(padapter, pchsw_info->off_ch_num);
		setchtime = rtw_systime_to_ms(rtw_get_current_time()) - setchtime;
		setchtime += resp_sleep;

		if (pmlmeext->cur_channel != rtw_get_oper_ch(padapter))
			issue_nulldata(padapter, NULL, 0, 0, 0);
		pchsw_info->ch_sw_state &= ~(TDLS_PEER_AT_OFF_STATE);

		if ((u32)ptdls_sta->ch_switch_time/1000 > setchtime)
			wait_time = (u32)ptdls_sta->ch_switch_time/1000 - setchtime;
		else
			wait_time = 0;

		if (wait_time > 0)
			rtw_msleep_os(wait_time);

		issue_nulldata_to_TDLS_peer_STA(ptdls_sta->padapter, ptdls_sta->hwaddr, 0, 0, 0);
		issue_nulldata_to_TDLS_peer_STA(ptdls_sta->padapter, ptdls_sta->hwaddr, 0, 0, 0);

		break;
	case TDLS_CH_SW_BACK:
		pchsw_info->ch_sw_state &= ~(TDLS_PEER_AT_OFF_STATE | TDLS_WAIT_CH_RSP_STATE);
		ATOMIC_SET(&pchsw_info->chsw_on, _FALSE);
		SelectChannel(padapter, padapter->mlmeextpriv.cur_channel);
		issue_nulldata(padapter, NULL, 0, 0, 0);
		break;
#endif		
	case TDLS_RS_RCR:
		rtw_hal_set_hwreg(padapter, HW_VAR_TDLS_RS_RCR, 0);
		DBG_871X("wirte REG_RCR, set bit6 on\n");
		break;
	case TDLS_TEAR_STA:
#ifdef CONFIG_TDLS_CH_SW	
		if (_rtw_memcmp(TDLSoption->addr, pchsw_info->addr, ETH_ALEN) == _TRUE) {
			pchsw_info->ch_sw_state &= ~(TDLS_CH_SW_INITIATOR_STATE |
										TDLS_CH_SWITCH_ON_STATE |
										TDLS_PEER_AT_OFF_STATE);
			ATOMIC_SET(&pchsw_info->chsw_on, _FALSE);
			_rtw_memset(pchsw_info->addr, 0x00, ETH_ALEN);
		}
#endif		
		rtw_sta_media_status_rpt(padapter, ptdls_sta, 0);
		free_tdls_sta(padapter, ptdls_sta);
		break;			
	}
