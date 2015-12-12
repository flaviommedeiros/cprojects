#ifdef HAVE_GNUTLS
if (client->ssl)
            num_sent = gnutls_record_send (client->gnutls_sess, ptr_data, data_size);
        else
#endif /* HAVE_GNUTLS */
            num_sent = send (client->sock, ptr_data, data_size, 0);
