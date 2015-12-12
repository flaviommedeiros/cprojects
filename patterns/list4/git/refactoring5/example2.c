#ifndef NO_OPENSSL
if (sock->ssl)
		n = SSL_read(sock->ssl, buf, len);
	else
#endif
		n = xread(sock->fd[0], buf, len);
