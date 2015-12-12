if (1
#ifdef CONFIG_BT_COEXIST
			&& (((rtw_btcoex_IsBtControlLps(padapter) == _FALSE)
#ifdef CONFIG_P2P_PS
					&& (pwdinfo->opp_ps == 0)
#endif // CONFIG_P2P_PS
					)
				|| ((rtw_btcoex_IsBtControlLps(padapter) == _TRUE)
					&& (rtw_btcoex_IsLpsOn(padapter) == _FALSE))
				)
#else // !CONFIG_BT_COEXIST
#ifdef CONFIG_P2P_PS
			&& (pwdinfo->opp_ps == 0)
#endif // CONFIG_P2P_PS
#endif // !CONFIG_BT_COEXIST
			)
		{
			DBG_871X(FUNC_ADPT_FMT" Leave 802.11 power save - %s\n",
				FUNC_ADPT_ARG(padapter), msg);

			if (pwrpriv->lps_leave_cnts < UINT_MAX)
				pwrpriv->lps_leave_cnts++;
			else
				pwrpriv->lps_leave_cnts = 0;
#ifdef CONFIG_TDLS
			_enter_critical_bh(&pstapriv->sta_hash_lock, &irqL);

			for(i=0; i< NUM_STA; i++)
			{
				phead = &(pstapriv->sta_hash[i]);
				plist = get_next(phead);

				while ((rtw_end_of_queue_search(phead, plist)) == _FALSE)
				{
					ptdls_sta = LIST_CONTAINOR(plist, struct sta_info, hash_list);

					if( ptdls_sta->tdls_sta_state & TDLS_LINKED_STATE )
						issue_nulldata_to_TDLS_peer_STA(padapter, ptdls_sta->hwaddr, 0, 0, 0);
					plist = get_next(plist);
				}
			}

			_exit_critical_bh(&pstapriv->sta_hash_lock, &irqL);
#endif //CONFIG_TDLS

			pwrpriv->pwr_mode = ps_mode;
			rtw_set_rpwm(padapter, PS_STATE_S4);
			
#if defined(CONFIG_WOWLAN) || defined(CONFIG_AP_WOWLAN) || defined(CONFIG_P2P_WOWLAN)
			if (pwrpriv->wowlan_mode == _TRUE ||
					pwrpriv->wowlan_ap_mode == _TRUE ||
					pwrpriv->wowlan_p2p_mode == _TRUE)
			{
				u32 start_time, delay_ms;
				u8 val8;
				delay_ms = 20;
				start_time = rtw_get_current_time();
				do { 
					rtw_hal_get_hwreg(padapter, HW_VAR_SYS_CLKR, &val8);
					if (!(val8 & BIT(4))){ //0x08 bit4 =1 --> in 32k, bit4 = 0 --> leave 32k
						pwrpriv->cpwm = PS_STATE_S4;
						break;
					}
					if (rtw_get_passing_time_ms(start_time) > delay_ms)
					{
						DBG_871X("%s: Wait for FW 32K leave more than %u ms!!!\n", 
								__FUNCTION__, delay_ms);
						pdbgpriv->dbg_wow_leave_ps_fail_cnt++;
						break;
					}
					rtw_usleep_os(100);
				} while (1); 
			}
#endif
			rtw_hal_set_hwreg(padapter, HW_VAR_H2C_FW_PWRMODE, (u8 *)(&ps_mode));
			pwrpriv->bFwCurrentInPSMode = _FALSE;

#ifdef CONFIG_BT_COEXIST
			rtw_btcoex_LpsNotify(padapter, ps_mode);
#endif // CONFIG_BT_COEXIST
		}
