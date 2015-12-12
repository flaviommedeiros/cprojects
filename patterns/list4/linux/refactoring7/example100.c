return
		/* IFLA_IPTUN_LINK */
		nla_total_size(4) +
		/* IFLA_IPTUN_LOCAL */
		nla_total_size(4) +
		/* IFLA_IPTUN_REMOTE */
		nla_total_size(4) +
		/* IFLA_IPTUN_TTL */
		nla_total_size(1) +
		/* IFLA_IPTUN_TOS */
		nla_total_size(1) +
		/* IFLA_IPTUN_PMTUDISC */
		nla_total_size(1) +
		/* IFLA_IPTUN_FLAGS */
		nla_total_size(2) +
		/* IFLA_IPTUN_PROTO */
		nla_total_size(1) +
#ifdef CONFIG_IPV6_SIT_6RD
		/* IFLA_IPTUN_6RD_PREFIX */
		nla_total_size(sizeof(struct in6_addr)) +
		/* IFLA_IPTUN_6RD_RELAY_PREFIX */
		nla_total_size(4) +
		/* IFLA_IPTUN_6RD_PREFIXLEN */
		nla_total_size(2) +
		/* IFLA_IPTUN_6RD_RELAY_PREFIXLEN */
		nla_total_size(2) +
#endif
		/* IFLA_IPTUN_ENCAP_TYPE */
		nla_total_size(2) +
		/* IFLA_IPTUN_ENCAP_FLAGS */
		nla_total_size(2) +
		/* IFLA_IPTUN_ENCAP_SPORT */
		nla_total_size(2) +
		/* IFLA_IPTUN_ENCAP_DPORT */
		nla_total_size(2) +
		0;
