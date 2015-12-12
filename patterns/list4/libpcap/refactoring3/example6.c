switch (linktype) {
	case DLT_SLIP:
		b0 = gen_relation(BPF_JEQ,
			  gen_load(Q_LINK, gen_loadi(0), 1),
			  gen_loadi(0),
			  dir);
		break;

	case DLT_IPNET:
		if (dir) {
			/* match outgoing packets */
			b0 = gen_cmp(OR_LINKHDR, 2, BPF_H, IPNET_OUTBOUND);
		} else {
			/* match incoming packets */
			b0 = gen_cmp(OR_LINKHDR, 2, BPF_H, IPNET_INBOUND);
		}
		break;

	case DLT_LINUX_SLL:
		/* match outgoing packets */
		b0 = gen_cmp(OR_LINKHDR, 0, BPF_H, LINUX_SLL_OUTGOING);
		if (!dir) {
			/* to filter on inbound traffic, invert the match */
			gen_not(b0);
		}
		break;

#ifdef HAVE_NET_PFVAR_H
	case DLT_PFLOG:
		b0 = gen_cmp(OR_LINKHDR, offsetof(struct pfloghdr, dir), BPF_B,
		    (bpf_int32)((dir == 0) ? PF_IN : PF_OUT));
		break;
#endif

	case DLT_PPP_PPPD:
		if (dir) {
			/* match outgoing packets */
			b0 = gen_cmp(OR_LINKHDR, 0, BPF_B, PPP_PPPD_OUT);
		} else {
			/* match incoming packets */
			b0 = gen_cmp(OR_LINKHDR, 0, BPF_B, PPP_PPPD_IN);
		}
		break;

        case DLT_JUNIPER_MFR:
        case DLT_JUNIPER_MLFR:
        case DLT_JUNIPER_MLPPP:
	case DLT_JUNIPER_ATM1:
	case DLT_JUNIPER_ATM2:
	case DLT_JUNIPER_PPPOE:
	case DLT_JUNIPER_PPPOE_ATM:
        case DLT_JUNIPER_GGSN:
        case DLT_JUNIPER_ES:
        case DLT_JUNIPER_MONITOR:
        case DLT_JUNIPER_SERVICES:
        case DLT_JUNIPER_ETHER:
        case DLT_JUNIPER_PPP:
        case DLT_JUNIPER_FRELAY:
        case DLT_JUNIPER_CHDLC:
        case DLT_JUNIPER_VP:
        case DLT_JUNIPER_ST:
        case DLT_JUNIPER_ISM:
        case DLT_JUNIPER_VS:
        case DLT_JUNIPER_SRX_E2E:
        case DLT_JUNIPER_FIBRECHANNEL:
	case DLT_JUNIPER_ATM_CEMIC:

		/* juniper flags (including direction) are stored
		 * the byte after the 3-byte magic number */
		if (dir) {
			/* match outgoing packets */
			b0 = gen_mcmp(OR_LINKHDR, 3, BPF_B, 0, 0x01);
		} else {
			/* match incoming packets */
			b0 = gen_mcmp(OR_LINKHDR, 3, BPF_B, 1, 0x01);
		}
		break;

	default:
		/*
		 * If we have packet meta-data indicating a direction,
		 * check it, otherwise give up as this link-layer type
		 * has nothing in the packet data.
		 */
#if defined(linux) && defined(PF_PACKET) && defined(SO_ATTACH_FILTER)
		/*
		 * This is Linux with PF_PACKET support.
		 * If this is a *live* capture, we can look at
		 * special meta-data in the filter expression;
		 * if it's a savefile, we can't.
		 */
		if (bpf_pcap->rfile != NULL) {
			/* We have a FILE *, so this is a savefile */
			bpf_error("inbound/outbound not supported on linktype %d when reading savefiles",
			    linktype);
			b0 = NULL;
			/* NOTREACHED */
		}
		/* match outgoing packets */
		b0 = gen_cmp(OR_LINKHDR, SKF_AD_OFF + SKF_AD_PKTTYPE, BPF_H,
		             PACKET_OUTGOING);
		if (!dir) {
			/* to filter on inbound traffic, invert the match */
			gen_not(b0);
		}
#else /* defined(linux) && defined(PF_PACKET) && defined(SO_ATTACH_FILTER) */
		bpf_error("inbound/outbound not supported on linktype %d",
		    linktype);
		b0 = NULL;
		/* NOTREACHED */
#endif /* defined(linux) && defined(PF_PACKET) && defined(SO_ATTACH_FILTER) */
	}
