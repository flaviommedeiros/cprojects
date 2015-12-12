#ifndef WL_CFG80211_VSDB_PRIORITIZE_SCAN_REQUEST
if (wl_get_drv_status_all(wl, REMAINING_ON_CHANNEL)) {
#else
		if (wl_get_drv_status_all(wl, REMAINING_ON_CHANNEL) ||
			wl_get_drv_status_all(wl, FAKE_REMAINING_ON_CHANNEL)) {
#endif /* WL_CFG80211_VSDB_PRIORITIZE_SCAN_REQUEST */
			WL_DBG(("Listen DONE for ramain on channel expired\n"));
			wl_clr_drv_status(wl, REMAINING_ON_CHANNEL, ndev);
#ifdef WL_CFG80211_VSDB_PRIORITIZE_SCAN_REQUEST
			wl_clr_drv_status(wl, FAKE_REMAINING_ON_CHANNEL, ndev);
#endif /* WL_CFG80211_VSDB_PRIORITIZE_SCAN_REQUEST */
			if (ndev && (ndev->ieee80211_ptr != NULL)) {
#if defined(WL_CFG80211_P2P_DEV_IF)
				cfg80211_remain_on_channel_expired(cfgdev, wl->last_roc_id,
					&wl->remain_on_chan, GFP_KERNEL);
#else
				cfg80211_remain_on_channel_expired(cfgdev, wl->last_roc_id,
					&wl->remain_on_chan, wl->remain_on_chan_type, GFP_KERNEL);
#endif /* WL_CFG80211_P2P_DEV_IF */
			}
		}
		if (wl_add_remove_eventmsg(wl_to_prmry_ndev(wl),
			WLC_E_P2P_PROBREQ_MSG, false) != BCME_OK) {
			CFGP2P_ERR((" failed to unset WLC_E_P2P_PROPREQ_MSG\n"));
		}
	} else
		wl_clr_p2p_status(wl, LISTEN_EXPIRED);
