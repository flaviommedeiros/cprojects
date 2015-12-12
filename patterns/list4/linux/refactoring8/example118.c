static const struct ieee80211_iface_limit ath10k_if_limits[] = {
	{
	.max	= 8,
	.types	= BIT(NL80211_IFTYPE_STATION)
		| BIT(NL80211_IFTYPE_P2P_CLIENT)
	},
	{
	.max	= 3,
	.types	= BIT(NL80211_IFTYPE_P2P_GO)
	},
	{
	.max	= 1,
	.types	= BIT(NL80211_IFTYPE_P2P_DEVICE)
	},
	{
	.max	= 7,
	.types	= BIT(NL80211_IFTYPE_AP)
#ifdef CONFIG_MAC80211_MESH
		| BIT(NL80211_IFTYPE_MESH_POINT)
#endif
	},
};
