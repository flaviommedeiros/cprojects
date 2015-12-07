#ifdef CONFIG_IP_VS_IPV6
if (cp->af == AF_INET6)
			tcph->check = csum_ipv6_magic(&cp->caddr.in6,
						      &cp->daddr.in6,
						      skb->len - tcphoff,
						      cp->protocol, skb->csum);
		else
#endif
			tcph->check = csum_tcpudp_magic(cp->caddr.ip,
							cp->daddr.ip,
							skb->len - tcphoff,
							cp->protocol,
							skb->csum);
