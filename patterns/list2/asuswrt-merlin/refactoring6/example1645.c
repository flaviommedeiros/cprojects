if (!(((hapd->conf->auth_algs & WPA_AUTH_ALG_OPEN) &&
	       auth_alg == WLAN_AUTH_OPEN) ||
#ifdef CONFIG_IEEE80211R
	      (hapd->conf->wpa &&
	       (hapd->conf->wpa_key_mgmt &
		(WPA_KEY_MGMT_FT_IEEE8021X | WPA_KEY_MGMT_FT_PSK)) &&
	       auth_alg == WLAN_AUTH_FT) ||
#endif /* CONFIG_IEEE80211R */
	      ((hapd->conf->auth_algs & WPA_AUTH_ALG_SHARED) &&
	       auth_alg == WLAN_AUTH_SHARED_KEY))) {
		printf("Unsupported authentication algorithm (%d)\n",
		       auth_alg);
		resp = WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG;
		goto fail;
	}
