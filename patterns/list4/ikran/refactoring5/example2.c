#ifdef LWS_OPENSSL_SUPPORT
if (wsi->use_ssl)
			len = SSL_read(wsi->ssl, pkt, sizeof pkt);
		else
	#endif
			len = recv(wsi->sock, pkt, sizeof pkt, 0);
