#ifdef HAVE_GNUTLS
if (ptr_client->ssl)
                {
                    num_sent = gnutls_record_send (ptr_client->gnutls_sess,
                                                   ptr_client->outqueue->data,
                                                   ptr_client->outqueue->data_size);
                }
                else
#endif /* HAVE_GNUTLS */
                {
                    num_sent = send (ptr_client->sock,
                                     ptr_client->outqueue->data,
                                     ptr_client->outqueue->data_size, 0);
                }
