switch (lp->p_encap) {
		case ISDN_NET_ENCAP_ETHER:
			/* Ethernet over ISDN */
			olp->huptimer = 0;
			lp->huptimer = 0;
			skb->protocol = isdn_net_type_trans(skb, ndev);
			break;
		case ISDN_NET_ENCAP_UIHDLC:
			/* HDLC with UI-frame (for ispa with -h1 option) */
			olp->huptimer = 0;
			lp->huptimer = 0;
			skb_pull(skb, 2);
			/* Fall through */
		case ISDN_NET_ENCAP_RAWIP:
			/* RAW-IP without MAC-Header */
			olp->huptimer = 0;
			lp->huptimer = 0;
			skb->protocol = htons(ETH_P_IP);
			break;
		case ISDN_NET_ENCAP_CISCOHDLCK:
			isdn_net_ciscohdlck_receive(lp, skb);
			return;
		case ISDN_NET_ENCAP_CISCOHDLC:
			/* CISCO-HDLC IP with type field and  fake I-frame-header */
			skb_pull(skb, 2);
			/* Fall through */
		case ISDN_NET_ENCAP_IPTYP:
			/* IP with type field */
			olp->huptimer = 0;
			lp->huptimer = 0;
			skb->protocol = *(__be16 *)&(skb->data[0]);
			skb_pull(skb, 2);
			if (*(unsigned short *) skb->data == 0xFFFF)
				skb->protocol = htons(ETH_P_802_3);
			break;
#ifdef CONFIG_ISDN_PPP
		case ISDN_NET_ENCAP_SYNCPPP:
			/* huptimer is done in isdn_ppp_push_higher */
			isdn_ppp_receive(lp->netdev, olp, skb);
			return;
#endif

		default:
#ifdef CONFIG_ISDN_X25
		  /* try if there are generic sync_device receiver routines */
			if(cprot) if(cprot -> pops)
				if( cprot -> pops -> data_ind){
					cprot -> pops -> data_ind(cprot,skb);
					return;
				};
#endif /* CONFIG_ISDN_X25 */
			printk(KERN_WARNING "%s: unknown encapsulation, dropping\n",
			       lp->netdev->dev->name);
			kfree_skb(skb);
			return;
	}
