#ifdef NETIF_F_TSO
if (!skb_is_gso(skb))
#endif /* NETIF_F_TSO */
		return 0;
