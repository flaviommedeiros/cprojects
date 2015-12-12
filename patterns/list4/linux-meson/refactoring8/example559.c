static const struct nla_policy ipip6_policy[IFLA_IPTUN_MAX + 1] = {
	[IFLA_IPTUN_LINK]		= { .type = NLA_U32 },
	[IFLA_IPTUN_LOCAL]		= { .type = NLA_U32 },
	[IFLA_IPTUN_REMOTE]		= { .type = NLA_U32 },
	[IFLA_IPTUN_TTL]		= { .type = NLA_U8 },
	[IFLA_IPTUN_TOS]		= { .type = NLA_U8 },
	[IFLA_IPTUN_PMTUDISC]		= { .type = NLA_U8 },
	[IFLA_IPTUN_FLAGS]		= { .type = NLA_U16 },
#ifdef CONFIG_IPV6_SIT_6RD
	[IFLA_IPTUN_6RD_PREFIX]		= { .len = sizeof(struct in6_addr) },
	[IFLA_IPTUN_6RD_RELAY_PREFIX]	= { .type = NLA_U32 },
	[IFLA_IPTUN_6RD_PREFIXLEN]	= { .type = NLA_U16 },
	[IFLA_IPTUN_6RD_RELAY_PREFIXLEN] = { .type = NLA_U16 },
#endif
};
