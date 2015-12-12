switch (skb->dev->type) {
#ifdef CONFIG_TR
	case ARPHRD_IEEE802_TR: {
		struct net_device *dev = skb->dev;
		struct trh_hdr *trh;

		skb_push(skb, sizeof(*trh));
		skb_reset_mac_header(skb);
		trh = tr_hdr(skb);
		trh->ac = AC;
		trh->fc = LLC_FRAME;
		if (sa)
			memcpy(trh->saddr, sa, dev->addr_len);
		else
			memset(trh->saddr, 0, dev->addr_len);
		if (da) {
			memcpy(trh->daddr, da, dev->addr_len);
			tr_source_route(skb, trh, dev);
			skb_reset_mac_header(skb);
		}
		break;
	}
#endif
	case ARPHRD_ETHER:
	case ARPHRD_LOOPBACK: {
		unsigned short len = skb->len;
		struct ethhdr *eth;

		skb_push(skb, sizeof(*eth));
		skb_reset_mac_header(skb);
		eth = eth_hdr(skb);
		eth->h_proto = htons(len);
		memcpy(eth->h_dest, da, ETH_ALEN);
		memcpy(eth->h_source, sa, ETH_ALEN);
		break;
	}
	default:
		printk(KERN_WARNING "device type not supported: %d\n",
		       skb->dev->type);
		rc = -EINVAL;
	}
