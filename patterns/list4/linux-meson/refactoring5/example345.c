#ifdef CONFIG_IPV6_MROUTE
if (ipv6_addr_is_multicast(&rt->rt6i_dst.addr)) {
			int err = ip6mr_get_route(net, skb, rtm, nowait);
			if (err <= 0) {
				if (!nowait) {
					if (err == 0)
						return 0;
					goto nla_put_failure;
				} else {
					if (err == -EMSGSIZE)
						goto nla_put_failure;
				}
			}
		} else
#endif
			if (nla_put_u32(skb, RTA_IIF, iif))
				goto nla_put_failure;
