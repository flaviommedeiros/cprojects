switch (linktype) {

	case DLT_EN10MB:
	case DLT_NETANALYZER:
	case DLT_NETANALYZER_TRANSPARENT:
		/* Geneve has an EtherType regardless of whether there is an
		 * L2 header. */
		if (!is_geneve)
			b0 = gen_prevlinkhdr_check();
		else
			b0 = NULL;

		b1 = gen_ether_linktype(proto);
		if (b0 != NULL)
			gen_and(b0, b1);
		return b1;
		/*NOTREACHED*/
		break;

	case DLT_C_HDLC:
		switch (proto) {

		case LLCSAP_ISONS:
			proto = (proto << 8 | LLCSAP_ISONS);
			/* fall through */

		default:
			return gen_cmp(OR_LINKTYPE, 0, BPF_H, (bpf_int32)proto);
			/*NOTREACHED*/
			break;
		}
		break;

	case DLT_IEEE802_11:
	case DLT_PRISM_HEADER:
	case DLT_IEEE802_11_RADIO_AVS:
	case DLT_IEEE802_11_RADIO:
	case DLT_PPI:
		/*
		 * Check that we have a data frame.
		 */
		b0 = gen_check_802_11_data_frame();

		/*
		 * Now check for the specified link-layer type.
		 */
		b1 = gen_llc_linktype(proto);
		gen_and(b0, b1);
		return b1;
		/*NOTREACHED*/
		break;

	case DLT_FDDI:
		/*
		 * XXX - check for LLC frames.
		 */
		return gen_llc_linktype(proto);
		/*NOTREACHED*/
		break;

	case DLT_IEEE802:
		/*
		 * XXX - check for LLC PDUs, as per IEEE 802.5.
		 */
		return gen_llc_linktype(proto);
		/*NOTREACHED*/
		break;

	case DLT_ATM_RFC1483:
	case DLT_ATM_CLIP:
	case DLT_IP_OVER_FC:
		return gen_llc_linktype(proto);
		/*NOTREACHED*/
		break;

	case DLT_SUNATM:
		/*
		 * Check for an LLC-encapsulated version of this protocol;
		 * if we were checking for LANE, linktype would no longer
		 * be DLT_SUNATM.
		 *
		 * Check for LLC encapsulation and then check the protocol.
		 */
		b0 = gen_atmfield_code(A_PROTOTYPE, PT_LLC, BPF_JEQ, 0);
		b1 = gen_llc_linktype(proto);
		gen_and(b0, b1);
		return b1;
		/*NOTREACHED*/
		break;

	case DLT_LINUX_SLL:
		return gen_linux_sll_linktype(proto);
		/*NOTREACHED*/
		break;

	case DLT_SLIP:
	case DLT_SLIP_BSDOS:
	case DLT_RAW:
		/*
		 * These types don't provide any type field; packets
		 * are always IPv4 or IPv6.
		 *
		 * XXX - for IPv4, check for a version number of 4, and,
		 * for IPv6, check for a version number of 6?
		 */
		switch (proto) {

		case ETHERTYPE_IP:
			/* Check for a version number of 4. */
			return gen_mcmp(OR_LINKHDR, 0, BPF_B, 0x40, 0xF0);

		case ETHERTYPE_IPV6:
			/* Check for a version number of 6. */
			return gen_mcmp(OR_LINKHDR, 0, BPF_B, 0x60, 0xF0);

		default:
			return gen_false();		/* always false */
		}
		/*NOTREACHED*/
		break;

	case DLT_IPV4:
		/*
		 * Raw IPv4, so no type field.
		 */
		if (proto == ETHERTYPE_IP)
			return gen_true();		/* always true */

		/* Checking for something other than IPv4; always false */
		return gen_false();
		/*NOTREACHED*/
		break;

	case DLT_IPV6:
		/*
		 * Raw IPv6, so no type field.
		 */
		if (proto == ETHERTYPE_IPV6)
			return gen_true();		/* always true */

		/* Checking for something other than IPv6; always false */
		return gen_false();
		/*NOTREACHED*/
		break;

	case DLT_PPP:
	case DLT_PPP_PPPD:
	case DLT_PPP_SERIAL:
	case DLT_PPP_ETHER:
		/*
		 * We use Ethernet protocol types inside libpcap;
		 * map them to the corresponding PPP protocol types.
		 */
		proto = ethertype_to_ppptype(proto);
		return gen_cmp(OR_LINKTYPE, 0, BPF_H, (bpf_int32)proto);
		/*NOTREACHED*/
		break;

	case DLT_PPP_BSDOS:
		/*
		 * We use Ethernet protocol types inside libpcap;
		 * map them to the corresponding PPP protocol types.
		 */
		switch (proto) {

		case ETHERTYPE_IP:
			/*
			 * Also check for Van Jacobson-compressed IP.
			 * XXX - do this for other forms of PPP?
			 */
			b0 = gen_cmp(OR_LINKTYPE, 0, BPF_H, PPP_IP);
			b1 = gen_cmp(OR_LINKTYPE, 0, BPF_H, PPP_VJC);
			gen_or(b0, b1);
			b0 = gen_cmp(OR_LINKTYPE, 0, BPF_H, PPP_VJNC);
			gen_or(b1, b0);
			return b0;

		default:
			proto = ethertype_to_ppptype(proto);
			return gen_cmp(OR_LINKTYPE, 0, BPF_H,
				(bpf_int32)proto);
		}
		/*NOTREACHED*/
		break;

	case DLT_NULL:
	case DLT_LOOP:
	case DLT_ENC:
		/*
		 * For DLT_NULL, the link-layer header is a 32-bit
		 * word containing an AF_ value in *host* byte order,
		 * and for DLT_ENC, the link-layer header begins
		 * with a 32-bit work containing an AF_ value in
		 * host byte order.
		 *
		 * In addition, if we're reading a saved capture file,
		 * the host byte order in the capture may not be the
		 * same as the host byte order on this machine.
		 *
		 * For DLT_LOOP, the link-layer header is a 32-bit
		 * word containing an AF_ value in *network* byte order.
		 *
		 * XXX - AF_ values may, unfortunately, be platform-
		 * dependent; for example, FreeBSD's AF_INET6 is 24
		 * whilst NetBSD's and OpenBSD's is 26.
		 *
		 * This means that, when reading a capture file, just
		 * checking for our AF_INET6 value won't work if the
		 * capture file came from another OS.
		 */
		switch (proto) {

		case ETHERTYPE_IP:
			proto = AF_INET;
			break;

#ifdef INET6
		case ETHERTYPE_IPV6:
			proto = AF_INET6;
			break;
#endif

		default:
			/*
			 * Not a type on which we support filtering.
			 * XXX - support those that have AF_ values
			 * #defined on this platform, at least?
			 */
			return gen_false();
		}

		if (linktype == DLT_NULL || linktype == DLT_ENC) {
			/*
			 * The AF_ value is in host byte order, but
			 * the BPF interpreter will convert it to
			 * network byte order.
			 *
			 * If this is a save file, and it's from a
			 * machine with the opposite byte order to
			 * ours, we byte-swap the AF_ value.
			 *
			 * Then we run it through "htonl()", and
			 * generate code to compare against the result.
			 */
			if (bpf_pcap->rfile != NULL && bpf_pcap->swapped)
				proto = SWAPLONG(proto);
			proto = htonl(proto);
		}
		return (gen_cmp(OR_LINKHDR, 0, BPF_W, (bpf_int32)proto));

#ifdef HAVE_NET_PFVAR_H
	case DLT_PFLOG:
		/*
		 * af field is host byte order in contrast to the rest of
		 * the packet.
		 */
		if (proto == ETHERTYPE_IP)
			return (gen_cmp(OR_LINKHDR, offsetof(struct pfloghdr, af),
			    BPF_B, (bpf_int32)AF_INET));
		else if (proto == ETHERTYPE_IPV6)
			return (gen_cmp(OR_LINKHDR, offsetof(struct pfloghdr, af),
			    BPF_B, (bpf_int32)AF_INET6));
		else
			return gen_false();
		/*NOTREACHED*/
		break;
#endif /* HAVE_NET_PFVAR_H */

	case DLT_ARCNET:
	case DLT_ARCNET_LINUX:
		/*
		 * XXX should we check for first fragment if the protocol
		 * uses PHDS?
		 */
		switch (proto) {

		default:
			return gen_false();

		case ETHERTYPE_IPV6:
			return (gen_cmp(OR_LINKTYPE, 0, BPF_B,
				(bpf_int32)ARCTYPE_INET6));

		case ETHERTYPE_IP:
			b0 = gen_cmp(OR_LINKTYPE, 0, BPF_B,
				     (bpf_int32)ARCTYPE_IP);
			b1 = gen_cmp(OR_LINKTYPE, 0, BPF_B,
				     (bpf_int32)ARCTYPE_IP_OLD);
			gen_or(b0, b1);
			return (b1);

		case ETHERTYPE_ARP:
			b0 = gen_cmp(OR_LINKTYPE, 0, BPF_B,
				     (bpf_int32)ARCTYPE_ARP);
			b1 = gen_cmp(OR_LINKTYPE, 0, BPF_B,
				     (bpf_int32)ARCTYPE_ARP_OLD);
			gen_or(b0, b1);
			return (b1);

		case ETHERTYPE_REVARP:
			return (gen_cmp(OR_LINKTYPE, 0, BPF_B,
					(bpf_int32)ARCTYPE_REVARP));

		case ETHERTYPE_ATALK:
			return (gen_cmp(OR_LINKTYPE, 0, BPF_B,
					(bpf_int32)ARCTYPE_ATALK));
		}
		/*NOTREACHED*/
		break;

	case DLT_LTALK:
		switch (proto) {
		case ETHERTYPE_ATALK:
			return gen_true();
		default:
			return gen_false();
		}
		/*NOTREACHED*/
		break;

	case DLT_FRELAY:
		/*
		 * XXX - assumes a 2-byte Frame Relay header with
		 * DLCI and flags.  What if the address is longer?
		 */
		switch (proto) {

		case ETHERTYPE_IP:
			/*
			 * Check for the special NLPID for IP.
			 */
			return gen_cmp(OR_LINKHDR, 2, BPF_H, (0x03<<8) | 0xcc);

		case ETHERTYPE_IPV6:
			/*
			 * Check for the special NLPID for IPv6.
			 */
			return gen_cmp(OR_LINKHDR, 2, BPF_H, (0x03<<8) | 0x8e);

		case LLCSAP_ISONS:
			/*
			 * Check for several OSI protocols.
			 *
			 * Frame Relay packets typically have an OSI
			 * NLPID at the beginning; we check for each
			 * of them.
			 *
			 * What we check for is the NLPID and a frame
			 * control field of UI, i.e. 0x03 followed
			 * by the NLPID.
			 */
			b0 = gen_cmp(OR_LINKHDR, 2, BPF_H, (0x03<<8) | ISO8473_CLNP);
			b1 = gen_cmp(OR_LINKHDR, 2, BPF_H, (0x03<<8) | ISO9542_ESIS);
			b2 = gen_cmp(OR_LINKHDR, 2, BPF_H, (0x03<<8) | ISO10589_ISIS);
			gen_or(b1, b2);
			gen_or(b0, b2);
			return b2;

		default:
			return gen_false();
		}
		/*NOTREACHED*/
		break;

	case DLT_MFR:
		bpf_error("Multi-link Frame Relay link-layer type filtering not implemented");

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

		/* just lets verify the magic number for now -
		 * on ATM we may have up to 6 different encapsulations on the wire
		 * and need a lot of heuristics to figure out that the payload
		 * might be;
		 *
		 * FIXME encapsulation specific BPF_ filters
		 */
		return gen_mcmp(OR_LINKHDR, 0, BPF_W, 0x4d474300, 0xffffff00); /* compare the magic number */

	case DLT_BACNET_MS_TP:
		return gen_mcmp(OR_LINKHDR, 0, BPF_W, 0x55FF0000, 0xffff0000);

	case DLT_IPNET:
		return gen_ipnet_linktype(proto);

	case DLT_LINUX_IRDA:
		bpf_error("IrDA link-layer type filtering not implemented");

	case DLT_DOCSIS:
		bpf_error("DOCSIS link-layer type filtering not implemented");

	case DLT_MTP2:
	case DLT_MTP2_WITH_PHDR:
		bpf_error("MTP2 link-layer type filtering not implemented");

	case DLT_ERF:
		bpf_error("ERF link-layer type filtering not implemented");

	case DLT_PFSYNC:
		bpf_error("PFSYNC link-layer type filtering not implemented");

	case DLT_LINUX_LAPD:
		bpf_error("LAPD link-layer type filtering not implemented");

	case DLT_USB:
	case DLT_USB_LINUX:
	case DLT_USB_LINUX_MMAPPED:
		bpf_error("USB link-layer type filtering not implemented");

	case DLT_BLUETOOTH_HCI_H4:
	case DLT_BLUETOOTH_HCI_H4_WITH_PHDR:
		bpf_error("Bluetooth link-layer type filtering not implemented");

	case DLT_CAN20B:
	case DLT_CAN_SOCKETCAN:
		bpf_error("CAN link-layer type filtering not implemented");

	case DLT_IEEE802_15_4:
	case DLT_IEEE802_15_4_LINUX:
	case DLT_IEEE802_15_4_NONASK_PHY:
	case DLT_IEEE802_15_4_NOFCS:
		bpf_error("IEEE 802.15.4 link-layer type filtering not implemented");

	case DLT_IEEE802_16_MAC_CPS_RADIO:
		bpf_error("IEEE 802.16 link-layer type filtering not implemented");

	case DLT_SITA:
		bpf_error("SITA link-layer type filtering not implemented");

	case DLT_RAIF1:
		bpf_error("RAIF1 link-layer type filtering not implemented");

	case DLT_IPMB:
		bpf_error("IPMB link-layer type filtering not implemented");

	case DLT_AX25_KISS:
		bpf_error("AX.25 link-layer type filtering not implemented");

	case DLT_NFLOG:
		/* Using the fixed-size NFLOG header it is possible to tell only
		 * the address family of the packet, other meaningful data is
		 * either missing or behind TLVs.
		 */
		bpf_error("NFLOG link-layer type filtering not implemented");

	default:
		/*
		 * Does this link-layer header type have a field
		 * indicating the type of the next protocol?  If
		 * so, off_linktype.constant_part will be the offset of that
		 * field in the packet; if not, it will be -1.
		 */
		if (off_linktype.constant_part != (u_int)-1) {
			/*
			 * Yes; assume it's an Ethernet type.  (If
			 * it's not, it needs to be handled specially
			 * above.)
			 */
			return gen_cmp(OR_LINKTYPE, 0, BPF_H, (bpf_int32)proto);
		} else {
			/*
			 * No; report an error.
			 */
			description = pcap_datalink_val_to_description(linktype);
			if (description != NULL) {
				bpf_error("%s link-layer type filtering not implemented",
				    description);
			} else {
				bpf_error("DLT %u link-layer type filtering not implemented",
				    linktype);
			}
		}
		break;
	}
