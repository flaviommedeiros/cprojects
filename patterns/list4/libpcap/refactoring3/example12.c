switch (handlep->tp_version) {
	case TPACKET_V1:
		return (h.h1->tp_status);
		break;
	case TPACKET_V1_64:
		return (h.h1_64->tp_status);
		break;
#ifdef HAVE_TPACKET2
	case TPACKET_V2:
		return (h.h2->tp_status);
		break;
#endif
#ifdef HAVE_TPACKET3
	case TPACKET_V3:
		return (h.h3->hdr.bh1.block_status);
		break;
#endif
	}
