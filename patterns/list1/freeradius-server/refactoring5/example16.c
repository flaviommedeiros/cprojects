#ifdef HAVE_LINUX_IF_PACKET_H
if (raw_mode) {
		sockfd = fr_socket_packet(iface_ind, &ll);
	} else
#endif
	{
		sockfd = fr_socket(&request->src_ipaddr, request->src_port);
	}
