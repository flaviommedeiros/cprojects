if ((adapter_to_pwrctl(padapter)->bLeisurePs) 
					&& (adapter_to_pwrctl(padapter)->pwr_mode != PS_MODE_ACTIVE)
#ifdef CONFIG_BT_COEXIST
					&& (rtw_btcoex_IsBtControlLps(padapter) == _FALSE)
#endif
					)
				{
					//DBG_871X("leave lps via Tx = %d\n", xmit_cnt);			
					bLeaveLPS = _TRUE;
				}
