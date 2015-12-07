if (our
#ifdef CONFIG_IP_MROUTE
			    || (!LOCAL_MCAST(daddr) && IN_DEV_MFORWARD(in_dev))
#endif
			    ) {
				res = ip_route_input_mc(skb, daddr, saddr,
							 tos, dev, our);
				rcu_read_unlock();
				return res;
			}
