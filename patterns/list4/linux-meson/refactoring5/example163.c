#ifdef CONFIG_P2P
if(!rtw_p2p_chk_state(&padapter->wdinfo, P2P_STATE_NONE))
			{
				rtw_p2p_findphase_ex_set(pwdinfo, P2P_FINDPHASE_EX_MAX);
				pmlmeext->sitesurvey_res.channel_idx = 3;
				DBG_871X("%s idx:%d, cnt:%u\n", __FUNCTION__
					, pmlmeext->sitesurvey_res.channel_idx
					, pwdinfo->find_phase_state_exchange_cnt
				);
			}
			else
			#endif
			{
				pmlmeext->sitesurvey_res.channel_idx = pmlmeext->sitesurvey_res.ch_num;
				DBG_871X("%s idx:%d\n", __FUNCTION__
					, pmlmeext->sitesurvey_res.channel_idx
				);
			}
