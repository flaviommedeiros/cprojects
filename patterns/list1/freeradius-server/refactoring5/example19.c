#ifdef PCAP_RAW_SOCKETS
if (sock->lsock.pcap) {
		packet = fr_dhcp_recv_pcap(sock->lsock.pcap);
	} else
#endif
	{
		packet = fr_dhcp_recv_socket(listener->fd);
	}
