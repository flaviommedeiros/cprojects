if (err == BCME_OK ||
#if WL_OLPC_IOVARS_ENAB
			olpc_chan->dbg_mode ||
#endif /* WL_OLPC_IOVARS_ENAB */
			FALSE) {
			/* inform the phy we are calibrated */
			/* if dbg mode is set, we ignore cal cache errors and tell the phy */
			/* to use dbg storage for cal result */
			wlc_phy_update_olpc_cal((wlc_phy_t *)wlc->band->pi, TRUE,
#if WL_OLPC_IOVARS_ENAB
				olpc_chan->dbg_mode);
#else
				FALSE);
