#ifdef CONFIG_IPSEC_NAT_TRAVERSAL
if (xfrm4_rcv_encap_func != NULL)
		ret = (*xfrm4_rcv_encap_func)(skb, encap_type);
	else
#endif
	ret = xfrm4_rcv_encap(skb, encap_type);
