#ifdef HAVE_GNUTLS
if (server->ssl_connected)
            num_read = gnutls_record_recv (server->gnutls_sess, buffer,
                                           sizeof (buffer) - 2);
        else
#endif /* HAVE_GNUTLS */
            num_read = recv (server->sock, buffer, sizeof (buffer) - 2, 0);
