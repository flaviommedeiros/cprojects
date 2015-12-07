if (((dst = __br_fdb_get(br, dest)) && dst->is_local) ||
#ifdef BCM_GMAC3
		(htons(skb->protocol) == 0x88c7) ||
		/* 0x88c7 is EAPOL Preauth frame, and for gmac3_enable/ATLAS configuration
		 * Platforms,we are allowing this packet to reach upto EAPD-> NAS, as bridge
		 * does not have the radio interfaces in it's port list.
		 */
#endif
		0) {
		skb2 = skb;
		/* Do not forward the packet since it's local. */
		skb = NULL;
	}
