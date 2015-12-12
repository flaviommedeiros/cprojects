switch (linktype) {

	case DLT_ARCNET:
		off_linktype.constant_part = 2;
		off_linkpl.constant_part = 6;
		off_nl = 0;		/* XXX in reality, variable! */
		off_nl_nosnap = 0;	/* no 802.2 LLC */
		break;

	case DLT_ARCNET_LINUX:
		off_linktype.constant_part = 4;
		off_linkpl.constant_part = 8;
		off_nl = 0;		/* XXX in reality, variable! */
		off_nl_nosnap = 0;	/* no 802.2 LLC */
		break;

	case DLT_EN10MB:
		off_linktype.constant_part = 12;
		off_linkpl.constant_part = 14;	/* Ethernet header length */
		off_nl = 0;		/* Ethernet II */
		off_nl_nosnap = 3;	/* 802.3+802.2 */
		break;

	case DLT_SLIP:
		/*
		 * SLIP doesn't have a link level type.  The 16 byte
		 * header is hacked into our SLIP driver.
		 */
		off_linktype.constant_part = -1;
		off_linkpl.constant_part = 16;
		off_nl = 0;
		off_nl_nosnap = 0;	/* no 802.2 LLC */
		break;

	case DLT_SLIP_BSDOS:
		/* XXX this may be the same as the DLT_PPP_BSDOS case */
		off_linktype.constant_part = -1;
		/* XXX end */
		off_linkpl.constant_part = 24;
		off_nl = 0;
		off_nl_nosnap = 0;	/* no 802.2 LLC */
		break;

	case DLT_NULL:
	case DLT_LOOP:
		off_linktype.constant_part = 0;
		off_linkpl.constant_part = 4;
		off_nl = 0;
		off_nl_nosnap = 0;	/* no 802.2 LLC */
		break;

	case DLT_ENC:
		off_linktype.constant_part = 0;
		off_linkpl.constant_part = 12;
		off_nl = 0;
		off_nl_nosnap = 0;	/* no 802.2 LLC */
		break;

	case DLT_PPP:
	case DLT_PPP_PPPD:
	case DLT_C_HDLC:		/* BSD/OS Cisco HDLC */
	case DLT_PPP_SERIAL:		/* NetBSD sync/async serial PPP */
		off_linktype.constant_part = 2;	/* skip HDLC-like framing */
		off_linkpl.constant_part = 4;	/* skip HDLC-like framing and protocol field */
		off_nl = 0;
		off_nl_nosnap = 0;	/* no 802.2 LLC */
		break;

	case DLT_PPP_ETHER:
		/*
		 * This does no include the Ethernet header, and
		 * only covers session state.
		 */
		off_linktype.constant_part = 6;
		off_linkpl.constant_part = 8;
		off_nl = 0;
		off_nl_nosnap = 0;	/* no 802.2 LLC */
		break;

	case DLT_PPP_BSDOS:
		off_linktype.constant_part = 5;
		off_linkpl.constant_part = 24;
		off_nl = 0;
		off_nl_nosnap = 0;	/* no 802.2 LLC */
		break;

	case DLT_FDDI:
		/*
		 * FDDI doesn't really have a link-level type field.
		 * We set "off_linktype" to the offset of the LLC header.
		 *
		 * To check for Ethernet types, we assume that SSAP = SNAP
		 * is being used and pick out the encapsulated Ethernet type.
		 * XXX - should we generate code to check for SNAP?
		 */
		off_linktype.constant_part = 13;
		off_linktype.constant_part += pcap_fddipad;
		off_linkpl.constant_part = 13;	/* FDDI MAC header length */
		off_linkpl.constant_part += pcap_fddipad;
		off_nl = 8;		/* 802.2+SNAP */
		off_nl_nosnap = 3;	/* 802.2 */
		break;

	case DLT_IEEE802:
		/*
		 * Token Ring doesn't really have a link-level type field.
		 * We set "off_linktype" to the offset of the LLC header.
		 *
		 * To check for Ethernet types, we assume that SSAP = SNAP
		 * is being used and pick out the encapsulated Ethernet type.
		 * XXX - should we generate code to check for SNAP?
		 *
		 * XXX - the header is actually variable-length.
		 * Some various Linux patched versions gave 38
		 * as "off_linktype" and 40 as "off_nl"; however,
		 * if a token ring packet has *no* routing
		 * information, i.e. is not source-routed, the correct
		 * values are 20 and 22, as they are in the vanilla code.
		 *
		 * A packet is source-routed iff the uppermost bit
		 * of the first byte of the source address, at an
		 * offset of 8, has the uppermost bit set.  If the
		 * packet is source-routed, the total number of bytes
		 * of routing information is 2 plus bits 0x1F00 of
		 * the 16-bit value at an offset of 14 (shifted right
		 * 8 - figure out which byte that is).
		 */
		off_linktype.constant_part = 14;
		off_linkpl.constant_part = 14;	/* Token Ring MAC header length */
		off_nl = 8;		/* 802.2+SNAP */
		off_nl_nosnap = 3;	/* 802.2 */
		break;

	case DLT_PRISM_HEADER:
	case DLT_IEEE802_11_RADIO_AVS:
	case DLT_IEEE802_11_RADIO:
		off_linkhdr.is_variable = 1;
		/* Fall through, 802.11 doesn't have a variable link
		 * prefix but is otherwise the same. */

	case DLT_IEEE802_11:
		/*
		 * 802.11 doesn't really have a link-level type field.
		 * We set "off_linktype.constant_part" to the offset of
		 * the LLC header.
		 *
		 * To check for Ethernet types, we assume that SSAP = SNAP
		 * is being used and pick out the encapsulated Ethernet type.
		 * XXX - should we generate code to check for SNAP?
		 *
		 * We also handle variable-length radio headers here.
		 * The Prism header is in theory variable-length, but in
		 * practice it's always 144 bytes long.  However, some
		 * drivers on Linux use ARPHRD_IEEE80211_PRISM, but
		 * sometimes or always supply an AVS header, so we
		 * have to check whether the radio header is a Prism
		 * header or an AVS header, so, in practice, it's
		 * variable-length.
		 */
		off_linktype.constant_part = 24;
		off_linkpl.constant_part = 0;	/* link-layer header is variable-length */
		off_linkpl.is_variable = 1;
		off_nl = 8;		/* 802.2+SNAP */
		off_nl_nosnap = 3;	/* 802.2 */
		break;

	case DLT_PPI:
		/*
		 * At the moment we treat PPI the same way that we treat
		 * normal Radiotap encoded packets. The difference is in
		 * the function that generates the code at the beginning
		 * to compute the header length.  Since this code generator
		 * of PPI supports bare 802.11 encapsulation only (i.e.
		 * the encapsulated DLT should be DLT_IEEE802_11) we
		 * generate code to check for this too.
		 */
		off_linktype.constant_part = 24;
		off_linkpl.constant_part = 0;	/* link-layer header is variable-length */
		off_linkpl.is_variable = 1;
		off_linkhdr.is_variable = 1;
		off_nl = 8;		/* 802.2+SNAP */
		off_nl_nosnap = 3;	/* 802.2 */
		break;

	case DLT_ATM_RFC1483:
	case DLT_ATM_CLIP:	/* Linux ATM defines this */
		/*
		 * assume routed, non-ISO PDUs
		 * (i.e., LLC = 0xAA-AA-03, OUT = 0x00-00-00)
		 *
		 * XXX - what about ISO PDUs, e.g. CLNP, ISIS, ESIS,
		 * or PPP with the PPP NLPID (e.g., PPPoA)?  The
		 * latter would presumably be treated the way PPPoE
		 * should be, so you can do "pppoe and udp port 2049"
		 * or "pppoa and tcp port 80" and have it check for
		 * PPPo{A,E} and a PPP protocol of IP and....
		 */
		off_linktype.constant_part = 0;
		off_linkpl.constant_part = 0;	/* packet begins with LLC header */
		off_nl = 8;		/* 802.2+SNAP */
		off_nl_nosnap = 3;	/* 802.2 */
		break;

	case DLT_SUNATM:
		/*
		 * Full Frontal ATM; you get AALn PDUs with an ATM
		 * pseudo-header.
		 */
		is_atm = 1;
		off_vpi = SUNATM_VPI_POS;
		off_vci = SUNATM_VCI_POS;
		off_proto = PROTO_POS;
		off_payload = SUNATM_PKT_BEGIN_POS;
		off_linktype.constant_part = off_payload;
		off_linkpl.constant_part = off_payload;	/* if LLC-encapsulated */
		off_nl = 8;		/* 802.2+SNAP */
		off_nl_nosnap = 3;	/* 802.2 */
		break;

	case DLT_RAW:
	case DLT_IPV4:
	case DLT_IPV6:
		off_linktype.constant_part = -1;
		off_linkpl.constant_part = 0;
		off_nl = 0;
		off_nl_nosnap = 0;	/* no 802.2 LLC */
		break;

	case DLT_LINUX_SLL:	/* fake header for Linux cooked socket */
		off_linktype.constant_part = 14;
		off_linkpl.constant_part = 16;
		off_nl = 0;
		off_nl_nosnap = 0;	/* no 802.2 LLC */
		break;

	case DLT_LTALK:
		/*
		 * LocalTalk does have a 1-byte type field in the LLAP header,
		 * but really it just indicates whether there is a "short" or
		 * "long" DDP packet following.
		 */
		off_linktype.constant_part = -1;
		off_linkpl.constant_part = 0;
		off_nl = 0;
		off_nl_nosnap = 0;	/* no 802.2 LLC */
		break;

	case DLT_IP_OVER_FC:
		/*
		 * RFC 2625 IP-over-Fibre-Channel doesn't really have a
		 * link-level type field.  We set "off_linktype" to the
		 * offset of the LLC header.
		 *
		 * To check for Ethernet types, we assume that SSAP = SNAP
		 * is being used and pick out the encapsulated Ethernet type.
		 * XXX - should we generate code to check for SNAP? RFC
		 * 2625 says SNAP should be used.
		 */
		off_linktype.constant_part = 16;
		off_linkpl.constant_part = 16;
		off_nl = 8;		/* 802.2+SNAP */
		off_nl_nosnap = 3;	/* 802.2 */
		break;

	case DLT_FRELAY:
		/*
		 * XXX - we should set this to handle SNAP-encapsulated
		 * frames (NLPID of 0x80).
		 */
		off_linktype.constant_part = -1;
		off_linkpl.constant_part = 0;
		off_nl = 0;
		off_nl_nosnap = 0;	/* no 802.2 LLC */
		break;

                /*
                 * the only BPF-interesting FRF.16 frames are non-control frames;
                 * Frame Relay has a variable length link-layer
                 * so lets start with offset 4 for now and increments later on (FIXME);
                 */
	case DLT_MFR:
		off_linktype.constant_part = -1;
		off_linkpl.constant_part = 0;
		off_nl = 4;
		off_nl_nosnap = 0;	/* XXX - for now -> no 802.2 LLC */
		break;

	case DLT_APPLE_IP_OVER_IEEE1394:
		off_linktype.constant_part = 16;
		off_linkpl.constant_part = 18;
		off_nl = 0;
		off_nl_nosnap = 0;	/* no 802.2 LLC */
		break;

	case DLT_SYMANTEC_FIREWALL:
		off_linktype.constant_part = 6;
		off_linkpl.constant_part = 44;
		off_nl = 0;		/* Ethernet II */
		off_nl_nosnap = 0;	/* XXX - what does it do with 802.3 packets? */
		break;

#ifdef HAVE_NET_PFVAR_H
	case DLT_PFLOG:
		off_linktype.constant_part = 0;
		off_linkpl.constant_part = PFLOG_HDRLEN;
		off_nl = 0;
		off_nl_nosnap = 0;	/* no 802.2 LLC */
		break;
#endif

        case DLT_JUNIPER_MFR:
        case DLT_JUNIPER_MLFR:
        case DLT_JUNIPER_MLPPP:
        case DLT_JUNIPER_PPP:
        case DLT_JUNIPER_CHDLC:
        case DLT_JUNIPER_FRELAY:
                off_linktype.constant_part = 4;
		off_linkpl.constant_part = 4;
		off_nl = 0;
		off_nl_nosnap = -1;	/* no 802.2 LLC */
                break;

	case DLT_JUNIPER_ATM1:
		off_linktype.constant_part = 4;		/* in reality variable between 4-8 */
		off_linkpl.constant_part = 4;	/* in reality variable between 4-8 */
		off_nl = 0;
		off_nl_nosnap = 10;
		break;

	case DLT_JUNIPER_ATM2:
		off_linktype.constant_part = 8;		/* in reality variable between 8-12 */
		off_linkpl.constant_part = 8;	/* in reality variable between 8-12 */
		off_nl = 0;
		off_nl_nosnap = 10;
		break;

		/* frames captured on a Juniper PPPoE service PIC
		 * contain raw ethernet frames */
	case DLT_JUNIPER_PPPOE:
        case DLT_JUNIPER_ETHER:
        	off_linkpl.constant_part = 14;
		off_linktype.constant_part = 16;
		off_nl = 18;		/* Ethernet II */
		off_nl_nosnap = 21;	/* 802.3+802.2 */
		break;

	case DLT_JUNIPER_PPPOE_ATM:
		off_linktype.constant_part = 4;
		off_linkpl.constant_part = 6;
		off_nl = 0;
		off_nl_nosnap = -1;	/* no 802.2 LLC */
		break;

	case DLT_JUNIPER_GGSN:
		off_linktype.constant_part = 6;
		off_linkpl.constant_part = 12;
		off_nl = 0;
		off_nl_nosnap = -1;	/* no 802.2 LLC */
		break;

	case DLT_JUNIPER_ES:
		off_linktype.constant_part = 6;
		off_linkpl.constant_part = -1;	/* not really a network layer but raw IP addresses */
		off_nl = -1;		/* not really a network layer but raw IP addresses */
		off_nl_nosnap = -1;	/* no 802.2 LLC */
		break;

	case DLT_JUNIPER_MONITOR:
		off_linktype.constant_part = 12;
		off_linkpl.constant_part = 12;
		off_nl = 0;		/* raw IP/IP6 header */
		off_nl_nosnap = -1;	/* no 802.2 LLC */
		break;

	case DLT_BACNET_MS_TP:
		off_linktype.constant_part = -1;
		off_linkpl.constant_part = -1;
		off_nl = -1;
		off_nl_nosnap = -1;
		break;

	case DLT_JUNIPER_SERVICES:
		off_linktype.constant_part = 12;
		off_linkpl.constant_part = -1;	/* L3 proto location dep. on cookie type */
		off_nl = -1;		/* L3 proto location dep. on cookie type */
		off_nl_nosnap = -1;	/* no 802.2 LLC */
		break;

	case DLT_JUNIPER_VP:
		off_linktype.constant_part = 18;
		off_linkpl.constant_part = -1;
		off_nl = -1;
		off_nl_nosnap = -1;
		break;

	case DLT_JUNIPER_ST:
		off_linktype.constant_part = 18;
		off_linkpl.constant_part = -1;
		off_nl = -1;
		off_nl_nosnap = -1;
		break;

	case DLT_JUNIPER_ISM:
		off_linktype.constant_part = 8;
		off_linkpl.constant_part = -1;
		off_nl = -1;
		off_nl_nosnap = -1;
		break;

	case DLT_JUNIPER_VS:
	case DLT_JUNIPER_SRX_E2E:
	case DLT_JUNIPER_FIBRECHANNEL:
	case DLT_JUNIPER_ATM_CEMIC:
		off_linktype.constant_part = 8;
		off_linkpl.constant_part = -1;
		off_nl = -1;
		off_nl_nosnap = -1;
		break;

	case DLT_MTP2:
		off_li = 2;
		off_li_hsl = 4;
		off_sio = 3;
		off_opc = 4;
		off_dpc = 4;
		off_sls = 7;
		off_linktype.constant_part = -1;
		off_linkpl.constant_part = -1;
		off_nl = -1;
		off_nl_nosnap = -1;
		break;

	case DLT_MTP2_WITH_PHDR:
		off_li = 6;
		off_li_hsl = 8;
		off_sio = 7;
		off_opc = 8;
		off_dpc = 8;
		off_sls = 11;
		off_linktype.constant_part = -1;
		off_linkpl.constant_part = -1;
		off_nl = -1;
		off_nl_nosnap = -1;
		break;

	case DLT_ERF:
		off_li = 22;
		off_li_hsl = 24;
		off_sio = 23;
		off_opc = 24;
		off_dpc = 24;
		off_sls = 27;
		off_linktype.constant_part = -1;
		off_linkpl.constant_part = -1;
		off_nl = -1;
		off_nl_nosnap = -1;
		break;

	case DLT_PFSYNC:
		off_linktype.constant_part = -1;
		off_linkpl.constant_part = 4;
		off_nl = 0;
		off_nl_nosnap = 0;
		break;

	case DLT_AX25_KISS:
		/*
		 * Currently, only raw "link[N:M]" filtering is supported.
		 */
		off_linktype.constant_part = -1;	/* variable, min 15, max 71 steps of 7 */
		off_linkpl.constant_part = -1;
		off_nl = -1;		/* variable, min 16, max 71 steps of 7 */
		off_nl_nosnap = -1;	/* no 802.2 LLC */
		break;

	case DLT_IPNET:
		off_linktype.constant_part = 1;
		off_linkpl.constant_part = 24;	/* ipnet header length */
		off_nl = 0;
		off_nl_nosnap = -1;
		break;

	case DLT_NETANALYZER:
		off_linkhdr.constant_part = 4;	/* Ethernet header is past 4-byte pseudo-header */
		off_linktype.constant_part = off_linkhdr.constant_part + 12;
		off_linkpl.constant_part = off_linkhdr.constant_part + 14;	/* pseudo-header+Ethernet header length */
		off_nl = 0;		/* Ethernet II */
		off_nl_nosnap = 3;	/* 802.3+802.2 */
		break;

	case DLT_NETANALYZER_TRANSPARENT:
		off_linkhdr.constant_part = 12;	/* MAC header is past 4-byte pseudo-header, preamble, and SFD */
		off_linktype.constant_part = off_linkhdr.constant_part + 12;
		off_linkpl.constant_part = off_linkhdr.constant_part + 14;	/* pseudo-header+preamble+SFD+Ethernet header length */
		off_nl = 0;		/* Ethernet II */
		off_nl_nosnap = 3;	/* 802.3+802.2 */
		break;

	default:
		/*
		 * For values in the range in which we've assigned new
		 * DLT_ values, only raw "link[N:M]" filtering is supported.
		 */
		if (linktype >= DLT_MATCHING_MIN &&
		    linktype <= DLT_MATCHING_MAX) {
			off_linktype.constant_part = -1;
			off_linkpl.constant_part = -1;
			off_nl = -1;
			off_nl_nosnap = -1;
		} else {
			bpf_error("unknown data link type %d", linktype);
		}
		break;
	}
