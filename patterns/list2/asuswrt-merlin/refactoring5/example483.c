#ifdef EAP_AKA_PRIME
if (k_aut && msg->mac && msg->type == EAP_TYPE_AKA_PRIME) {
		eap_sim_add_mac_sha256(k_aut, (u8 *) wpabuf_head(msg->buf),
				       wpabuf_len(msg->buf),
				       (u8 *) wpabuf_mhead(msg->buf) +
				       msg->mac, extra, extra_len);
	} else
#endif /* EAP_AKA_PRIME */
	if (k_aut && msg->mac) {
		eap_sim_add_mac(k_aut, (u8 *) wpabuf_head(msg->buf),
				wpabuf_len(msg->buf),
				(u8 *) wpabuf_mhead(msg->buf) + msg->mac,
				extra, extra_len);
	}
