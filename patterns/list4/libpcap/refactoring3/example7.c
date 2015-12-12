switch (mactype) {

	case DL_CSMACD:
	case DL_ETHER:
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
		p->dlt_list = (u_int *)malloc(sizeof(u_int) * 2);
		/*
		 * If that fails, just leave the list empty.
		 */
		if (p->dlt_list != NULL) {
			p->dlt_list[0] = DLT_EN10MB;
			p->dlt_list[1] = DLT_DOCSIS;
			p->dlt_count = 2;
		}
		break;

	case DL_FDDI:
		p->linktype = DLT_FDDI;
		p->offset = 3;
		break;

	case DL_TPR:
		/* XXX - what about DL_TPB?  Is that Token Bus?  */
		p->linktype = DLT_IEEE802;
		p->offset = 2;
		break;

#ifdef HAVE_SOLARIS
	case DL_IPATM:
		p->linktype = DLT_SUNATM;
		p->offset = 0;  /* works for LANE and LLC encapsulation */
		break;
#endif

	default:
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE, "unknown mactype %u",
		    mactype);
		retv = -1;
	}
