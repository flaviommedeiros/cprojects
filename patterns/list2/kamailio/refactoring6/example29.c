if (
#ifdef USE_SCTP
			(proto!=PROTO_SCTP || sctp_o2o) &&
#endif /* USE_SCTP */
			(connect(sock, (struct sockaddr*) &addr,
					sizeof(struct sockaddr))!=0)){
			fprintf(stderr, "ERROR: connect: %s\n", strerror(errno));
			goto error;
		}
