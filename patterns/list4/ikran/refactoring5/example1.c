#ifdef LWS_OPENSSL_SUPPORT
if (wsi->use_ssl)
			n = SSL_write(wsi->ssl, pkt, p - pkt);
		else
	#endif
			n = send(wsi->sock, pkt, p - pkt, 0);
