switch (devparams.end_dev_type) {

	case ENDT_10MB:
		p->linktype = DLT_EN10MB;
		p->offset = 2;
		/*
		 * This is (presumably) a real Ethernet capture; give it a
		 * link-layer-type list with DLT_EN10MB and DLT_DOCSIS, so
		 * that an application can let you choose it, in case you're
		 * capturing DOCSIS traffic that a Cisco Cable Modem
		 * Termination System is putting out onto an Ethernet (it
		 * doesn't put an Ethernet header onto the wire, it puts raw
		 * DOCSIS frames out on the wire inside the low-level
		 * Ethernet framing).
		 */
		p->dlt_list = (u_int *) malloc(sizeof(u_int) * 2);
		/*
		 * If that fails, just leave the list empty.
		 */
		if (p->dlt_list != NULL) {
			p->dlt_list[0] = DLT_EN10MB;
			p->dlt_list[1] = DLT_DOCSIS;
			p->dlt_count = 2;
		}
		break;

	case ENDT_FDDI:
		p->linktype = DLT_FDDI;
		break;

#ifdef ENDT_SLIP
	case ENDT_SLIP:
		p->linktype = DLT_SLIP;
		break;
#endif

#ifdef ENDT_PPP
	case ENDT_PPP:
		p->linktype = DLT_PPP;
		break;
#endif

#ifdef ENDT_LOOPBACK
	case ENDT_LOOPBACK:
		/*
		 * It appears to use Ethernet framing, at least on
		 * Digital UNIX 4.0.
		 */
		p->linktype = DLT_EN10MB;
		p->offset = 2;
		break;
#endif

#ifdef ENDT_TRN
	case ENDT_TRN:
		p->linktype = DLT_IEEE802;
		break;
#endif

	default:
		/*
		 * XXX - what about ENDT_IEEE802?  The pfilt.h header
		 * file calls this "IEEE 802 networks (non-Ethernet)",
		 * but that doesn't specify a specific link layer type;
		 * it could be 802.4, or 802.5 (except that 802.5 is
		 * ENDT_TRN), or 802.6, or 802.11, or....  That's why
		 * DLT_IEEE802 was hijacked to mean Token Ring in various
		 * BSDs, and why we went along with that hijacking.
		 *
		 * XXX - what about ENDT_HDLC and ENDT_NULL?
		 * Presumably, as ENDT_OTHER is just "Miscellaneous
		 * framing", there's not much we can do, as that
		 * doesn't specify a particular type of header.
		 */
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "unknown data-link type %u", devparams.end_dev_type);
		goto bad;
	}
