#ifdef CONFIG_IP_MROUTE
if (ipv4_is_multicast(dst) && !ipv4_is_local_multicast(dst) &&
		    IPV4_DEVCONF_ALL(net, MC_FORWARDING)) {
			int err = ipmr_get_route(net, skb,
						 fl4->saddr, fl4->daddr,
						 r, nowait);
			if (err <= 0) {
				if (!nowait) {
					if (err == 0)
						return 0;
					goto nla_put_failure;
				} else {
					if (err == -EMSGSIZE)
						goto nla_put_failure;
					error = err;
				}
			}
		} else
#endif
			if (nla_put_u32(skb, RTA_IIF, skb->dev->ifindex))
				goto nla_put_failure;
