static const struct ieee80211_iface_limit ath10k_10_4_if_limits[] = {
	{
		.max = 1,
		.types = BIT(NL80211_IFTYPE_STATION),
	},
	{
		.max	= 16,
		.types	= BIT(NL80211_IFTYPE_AP)
#ifdef CONFIG_MAC80211_MESH
			| BIT(NL80211_IFTYPE_MESH_POINT)
#endif
	},
};
