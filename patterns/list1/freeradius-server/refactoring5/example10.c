#ifdef WITH_TCP
if (proto) {
		sockfd = fr_socket_client_tcp(NULL, &server_ipaddr, server_port, false);
	} else
#endif
	sockfd = fr_socket(&client_ipaddr, client_port);
