static struct xt_target nfqueue_tg_reg[] __read_mostly = {
	{
		.name		= "NFQUEUE",
		.family		= NFPROTO_UNSPEC,
		.target		= nfqueue_tg,
		.targetsize	= sizeof(struct xt_NFQ_info),
		.me		= THIS_MODULE,
	},
	{
		.name		= "NFQUEUE",
		.revision	= 1,
		.family		= NFPROTO_IPV4,
		.checkentry	= nfqueue_tg_v1_check,
		.target		= nfqueue_tg4_v1,
		.targetsize	= sizeof(struct xt_NFQ_info_v1),
		.me		= THIS_MODULE,
	},
#if defined(CONFIG_IP6_NF_IPTABLES) || defined(CONFIG_IP6_NF_IPTABLES_MODULE)
	{
		.name		= "NFQUEUE",
		.revision	= 1,
		.family		= NFPROTO_IPV6,
		.checkentry	= nfqueue_tg_v1_check,
		.target		= nfqueue_tg6_v1,
		.targetsize	= sizeof(struct xt_NFQ_info_v1),
		.me		= THIS_MODULE,
	},
#endif
};
