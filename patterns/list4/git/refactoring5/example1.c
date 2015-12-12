#ifndef NO_OPENSSL
if (sock->ssl) {
		int sslerr = SSL_get_error(sock->ssl, ret);
		switch (sslerr) {
		case SSL_ERROR_NONE:
			break;
		case SSL_ERROR_SYSCALL:
			perror("SSL_connect");
			break;
		default:
			ssl_socket_perror("SSL_connect");
			break;
		}
	} else
#endif
	{
		if (ret < 0)
			perror(func);
		else
			fprintf(stderr, "%s: unexpected EOF\n", func);
	}
