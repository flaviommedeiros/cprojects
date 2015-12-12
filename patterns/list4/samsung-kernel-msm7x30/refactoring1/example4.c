if (wl->afx_hdl->is_listen == TRUE &&
			wl_get_drv_status_all(wl, FINDING_COMMON_CHANNEL)) {
			WL_DBG(("Listen DONE for action frame\n"));
			complete(&wl->act_frm_scan);
		}
#ifdef WL_CFG80211_SYNC_GON
		else if (wl_get_drv_status_all(wl, WAITING_NEXT_ACT_FRM_LISTEN)) {
			wl_clr_drv_status(wl, WAITING_NEXT_ACT_FRM_LISTEN, ndev);
			WL_DBG(("Listen DONE and wake up wait_next_af !!(%d)\n",
				jiffies_to_msecs(jiffies - wl->af_tx_sent_jiffies)));

			if (wl_get_drv_status_all(wl, WAITING_NEXT_ACT_FRM))
				wl_clr_drv_status(wl, WAITING_NEXT_ACT_FRM, ndev);

			complete(&wl->wait_next_af);
		}
#endif
