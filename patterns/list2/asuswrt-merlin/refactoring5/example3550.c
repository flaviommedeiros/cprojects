#ifdef CONFIG_INET
if (fddi->hdr.llc_snap.ethertype == htons(ETH_P_IP))
		/* Try to get ARP to resolve the header and fill destination address */
		return arp_find(fddi->daddr, skb);
	else
#endif
	{
		printk("%s: Don't know how to resolve type %04X addresses.\n",
		       skb->dev->name, ntohs(fddi->hdr.llc_snap.ethertype));
		return(0);
	}
