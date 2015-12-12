static struct xt_target tcpoptstrip_tg_reg[] __read_mostly = {
	{
		.name       = "TCPOPTSTRIP",
		.family     = NFPROTO_IPV4,
		.table      = "mangle",
		.proto      = IPPROTO_TCP,
		.target     = tcpoptstrip_tg4,
		.targetsize = sizeof(struct xt_tcpoptstrip_target_info),
		.me         = THIS_MODULE,
	},
#if IS_ENABLED(CONFIG_IP6_NF_MANGLE)
	{
		.name       = "TCPOPTSTRIP",
		.family     = NFPROTO_IPV6,
		.table      = "mangle",
		.proto      = IPPROTO_TCP,
		.target     = tcpoptstrip_tg6,
		.targetsize = sizeof(struct xt_tcpoptstrip_target_info),
		.me         = THIS_MODULE,
	},
#endif
};
