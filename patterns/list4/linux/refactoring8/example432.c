static struct xt_match l2tp_mt_reg[] __read_mostly = {
	{
		.name      = "l2tp",
		.revision  = 0,
		.family    = NFPROTO_IPV4,
		.match     = l2tp_mt4,
		.matchsize = XT_ALIGN(sizeof(struct xt_l2tp_info)),
		.checkentry = l2tp_mt_check4,
		.hooks     = ((1 << NF_INET_PRE_ROUTING) |
			      (1 << NF_INET_LOCAL_IN) |
			      (1 << NF_INET_LOCAL_OUT) |
			      (1 << NF_INET_FORWARD)),
		.me        = THIS_MODULE,
	},
#if IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	{
		.name      = "l2tp",
		.revision  = 0,
		.family    = NFPROTO_IPV6,
		.match     = l2tp_mt6,
		.matchsize = XT_ALIGN(sizeof(struct xt_l2tp_info)),
		.checkentry = l2tp_mt_check6,
		.hooks     = ((1 << NF_INET_PRE_ROUTING) |
			      (1 << NF_INET_LOCAL_IN) |
			      (1 << NF_INET_LOCAL_OUT) |
			      (1 << NF_INET_FORWARD)),
		.me        = THIS_MODULE,
	},
#endif
};
