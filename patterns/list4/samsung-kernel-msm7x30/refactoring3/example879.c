switch (eth->h_proto) {
#ifdef CONFIG_INET
	case htons(ETH_P_IP):
		return arp_find(eth->h_dest, skb);
#endif
	default:
		printk(KERN_DEBUG
		       "%s: unable to resolve type %X addresses.\n",
		       dev->name, ntohs(eth->h_proto));

		memcpy(eth->h_source, dev->dev_addr, ETH_ALEN);
		break;
	}
