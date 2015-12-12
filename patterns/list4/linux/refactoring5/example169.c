#ifdef CONFIG_MAC80211_RC_MINSTREL_VHT
if (vht_cap->vht_supported)
		use_vht = vht_cap->vht_mcs.tx_mcs_map != cpu_to_le16(~0);
	else
#endif
	use_vht = 0;
