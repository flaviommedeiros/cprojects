if (connect(s, (struct sockaddr *)sinx,
		    RD_SOCKADDR_INX_LEN(sinx)) == SOCKET_ERROR &&
	    (socket_errno != EINPROGRESS
#ifdef _MSC_VER
		&& socket_errno != WSAEWOULDBLOCK
#endif
		)) {
		rd_rkb_dbg(rkb, BROKER, "CONNECT",
			   "couldn't connect to %s: %s (%i)",
			   rd_sockaddr2str(sinx,
					   RD_SOCKADDR2STR_F_PORT |
					   RD_SOCKADDR2STR_F_FAMILY),
			   socket_strerror(socket_errno), socket_errno);
		rd_snprintf(errstr, errstr_size,
			    "Failed to connect to broker at %s: %s",
			    rd_sockaddr2str(sinx, RD_SOCKADDR2STR_F_NICE),
			    socket_strerror(socket_errno));
		goto err;
	}
