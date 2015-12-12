static struct nla_policy tcp_metrics_nl_policy[TCP_METRICS_ATTR_MAX + 1] = {
	[TCP_METRICS_ATTR_ADDR_IPV4]	= { .type = NLA_U32, },
	[TCP_METRICS_ATTR_ADDR_IPV6]	= { .type = NLA_BINARY,
					    .len = sizeof(struct in6_addr), },
	/* Following attributes are not received for GET/DEL,
	 * we keep them for reference
	 */
#if 0
	[TCP_METRICS_ATTR_AGE]		= { .type = NLA_MSECS, },
	[TCP_METRICS_ATTR_TW_TSVAL]	= { .type = NLA_U32, },
	[TCP_METRICS_ATTR_TW_TS_STAMP]	= { .type = NLA_S32, },
	[TCP_METRICS_ATTR_VALS]		= { .type = NLA_NESTED, },
	[TCP_METRICS_ATTR_FOPEN_MSS]	= { .type = NLA_U16, },
	[TCP_METRICS_ATTR_FOPEN_SYN_DROPS]	= { .type = NLA_U16, },
	[TCP_METRICS_ATTR_FOPEN_SYN_DROP_TS]	= { .type = NLA_MSECS, },
	[TCP_METRICS_ATTR_FOPEN_COOKIE]	= { .type = NLA_BINARY,
					    .len = TCP_FASTOPEN_COOKIE_MAX, },
#endif
};
