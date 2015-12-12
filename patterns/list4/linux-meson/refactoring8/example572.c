static struct xt_match hashlimit_mt_reg[] __read_mostly = {
	{
		.name           = "hashlimit",
		.revision       = 1,
		.family         = NFPROTO_IPV4,
		.match          = hashlimit_mt,
		.matchsize      = sizeof(struct xt_hashlimit_mtinfo1),
		.checkentry     = hashlimit_mt_check,
		.destroy        = hashlimit_mt_destroy,
		.me             = THIS_MODULE,
	},
#if IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	{
		.name           = "hashlimit",
		.revision       = 1,
		.family         = NFPROTO_IPV6,
		.match          = hashlimit_mt,
		.matchsize      = sizeof(struct xt_hashlimit_mtinfo1),
		.checkentry     = hashlimit_mt_check,
		.destroy        = hashlimit_mt_destroy,
		.me             = THIS_MODULE,
	},
#endif
};
