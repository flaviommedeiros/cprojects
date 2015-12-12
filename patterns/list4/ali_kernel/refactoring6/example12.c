if (priv->cfg->bt_params &&
	    priv->cfg->bt_params->advanced_bt_coexist &&
#if 0 /* Not in RHEL6... */
	    vif->type == NL80211_IFTYPE_ADHOC) {
#else
	    conf->type == NL80211_IFTYPE_ADHOC) {
#endif
		/*
		 * pretend to have high BT traffic as long as we
		 * are operating in IBSS mode, as this will cause
		 * the rate scaling etc. to behave as intended.
		 */
		priv->bt_traffic_load = IWL_BT_COEX_TRAFFIC_LOAD_HIGH;
	}
