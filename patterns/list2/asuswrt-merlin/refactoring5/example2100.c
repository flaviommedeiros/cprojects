#ifdef CONFIG_IPV6_PIMSM_V2
if (assert == MRT6MSG_WHOLEPKT)
		skb = skb_realloc_headroom(pkt, -skb_network_offset(pkt)
						+sizeof(*msg));
	else
#endif
		skb = alloc_skb(sizeof(struct ipv6hdr) + sizeof(*msg), GFP_ATOMIC);
