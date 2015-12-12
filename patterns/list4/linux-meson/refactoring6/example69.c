if ((PS_RDY_CHECK(padapter) && check_fwstate(&padapter->mlmepriv, WIFI_ASOC_STATE))
#ifdef CONFIG_BT_COEXIST
			|| ((rtw_btcoex_IsBtControlLps(padapter) == _TRUE)
				&& (rtw_btcoex_IsLpsOn(padapter) == _TRUE))
#endif
#ifdef CONFIG_P2P_WOWLAN
			||( _TRUE == pwrpriv->wowlan_p2p_mode)
#endif //CONFIG_P2P_WOWLAN
			)
		{
			u8 pslv;

			DBG_871X(FUNC_ADPT_FMT" Enter 802.11 power save - %s\n",
				FUNC_ADPT_ARG(padapter), msg);

			if (pwrpriv->lps_enter_cnts < UINT_MAX)
				pwrpriv->lps_enter_cnts++;
			else
				pwrpriv->lps_enter_cnts = 0;
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
						issue_nulldata_to_TDLS_peer_STA(padapter, ptdls_sta->hwaddr, 1, 0, 0);
					plist = get_next(plist);
				}
			}

			_exit_critical_bh(&pstapriv->sta_hash_lock, &irqL);
#endif //CONFIG_TDLS

#ifdef CONFIG_BT_COEXIST
			rtw_btcoex_LpsNotify(padapter, ps_mode);
#endif // CONFIG_BT_COEXIST

			pwrpriv->bFwCurrentInPSMode = _TRUE;
			pwrpriv->pwr_mode = ps_mode;
			pwrpriv->smart_ps = smart_ps;
			pwrpriv->bcn_ant_mode = bcn_ant_mode;
			rtw_hal_set_hwreg(padapter, HW_VAR_H2C_FW_PWRMODE, (u8 *)(&ps_mode));

#ifdef CONFIG_P2P_PS
			// Set CTWindow after LPS
			if(pwdinfo->opp_ps == 1)
				p2p_ps_wk_cmd(padapter, P2P_PS_ENABLE, 0);
#endif //CONFIG_P2P_PS

			pslv = PS_STATE_S2;
#ifdef CONFIG_LPS_LCLK
			if (pwrpriv->alives == 0)
				pslv = PS_STATE_S0;
#endif // CONFIG_LPS_LCLK

#ifdef CONFIG_BT_COEXIST
			if ((rtw_btcoex_IsBtDisabled(padapter) == _FALSE)
				&& (rtw_btcoex_IsBtControlLps(padapter) == _TRUE))
			{
				u8 val8;

				val8 = rtw_btcoex_LpsVal(padapter);
				if (val8 & BIT(4))
					pslv = PS_STATE_S2;

			}
#endif // CONFIG_BT_COEXIST

			rtw_set_rpwm(padapter, pslv);
		}
