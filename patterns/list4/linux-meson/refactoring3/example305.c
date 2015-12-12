switch(intCmdType)
	{
		case P2P_FIND_PHASE_WK:
		{
			find_phase_handler( padapter );
			break;
		}
		case P2P_RESTORE_STATE_WK:
		{
			restore_p2p_state_handler( padapter );
			break;
		}
		case P2P_PRE_TX_PROVDISC_PROCESS_WK:
		{
#ifdef CONFIG_CONCURRENT_MODE
			if ( check_buddy_fwstate(padapter, _FW_LINKED ) )
			{
				p2p_concurrent_handler( padapter );
			}
			else
			{
				pre_tx_provdisc_handler( padapter );
			}
#else
			pre_tx_provdisc_handler( padapter );
#endif
			break;
		}
		case P2P_PRE_TX_INVITEREQ_PROCESS_WK:
		{
#ifdef CONFIG_CONCURRENT_MODE
			if ( check_buddy_fwstate(padapter, _FW_LINKED ) )
			{
				p2p_concurrent_handler( padapter );
			}
			else
			{
				pre_tx_invitereq_handler( padapter );
			}
#else			
			pre_tx_invitereq_handler( padapter );
#endif
			break;
		}
		case P2P_PRE_TX_NEGOREQ_PROCESS_WK:
		{
#ifdef CONFIG_CONCURRENT_MODE
			if ( check_buddy_fwstate(padapter, _FW_LINKED ) )
			{
				p2p_concurrent_handler( padapter );
			}
			else
			{
				pre_tx_negoreq_handler( padapter );
			}
#else			
			pre_tx_negoreq_handler( padapter );
#endif
			break;
		}
#ifdef CONFIG_P2P
#ifdef CONFIG_CONCURRENT_MODE
		case P2P_AP_P2P_CH_SWITCH_PROCESS_WK:
		{
			p2p_concurrent_handler( padapter );
			break;
		}		
#endif
#endif
#ifdef CONFIG_IOCTL_CFG80211
		case P2P_RO_CH_WK:
		{
			ro_ch_handler( padapter );
			break;
		}		
#endif //CONFIG_IOCTL_CFG80211		

	}
