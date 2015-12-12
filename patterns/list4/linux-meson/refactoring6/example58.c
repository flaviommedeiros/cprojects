if ((passtime > BUSY_TRAFFIC_SCAN_DENY_PERIOD)
//#ifdef CONFIG_P2P
//			||(!rtw_p2p_chk_state(&padapter->wdinfo, P2P_STATE_NONE))
//#endif //CONFIG_P2P
		)
#endif
		{
			DBG_871X("%s: bBusyTraffic == _TRUE at buddy_intf\n", __FUNCTION__);
			need_indicate_scan_done = _TRUE;
			goto check_need_indicate_scan_done;
		}
