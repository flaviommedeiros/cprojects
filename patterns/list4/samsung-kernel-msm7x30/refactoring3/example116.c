switch (lp->p_encap) {
		case ISDN_NET_ENCAP_IPTYP:
			proto = ntohs(*(__be16 *)&buf[0]);
			p = &buf[2];
			break;
		case ISDN_NET_ENCAP_ETHER:
			proto = ntohs(*(__be16 *)&buf[12]);
			p = &buf[14];
			break;
		case ISDN_NET_ENCAP_CISCOHDLC:
			proto = ntohs(*(__be16 *)&buf[2]);
			p = &buf[4];
			break;
#ifdef CONFIG_ISDN_PPP
		case ISDN_NET_ENCAP_SYNCPPP:
			proto = ntohs(skb->protocol);
			p = &buf[IPPP_MAX_HEADER];
			break;
#endif
		}
