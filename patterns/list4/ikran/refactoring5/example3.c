#ifdef LWS_OPENSSL_SUPPORT
if (wsi->ssl)
			eff_buf.token_len = SSL_read(wsi->ssl, buf, sizeof buf);
		else
#endif
			eff_buf.token_len =
					   recv(pollfd->fd, buf, sizeof buf, 0);
