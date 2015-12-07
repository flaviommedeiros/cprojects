#ifdef GNUTLS_IA
if (conn->tls_ia)
		res = gnutls_ia_send(conn->session, wpabuf_head(in_data),
				     wpabuf_len(in_data));
	else
#endif /* GNUTLS_IA */
	res = gnutls_record_send(conn->session, wpabuf_head(in_data),
				 wpabuf_len(in_data));
