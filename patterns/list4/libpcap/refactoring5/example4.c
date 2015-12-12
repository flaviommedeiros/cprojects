#ifdef PCAP_FDDIPAD
if (v == DLT_FDDI)
		p->fddipad = PCAP_FDDIPAD;
	else
#endif
		p->fddipad = 0;
