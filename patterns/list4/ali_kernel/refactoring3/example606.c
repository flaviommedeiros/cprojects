switch (ds->dst->tag_protocol) {
#ifdef CONFIG_NET_DSA_TAG_DSA
	case htons(ETH_P_DSA):
		slave_dev->netdev_ops = &dsa_netdev_ops;
		break;
#endif
#ifdef CONFIG_NET_DSA_TAG_EDSA
	case htons(ETH_P_EDSA):
		slave_dev->netdev_ops = &edsa_netdev_ops;
		break;
#endif
#ifdef CONFIG_NET_DSA_TAG_TRAILER
	case htons(ETH_P_TRAILER):
		slave_dev->netdev_ops = &trailer_netdev_ops;
		break;
#endif
	default:
		BUG();
	}
