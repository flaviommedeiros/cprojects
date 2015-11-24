#ifdef WITH_TLS
if (request->home_server->tls) {
			RDEBUG2("Proxying request to home server %s port %d (TLS) timeout %d.%06d",
				inet_ntop(request->proxy->dst_ipaddr.af,
					  &request->proxy->dst_ipaddr.ipaddr,
					  buffer, sizeof(buffer)),
				request->proxy->dst_port,
				(int) response_window->tv_sec, (int) response_window->tv_usec);
		} else
#endif
			RDEBUG2("Proxying request to home server %s port %d timeout %d.%06d",
				inet_ntop(request->proxy->dst_ipaddr.af,
					  &request->proxy->dst_ipaddr.ipaddr,
					  buffer, sizeof(buffer)),
				request->proxy->dst_port,
				(int) response_window->tv_sec, (int) response_window->tv_usec);
