static struct xt_target log_tg_regs[] __read_mostly = {
	{
		.name		= "LOG",
		.family		= NFPROTO_IPV4,
		.target		= log_tg,
		.targetsize	= sizeof(struct xt_log_info),
		.checkentry	= log_tg_check,
		.destroy	= log_tg_destroy,
		.me		= THIS_MODULE,
	},
#if IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	{
		.name		= "LOG",
		.family		= NFPROTO_IPV6,
		.target		= log_tg,
		.targetsize	= sizeof(struct xt_log_info),
		.checkentry	= log_tg_check,
		.destroy	= log_tg_destroy,
		.me		= THIS_MODULE,
	},
#endif
};
