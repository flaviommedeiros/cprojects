switch (proto) {
	/* handle any vlan tag if present */
	case __constant_htons(ETH_P_8021AD):
	case __constant_htons(ETH_P_8021Q):
		if ((hdr.network - data) > (max_len - VLAN_HLEN))
			return max_len;

		proto = hdr.vlan->h_vlan_encapsulated_proto;
		hdr.network += VLAN_HLEN;
		goto again;
	/* handle L3 protocols */
	case __constant_htons(ETH_P_IP):
		if ((hdr.network - data) > (max_len - sizeof(struct iphdr)))
			return max_len;

		/* access ihl as a u8 to avoid unaligned access on ia64 */
		hlen = (hdr.network[0] & 0x0F) << 2;

		/* verify hlen meets minimum size requirements */
		if (hlen < sizeof(struct iphdr))
			return hdr.network - data;

		/* record next protocol if header is present */
		if (!(hdr.ipv4->frag_off & htons(IP_OFFSET)))
			nexthdr = hdr.ipv4->protocol;

		hdr.network += hlen;
		break;
#ifdef NETIF_F_TSO6
	case __constant_htons(ETH_P_IPV6):
		if ((hdr.network - data) > (max_len - sizeof(struct ipv6hdr)))
			return max_len;

		/* record next protocol */
		nexthdr = hdr.ipv6->nexthdr;
		hdr.network += sizeof(struct ipv6hdr);
		break;
#endif /* NETIF_F_TSO6 */
	default:
		return hdr.network - data;
	}
