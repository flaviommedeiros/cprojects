static const struct ieee80211_iface_combination ath10k_10x_if_comb[] = {
	{
		.limits = ath10k_10x_if_limits,
		.n_limits = ARRAY_SIZE(ath10k_10x_if_limits),
		.max_interfaces = 8,
		.num_different_channels = 1,
		.beacon_int_infra_match = true,
#ifdef CONFIG_ATH10K_DFS_CERTIFIED
		.radar_detect_widths =	BIT(NL80211_CHAN_WIDTH_20_NOHT) |
					BIT(NL80211_CHAN_WIDTH_20) |
					BIT(NL80211_CHAN_WIDTH_40) |
					BIT(NL80211_CHAN_WIDTH_80),
#endif
	},
};
