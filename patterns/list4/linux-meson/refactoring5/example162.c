#ifdef CONFIG_P2P
if (!rtw_p2p_chk_state(&padapter->wdinfo, P2P_STATE_NONE))
		{
			if(!from_timer)
				link_count_limit = 3; // 8 sec
			else
				link_count_limit = 15; // 32 sec
		}
		else
#endif // CONFIG_P2P
		{
			if(!from_timer)
				link_count_limit = 7; // 16 sec
			else
				link_count_limit = 29; // 60 sec
		}
