switch (handlep->tp_version) {
	case TPACKET_V1:
		handle->read_op = pcap_read_linux_mmap_v1;
		break;
	case TPACKET_V1_64:
		handle->read_op = pcap_read_linux_mmap_v1_64;
		break;
#ifdef HAVE_TPACKET2
	case TPACKET_V2:
		handle->read_op = pcap_read_linux_mmap_v2;
		break;
#endif
#ifdef HAVE_TPACKET3
	case TPACKET_V3:
		handle->read_op = pcap_read_linux_mmap_v3;
		break;
#endif
	}
