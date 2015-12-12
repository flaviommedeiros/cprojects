#if 1
if (passtime > BUSY_TRAFFIC_SCAN_DENY_PERIOD)
#endif
		{
			DBG_871X("%s: bBusyTraffic == _TRUE\n", __FUNCTION__);
			need_indicate_scan_done = _TRUE;
			goto check_need_indicate_scan_done;
		}
