#ifdef WITH_TCP
if (proto) {
				mysockfd = fr_socket_client_tcp(NULL,
								&request->packet->dst_ipaddr,
								request->packet->dst_port, false);
			} else
#endif
			mysockfd = fr_socket(&client_ipaddr, 0);
