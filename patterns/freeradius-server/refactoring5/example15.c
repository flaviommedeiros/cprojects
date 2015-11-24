#ifdef WITH_TCP
if (pl->sockets[start].proto == IPPROTO_TCP) {
			packet = fr_tcp_recv(pl->sockets[start].sockfd, 0);
		} else
#endif
		packet = rad_recv(NULL, pl->sockets[start].sockfd, 0);
