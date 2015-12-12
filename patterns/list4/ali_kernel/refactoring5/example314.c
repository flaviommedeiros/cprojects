#ifdef CONFIG_IP_VS_IPV6
if (af == AF_INET6)
						icmpv6_send(skb,
							    ICMPV6_DEST_UNREACH,
							    ICMPV6_PORT_UNREACH,
							    0, skb->dev);
					else
#endif
						icmp_send(skb,
							  ICMP_DEST_UNREACH,
							  ICMP_PORT_UNREACH, 0);
