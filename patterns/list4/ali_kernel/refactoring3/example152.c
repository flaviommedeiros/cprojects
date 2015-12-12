switch (eth->h_proto)
	{
#ifdef CONFIG_INET
	case cpu_to_be16(ETH_P_IP):
 		return arp_find(eth->h_dest, skb);
#endif

	default:
		printk(KERN_DEBUG
		       "%s: unable to resolve type %X addresses.\n",
		       dev->name, (int)eth->h_proto);

		memcpy(eth->h_source, dev->dev_addr, dev->addr_len);
		return 0;
		break;
	}
