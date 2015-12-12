static struct xt_target hmark_tg_reg[] __read_mostly = {
	{
		.name		= "HMARK",
		.family		= NFPROTO_IPV4,
		.target		= hmark_tg_v4,
		.targetsize	= sizeof(struct xt_hmark_info),
		.checkentry	= hmark_tg_check,
		.me		= THIS_MODULE,
	},
#if IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	{
		.name		= "HMARK",
		.family		= NFPROTO_IPV6,
		.target		= hmark_tg_v6,
		.targetsize	= sizeof(struct xt_hmark_info),
		.checkentry	= hmark_tg_check,
		.me		= THIS_MODULE,
	},
#endif
};
