if (
#ifndef OPENSSL_NO_STDIO
	    SSL_CTX_use_PrivateKey_file(ssl_ctx, private_key,
					SSL_FILETYPE_ASN1) != 1 &&
	    SSL_CTX_use_PrivateKey_file(ssl_ctx, private_key,
					SSL_FILETYPE_PEM) != 1 &&
#endif /* OPENSSL_NO_STDIO */
	    tls_read_pkcs12(ssl_ctx, NULL, private_key, passwd)) {
		tls_show_errors(MSG_INFO, __func__,
				"Failed to load private key");
		os_free(passwd);
		ERR_clear_error();
		return -1;
	}
