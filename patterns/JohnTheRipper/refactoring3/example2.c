switch (pcap_datalink(pd)) {
	case DLT_EN10MB:
		offset = 14;
		break;
	case DLT_IEEE802:
		offset = 22;
		break;
	case DLT_IEEE802_11_RADIO:
		offset = 56;	/* 64+32...? */
		break;
	case DLT_IEEE802_11:
		offset = 32;
		break;
	case DLT_FDDI:
		offset = 21;
		break;
#ifdef DLT_PPP
	case DLT_PPP:
		offset = 24;
		break;
#endif
#ifdef DLT_LINUX_SLL
	case DLT_LINUX_SLL:
		offset = 16;
		break;
#endif
#ifdef DLT_LOOP
	case DLT_LOOP:
#endif
	case DLT_NULL:
		offset = 4;
		break;
	default:
		break;
	}
