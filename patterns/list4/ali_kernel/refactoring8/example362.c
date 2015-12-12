static struct xt_match socket_mt_reg[] __read_mostly = {
	{
		.name		= "socket",
		.revision	= 0,
		.family		= NFPROTO_IPV4,
		.match		= socket_mt4_v0,
		.hooks		= 1 << NF_INET_PRE_ROUTING,
		.me		= THIS_MODULE,
	},
	{
		.name		= "socket",
		.revision	= 1,
		.family		= NFPROTO_IPV4,
		.match		= socket_mt4_v1,
		.matchsize	= sizeof(struct xt_socket_mtinfo1),
		.hooks		= 1 << NF_INET_PRE_ROUTING,
		.me		= THIS_MODULE,
	},
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	{
		.name		= "socket",
		.revision	= 1,
		.family		= NFPROTO_IPV6,
		.match		= socket_mt6_v1,
		.matchsize	= sizeof(struct xt_socket_mtinfo1),
		.hooks		= (1 << NF_INET_PRE_ROUTING) |
				  (1 << NF_INET_LOCAL_IN),
		.me		= THIS_MODULE,
	},
#endif
};
