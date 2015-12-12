#ifdef CONFIG_IP_VS_IPV6
if (svc->af == AF_INET6) {
		if (!skb->dev) {
			struct net *net = dev_net(skb_dst(skb)->dev);

			skb->dev = net->loopback_dev;
		}
		icmpv6_send(skb, ICMPV6_DEST_UNREACH, ICMPV6_PORT_UNREACH, 0);
	} else
#endif
		icmp_send(skb, ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, 0);
