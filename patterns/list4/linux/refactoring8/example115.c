static const struct ieee80211_iface_limit if_dfs_limits[] = {
	{ .max = 1,	.types = BIT(NL80211_IFTYPE_AP) |
#ifdef CONFIG_MAC80211_MESH
				 BIT(NL80211_IFTYPE_MESH_POINT) |
#endif
				 BIT(NL80211_IFTYPE_ADHOC) },
};
