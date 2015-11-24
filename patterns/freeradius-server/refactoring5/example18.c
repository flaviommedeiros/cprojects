#ifdef HAVE_LIBPCAP
if (raw_mode) {
		ret = send_with_pcap(&reply, request);
	} else
#endif
	{
		ret = send_with_socket(&reply, request);
	}
