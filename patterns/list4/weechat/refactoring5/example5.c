#ifdef HAVE_GNUTLS
if (client->ssl)
        num_read = gnutls_record_recv (client->gnutls_sess, buffer,
                                       sizeof (buffer) - 1);
    else
#endif /* HAVE_GNUTLS */
        num_read = recv (client->sock, buffer, sizeof (buffer) - 1, 0);
