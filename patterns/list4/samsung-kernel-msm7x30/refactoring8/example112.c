static const struct ieee80211_iface_limit sta_p2p_limits[] = {
	/*
	 * During P2P-GO removal, P2P-GO is first changed to STA and later only
	 * removed. So setting maximum possible number of STA interfaces as 2 to
	 * accommodate the above behaviour.
	 */
	{
	.max = 2,
	.types = BIT(NL80211_IFTYPE_STATION),
	},
	{
	.max = 2,
	.types = BIT(NL80211_IFTYPE_P2P_GO) | BIT(NL80211_IFTYPE_P2P_CLIENT),
	},
#if defined(WL_CFG80211_P2P_DEV_IF)
	{
	.max = 1,
	.types = BIT(NL80211_IFTYPE_P2P_DEVICE),
	},
#endif /* WL_CFG80211_P2P_DEV_IF */
	{
	.max = 1,
	.types = BIT(NL80211_IFTYPE_ADHOC),
	},
};
