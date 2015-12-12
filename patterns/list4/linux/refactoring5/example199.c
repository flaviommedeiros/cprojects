#ifdef CONFIG_IP_VS_IPV6
if (c->mcast_af == AF_INET6) {
		if (nla_put_in6_addr(skb, IPVS_DAEMON_ATTR_MCAST_GROUP6,
				     &c->mcast_group.in6))
			goto nla_put_failure;
	} else
#endif
		if (c->mcast_af == AF_INET &&
		    nla_put_in_addr(skb, IPVS_DAEMON_ATTR_MCAST_GROUP,
				    c->mcast_group.ip))
			goto nla_put_failure;
