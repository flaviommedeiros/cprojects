#ifdef HAVE_GNUTLS
if (client->ssl)
            {
                if ((num_sent == GNUTLS_E_AGAIN)
                    || (num_sent == GNUTLS_E_INTERRUPTED))
                {
                    /* add message to queue (will be sent later) */
                    relay_client_outqueue_add (client, ptr_data, data_size,
                                               raw_flags, raw_msg, raw_size);
                }
                else
                {
                    weechat_printf_tags (NULL, "relay_client",
                                         _("%s%s: sending data to client %s%s%s: "
                                           "error %d %s"),
                                         weechat_prefix ("error"),
                                         RELAY_PLUGIN_NAME,
                                         RELAY_COLOR_CHAT_CLIENT,
                                         client->desc,
                                         RELAY_COLOR_CHAT,
                                         num_sent,
                                         gnutls_strerror (num_sent));
                    relay_client_set_status (client, RELAY_STATUS_DISCONNECTED);
                }
            }
            else
#endif /* HAVE_GNUTLS */
            {
                if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
                {
                    /* add message to queue (will be sent later) */
                    relay_client_outqueue_add (client, ptr_data, data_size,
                                               raw_flags, raw_msg, raw_size);
                }
                else
                {
                    weechat_printf_tags (NULL, "relay_client",
                                         _("%s%s: sending data to client %s%s%s: "
                                           "error %d %s"),
                                         weechat_prefix ("error"),
                                         RELAY_PLUGIN_NAME,
                                         RELAY_COLOR_CHAT_CLIENT,
                                         client->desc,
                                         RELAY_COLOR_CHAT,
                                         errno,
                                         strerror (errno));
                    relay_client_set_status (client, RELAY_STATUS_DISCONNECTED);
                }
            }
