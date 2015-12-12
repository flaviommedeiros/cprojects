switch (prot) {
#ifdef CONFIG_QETH_IPV6
			case __constant_htons(ETH_P_IPV6):
				ndisc_mc_map((struct in6_addr *)
				     skb->data + 24,
				     tg_addr, card->dev, 0);
				break;
#endif
			case __constant_htons(ETH_P_IP):
				ip_hdr = (struct iphdr *)skb->data;
				(card->dev->type == ARPHRD_IEEE802_TR) ?
				ip_tr_mc_map(ip_hdr->daddr, tg_addr):
				ip_eth_mc_map(ip_hdr->daddr, tg_addr);
				break;
			default:
				memcpy(tg_addr, card->dev->broadcast,
					card->dev->addr_len);
			}
