#ifdef HAVE_VLAN_RX_REGISTER
if (IGB_CB(lro_skb)->vid != vid)
#else
		if (lro_skb->vlan_tci != vid)
#endif
			continue;
