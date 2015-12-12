#ifdef CONFIG_CONCURRENT_MODE
if ( check_buddy_fwstate(padapter, _FW_LINKED ) == _TRUE )
		{
			rtw_p2p_set_state(pwdinfo, P2P_STATE_IDLE);
		}
		else
		#endif
		{
			rtw_p2p_set_state(pwdinfo, P2P_STATE_LISTEN);
		}
