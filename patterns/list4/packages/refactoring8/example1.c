static const struct ieee80211_iface_limit if_limits[] = {
	{ .max = 2048,	.types = BIT(NL80211_IFTYPE_STATION) },
	{ .max = 4,	.types =
#ifdef CONFIG_MAC80211_MESH
				 BIT(NL80211_IFTYPE_MESH_POINT) |
#endif
				 BIT(NL80211_IFTYPE_AP) },
};
