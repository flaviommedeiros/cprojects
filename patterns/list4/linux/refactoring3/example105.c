switch (proto) {
	case PPP_IPX:  /* untested */
		if (is->debug & 0x20)
			printk(KERN_DEBUG "isdn_ppp: IPX\n");
		skb->protocol = htons(ETH_P_IPX);
		break;
	case PPP_IP:
		if (is->debug & 0x20)
			printk(KERN_DEBUG "isdn_ppp: IP\n");
		skb->protocol = htons(ETH_P_IP);
		break;
	case PPP_COMP:
	case PPP_COMPFRAG:
		printk(KERN_INFO "isdn_ppp: unexpected compressed frame dropped\n");
		goto drop_packet;
#ifdef CONFIG_ISDN_PPP_VJ
	case PPP_VJC_UNCOMP:
		if (is->debug & 0x20)
			printk(KERN_DEBUG "isdn_ppp: VJC_UNCOMP\n");
		if (net_dev->local->ppp_slot < 0) {
			printk(KERN_ERR "%s: net_dev->local->ppp_slot(%d) out of range\n",
			       __func__, net_dev->local->ppp_slot);
			goto drop_packet;
		}
		if (slhc_remember(ippp_table[net_dev->local->ppp_slot]->slcomp, skb->data, skb->len) <= 0) {
			printk(KERN_WARNING "isdn_ppp: received illegal VJC_UNCOMP frame!\n");
			goto drop_packet;
		}
		skb->protocol = htons(ETH_P_IP);
		break;
	case PPP_VJC_COMP:
		if (is->debug & 0x20)
			printk(KERN_DEBUG "isdn_ppp: VJC_COMP\n");
		{
			struct sk_buff *skb_old = skb;
			int pkt_len;
			skb = dev_alloc_skb(skb_old->len + 128);

			if (!skb) {
				printk(KERN_WARNING "%s: Memory squeeze, dropping packet.\n", dev->name);
				skb = skb_old;
				goto drop_packet;
			}
			skb_put(skb, skb_old->len + 128);
			skb_copy_from_linear_data(skb_old, skb->data,
						  skb_old->len);
			if (net_dev->local->ppp_slot < 0) {
				printk(KERN_ERR "%s: net_dev->local->ppp_slot(%d) out of range\n",
				       __func__, net_dev->local->ppp_slot);
				goto drop_packet;
			}
			pkt_len = slhc_uncompress(ippp_table[net_dev->local->ppp_slot]->slcomp,
						  skb->data, skb_old->len);
			kfree_skb(skb_old);
			if (pkt_len < 0)
				goto drop_packet;

			skb_trim(skb, pkt_len);
			skb->protocol = htons(ETH_P_IP);
		}
		break;
#endif
	case PPP_CCP:
	case PPP_CCPFRAG:
		isdn_ppp_receive_ccp(net_dev, lp, skb, proto);
		/* Dont pop up ResetReq/Ack stuff to the daemon any
		   longer - the job is done already */
		if (skb->data[0] == CCP_RESETREQ ||
		    skb->data[0] == CCP_RESETACK)
			break;
		/* fall through */
	default:
		isdn_ppp_fill_rq(skb->data, skb->len, proto, lp->ppp_slot);	/* push data to pppd device */
		kfree_skb(skb);
		return;
	}
