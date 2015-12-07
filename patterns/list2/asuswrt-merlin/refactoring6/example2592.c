if (!(key_info & (WPA_KEY_INFO_ACK | WPA_KEY_INFO_SMK_MESSAGE))
#ifdef CONFIG_PEERKEY
	    && (peerkey == NULL || !peerkey->initiator)
#endif /* CONFIG_PEERKEY */
		) {
		wpa_printf(MSG_INFO, "WPA: No Ack bit in key_info");
		goto out;
	}
