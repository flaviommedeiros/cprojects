#ifdef USE_SCTP
if (proto==PROTO_SCTP && !sctp_o2o){
				if (sctp_sendmsg(sock, buf, n,  (struct sockaddr*) &addr,
									sizeof(struct sockaddr), 0, SCTP_UNORDERED,
									0, 0, 0)==-1){
					fprintf(stderr, "Error(%d): send: %s\n", err,
							strerror(errno));
					err++;;
				}
			}else
#endif /* USE_SCTP */
			{
				if (send(sock, buf, n, 0)==-1) {
					fprintf(stderr, "Error(%d): send: %s\n", err,
							strerror(errno));
					err++;;
				}
			}
