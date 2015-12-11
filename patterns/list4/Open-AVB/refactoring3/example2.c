switch (nexthdr) {
		case IPPROTO_TCP:
			type_tucmd |= E1000_ADVTXD_TUCMD_L4T_TCP;
			mss_l4len_idx = tcp_hdrlen(skb) <<
					E1000_ADVTXD_L4LEN_SHIFT;
			break;
#ifdef HAVE_SCTP
		case IPPROTO_SCTP:
			type_tucmd |= E1000_ADVTXD_TUCMD_L4T_SCTP;
			mss_l4len_idx = sizeof(struct sctphdr) <<
					E1000_ADVTXD_L4LEN_SHIFT;
			break;
#endif
		case IPPROTO_UDP:
			mss_l4len_idx = sizeof(struct udphdr) <<
					E1000_ADVTXD_L4LEN_SHIFT;
			break;
		default:
			if (unlikely(net_ratelimit())) {
				dev_warn(tx_ring->dev,
				 "partial checksum but l4 proto=%x!\n",
				 nexthdr);
			}
			break;
		}
