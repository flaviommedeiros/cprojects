switch (ds->tag_protocol) {
#ifdef CONFIG_NET_DSA_TAG_DSA
		case DSA_TAG_PROTO_DSA:
			dst->rcv = dsa_netdev_ops.rcv;
			break;
#endif
#ifdef CONFIG_NET_DSA_TAG_EDSA
		case DSA_TAG_PROTO_EDSA:
			dst->rcv = edsa_netdev_ops.rcv;
			break;
#endif
#ifdef CONFIG_NET_DSA_TAG_TRAILER
		case DSA_TAG_PROTO_TRAILER:
			dst->rcv = trailer_netdev_ops.rcv;
			break;
#endif
#ifdef CONFIG_NET_DSA_TAG_BRCM
		case DSA_TAG_PROTO_BRCM:
			dst->rcv = brcm_netdev_ops.rcv;
			break;
#endif
		case DSA_TAG_PROTO_NONE:
			break;
		default:
			ret = -ENOPROTOOPT;
			goto out;
		}
