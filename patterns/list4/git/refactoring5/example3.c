#ifndef NO_OPENSSL
if (sock->ssl)
		n = SSL_write(sock->ssl, buf, len);
	else
#endif
		n = write_in_full(sock->fd[1], buf, len);
