if ((udp_listen==0)
#ifdef USE_TCP
			&& (tcp_listen==0)
#ifdef USE_TLS
			&& (tls_listen==0)
#endif
#endif
#ifdef USE_SCTP
			&& (sctp_listen==0)
#endif
		){
		LM_ERR("no listening sockets\n");
		goto error;
	}
