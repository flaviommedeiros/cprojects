switch (lp->p_encap) {
		case ISDN_NET_ENCAP_ETHER:
			len = eth_header(skb, dev, type, daddr, saddr, plen);
			break;
#ifdef CONFIG_ISDN_PPP
		case ISDN_NET_ENCAP_SYNCPPP:
			/* stick on a fake header to keep fragmentation code happy. */
			len = IPPP_MAX_HEADER;
			skb_push(skb,len);
			break;
#endif
		case ISDN_NET_ENCAP_RAWIP:
			printk(KERN_WARNING "isdn_net_header called with RAW_IP!\n");
			len = 0;
			break;
		case ISDN_NET_ENCAP_IPTYP:
			/* ethernet type field */
			*((__be16 *)skb_push(skb, 2)) = htons(type);
			len = 2;
			break;
		case ISDN_NET_ENCAP_UIHDLC:
			/* HDLC with UI-Frames (for ispa with -h1 option) */
			*((__be16 *)skb_push(skb, 2)) = htons(0x0103);
			len = 2;
			break;
		case ISDN_NET_ENCAP_CISCOHDLC:
		case ISDN_NET_ENCAP_CISCOHDLCK:
			p = skb_push(skb, 4);
			*(u8 *)(p + 0) = CISCO_ADDR_UNICAST;
			*(u8 *)(p + 1) = CISCO_CTRL;
			*(__be16 *)(p + 2) = cpu_to_be16(type);
			p += 4;
			len = 4;
			break;
#ifdef CONFIG_ISDN_X25
		default:
		  /* try if there are generic concap protocol routines */
			if( lp-> netdev -> cprot ){
				printk(KERN_WARNING "isdn_net_header called with concap_proto!\n");
				len = 0;
				break;
			}
			break;
#endif /* CONFIG_ISDN_X25 */
	}
