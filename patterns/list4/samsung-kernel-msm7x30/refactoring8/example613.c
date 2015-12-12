static struct xt_target tproxy_tg_reg[] __read_mostly = {
	{
		.name		= "TPROXY",
		.family		= NFPROTO_IPV4,
		.table		= "mangle",
		.target		= tproxy_tg4_v0,
		.revision	= 0,
		.targetsize	= sizeof(struct xt_tproxy_target_info),
		.checkentry	= tproxy_tg4_check,
		.hooks		= 1 << NF_INET_PRE_ROUTING,
		.me		= THIS_MODULE,
	},
	{
		.name		= "TPROXY",
		.family		= NFPROTO_IPV4,
		.table		= "mangle",
		.target		= tproxy_tg4_v1,
		.revision	= 1,
		.targetsize	= sizeof(struct xt_tproxy_target_info_v1),
		.checkentry	= tproxy_tg4_check,
		.hooks		= 1 << NF_INET_PRE_ROUTING,
		.me		= THIS_MODULE,
	},
#ifdef XT_TPROXY_HAVE_IPV6
	{
		.name		= "TPROXY",
		.family		= NFPROTO_IPV6,
		.table		= "mangle",
		.target		= tproxy_tg6_v1,
		.revision	= 1,
		.targetsize	= sizeof(struct xt_tproxy_target_info_v1),
		.checkentry	= tproxy_tg6_check,
		.hooks		= 1 << NF_INET_PRE_ROUTING,
		.me		= THIS_MODULE,
	},
#endif

};
