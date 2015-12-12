static const struct ieee80211_iface_combination if_comb[] = {
	{
		.limits = if_limits,
		.n_limits = ARRAY_SIZE(if_limits),
		.max_interfaces = 2048,
		.num_different_channels = 1,
		.beacon_int_infra_match = true,
	},
	{
		.limits = wds_limits,
		.n_limits = ARRAY_SIZE(wds_limits),
		.max_interfaces = 2048,
		.num_different_channels = 1,
		.beacon_int_infra_match = true,
	},
#ifdef CONFIG_ATH9K_DFS_CERTIFIED
	{
		.limits = if_dfs_limits,
		.n_limits = ARRAY_SIZE(if_dfs_limits),
		.max_interfaces = 1,
		.num_different_channels = 1,
		.beacon_int_infra_match = true,
		.radar_detect_widths =	BIT(NL80211_CHAN_WIDTH_20_NOHT) |
					BIT(NL80211_CHAN_WIDTH_20) |
					BIT(NL80211_CHAN_WIDTH_40),
	}
#endif
};
