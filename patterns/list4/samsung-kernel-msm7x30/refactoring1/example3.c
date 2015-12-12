if (wl_get_drv_status_all(wl, SENDING_ACT_FRM)) {
		if (!(wl_get_p2p_status(wl, ACTION_TX_COMPLETED) ||
			wl_get_p2p_status(wl, ACTION_TX_NOACK)))
			wl_set_p2p_status(wl, ACTION_TX_COMPLETED);

		WL_DBG(("*** Wake UP ** abort actframe iovar\n"));
		/* if channel is not zero, "actfame" uses off channel scan.
		 * So abort scan for off channel completion.
		 */
		if (wl->af_sent_channel)
			wl_cfg80211_scan_abort(wl);
	}
#ifdef WL_CFG80211_SYNC_GON
	else if (wl_get_drv_status_all(wl, WAITING_NEXT_ACT_FRM_LISTEN)) {
		WL_DBG(("*** Wake UP ** abort listen for next af frame\n"));
		/* So abort scan to cancel listen */
		wl_cfg80211_scan_abort(wl);
	}
#endif
