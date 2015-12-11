switch (nexthdr) {
	case IPPROTO_TCP:
		if ((hdr.network - data) > (max_len - sizeof(struct tcphdr)))
			return max_len;

		/* access doff as a u8 to avoid unaligned access on ia64 */
		hdr.network += max_t(u8, sizeof(struct tcphdr),
				     (hdr.network[12] & 0xF0) >> 2);

		break;
	case IPPROTO_UDP:
	case IPPROTO_UDPLITE:
		hdr.network += sizeof(struct udphdr);
		break;
#ifdef HAVE_SCTP
	case IPPROTO_SCTP:
		hdr.network += sizeof(struct sctphdr);
		break;
#endif
	}
