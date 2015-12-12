static struct xt_target tcpmss_tg_reg[] __read_mostly = {
	{
		.family		= NFPROTO_IPV4,
		.name		= "TCPMSS",
		.checkentry	= tcpmss_tg4_check,
		.target		= tcpmss_tg4,
		.targetsize	= sizeof(struct xt_tcpmss_info),
		.proto		= IPPROTO_TCP,
		.me		= THIS_MODULE,
	},
#if defined(CONFIG_IP6_NF_IPTABLES) || defined(CONFIG_IP6_NF_IPTABLES_MODULE)
	{
		.family		= NFPROTO_IPV6,
		.name		= "TCPMSS",
		.checkentry	= tcpmss_tg6_check,
		.target		= tcpmss_tg6,
		.targetsize	= sizeof(struct xt_tcpmss_info),
		.proto		= IPPROTO_TCP,
		.me		= THIS_MODULE,
	},
#endif
};
