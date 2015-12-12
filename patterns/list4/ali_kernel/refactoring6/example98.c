if (our
#ifdef CONFIG_IP_MROUTE
			    || (!ipv4_is_local_multicast(daddr) &&
				IN_DEV_MFORWARD(in_dev))
#endif
			    ) {
				rcu_read_unlock();
				return ip_route_input_mc(skb, daddr, saddr,
							 tos, dev, our);
			}
