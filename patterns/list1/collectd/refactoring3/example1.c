switch (pcap_datalink (pcap_obj))
    {
	case DLT_EN10MB:
	    status = handle_ether (pkt, hdr->caplen);
	    break;
#if HAVE_NET_IF_PPP_H
	case DLT_PPP:
	    status = handle_ppp (pkt, hdr->caplen);
	    break;
#endif
#ifdef DLT_LOOP
	case DLT_LOOP:
	    status = handle_loop (pkt, hdr->caplen);
	    break;
#endif
#ifdef DLT_RAW
	case DLT_RAW:
	    status = handle_raw (pkt, hdr->caplen);
	    break;
#endif
#ifdef DLT_LINUX_SLL
	case DLT_LINUX_SLL:
	    status = handle_linux_sll (pkt, hdr->caplen);
	    break;
#endif
	case DLT_NULL:
	    status = handle_null (pkt, hdr->caplen);
	    break;

	default:
	    ERROR ("handle_pcap: unsupported data link type %d",
		    pcap_datalink(pcap_obj));
	    status = 0;
	    break;
    }
