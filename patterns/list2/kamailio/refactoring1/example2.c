if (proto==PROTO_TCP){
			t=1;
			if (setsockopt(sock, IPPROTO_TCP , TCP_NODELAY, &t, sizeof(t))<0){
				fprintf(stderr, "ERROR: could not disable Nagle: %s\n",
								strerror(errno));
			}
			if (tcp_rst){
				t_linger.l_onoff=1;
				t_linger.l_linger=0;
				if (setsockopt(sock, SOL_SOCKET, SO_LINGER, &t_linger,
									sizeof(t_linger))<0){
					fprintf(stderr, "ERROR: could not set SO_LINGER: %s\n",
									strerror(errno));
				}
			}
		}
#ifdef USE_SCTP
		else if (proto==PROTO_SCTP){
			t=1;
			if (setsockopt(sock, IPPROTO_SCTP, SCTP_NODELAY, &t, sizeof(t))<0){
				fprintf(stderr, "ERROR: could not disable Nagle: %s\n",
								strerror(errno));
			}
		}
#endif
