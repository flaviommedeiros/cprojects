#ifdef HAVE_GNUTLS
if (server->ssl_connected)
        rc = gnutls_record_send (server->gnutls_sess, buffer, size_buf);
    else
#endif /* HAVE_GNUTLS */
        rc = send (server->sock, buffer, size_buf, 0);
