#ifdef CONFIG_IEEE80211W
if (wpa_key_mgmt_sha256(sm->key_mgmt)) {
		if (ver != WPA_KEY_INFO_TYPE_AES_128_CMAC) {
			wpa_printf(MSG_INFO, "WPA: AP did not use the "
				   "negotiated AES-128-CMAC.");
			goto out;
		}
	} else
#endif /* CONFIG_IEEE80211W */
	if (sm->pairwise_cipher == WPA_CIPHER_CCMP &&
	    ver != WPA_KEY_INFO_TYPE_HMAC_SHA1_AES) {
		wpa_printf(MSG_INFO, "WPA: CCMP is used, but EAPOL-Key "
			   "descriptor version (%d) is not 2.", ver);
		if (sm->group_cipher != WPA_CIPHER_CCMP &&
		    !(key_info & WPA_KEY_INFO_KEY_TYPE)) {
			/* Earlier versions of IEEE 802.11i did not explicitly
			 * require version 2 descriptor for all EAPOL-Key
			 * packets, so allow group keys to use version 1 if
			 * CCMP is not used for them. */
			wpa_printf(MSG_INFO, "WPA: Backwards compatibility: "
				   "allow invalid version for non-CCMP group "
				   "keys");
		} else
			goto out;
	}
