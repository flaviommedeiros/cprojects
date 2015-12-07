#ifdef CONFIG_IEEE80211R
if (sta && sta->auth_alg == WLAN_AUTH_FT &&
	    (sta->flags & WLAN_STA_AUTH) == 0) {
		wpa_printf(MSG_DEBUG, "FT: Allow STA " MACSTR " to associate "
			   "prior to authentication since it is using "
			   "over-the-DS FT", MAC2STR(mgmt->sa));
	} else
#endif /* CONFIG_IEEE80211R */
	if (sta == NULL || (sta->flags & WLAN_STA_AUTH) == 0) {
		hostapd_logger(hapd, mgmt->sa, HOSTAPD_MODULE_IEEE80211,
			       HOSTAPD_LEVEL_INFO, "Station tried to "
			       "associate before authentication "
			       "(aid=%d flags=0x%x)",
			       sta ? sta->aid : -1,
			       sta ? sta->flags : 0);
		send_deauth(hapd, mgmt->sa,
			    WLAN_REASON_CLASS2_FRAME_FROM_NONAUTH_STA);
		return;
	}
