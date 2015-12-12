#ifdef CONFIG_IP_VS_IPV6
if (skb_af == AF_INET6) {
		old_ipv6h = ipv6_hdr(skb);
		*next_protocol = IPPROTO_IPV6;
		if (payload_len)
			*payload_len =
				ntohs(old_ipv6h->payload_len) +
				sizeof(*old_ipv6h);
		*dsfield = ipv6_get_dsfield(old_ipv6h);
		*ttl = old_ipv6h->hop_limit;
		if (df)
			*df = 0;
	} else
#endif
	{
		old_iph = ip_hdr(skb);
		/* Copy DF, reset fragment offset and MF */
		if (df)
			*df = (old_iph->frag_off & htons(IP_DF));
		*next_protocol = IPPROTO_IPIP;

		/* fix old IP header checksum */
		ip_send_check(old_iph);
		*dsfield = ipv4_get_dsfield(old_iph);
		*ttl = old_iph->ttl;
		if (payload_len)
			*payload_len = ntohs(old_iph->tot_len);
	}
