#ifdef CONFIG_IP_VS_IPV6
if (cp->af == AF_INET6)
			udph->check = csum_ipv6_magic(&cp->vaddr.in6,
						      &cp->caddr.in6,
						      skb->len - udphoff,
						      cp->protocol, skb->csum);
		else
#endif
			udph->check = csum_tcpudp_magic(cp->vaddr.ip,
							cp->caddr.ip,
							skb->len - udphoff,
							cp->protocol,
							skb->csum);
