switch (ds->dst->tag_protocol) {
#ifdef CONFIG_NET_DSA_TAG_DSA
	case DSA_TAG_PROTO_DSA:
		p->xmit = dsa_netdev_ops.xmit;
		break;
#endif
#ifdef CONFIG_NET_DSA_TAG_EDSA
	case DSA_TAG_PROTO_EDSA:
		p->xmit = edsa_netdev_ops.xmit;
		break;
#endif
#ifdef CONFIG_NET_DSA_TAG_TRAILER
	case DSA_TAG_PROTO_TRAILER:
		p->xmit = trailer_netdev_ops.xmit;
		break;
#endif
#ifdef CONFIG_NET_DSA_TAG_BRCM
	case DSA_TAG_PROTO_BRCM:
		p->xmit = brcm_netdev_ops.xmit;
		break;
#endif
	default:
		p->xmit	= dsa_slave_notag_xmit;
		break;
	}
