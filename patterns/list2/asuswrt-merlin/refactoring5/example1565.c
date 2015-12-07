#ifdef GNUTLS_IA
if (conn->tls_ia)
		res = gnutls_ia_send(conn->session, (char *) in_data, in_len);
	else
#endif /* GNUTLS_IA */
	res = gnutls_record_send(conn->session, in_data, in_len);
