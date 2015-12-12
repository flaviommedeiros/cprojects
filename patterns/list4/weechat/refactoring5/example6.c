#ifdef HAVE_GNUTLS
if (client->ssl)
        {
            if ((num_read == 0)
                || ((num_read != GNUTLS_E_AGAIN) && (num_read != GNUTLS_E_INTERRUPTED)))
            {
                weechat_printf_tags (NULL, "relay_client",
                                     _("%s%s: reading data on socket for "
                                       "client %s%s%s: error %d %s"),
                                     weechat_prefix ("error"), RELAY_PLUGIN_NAME,
                                     RELAY_COLOR_CHAT_CLIENT,
                                     client->desc,
                                     RELAY_COLOR_CHAT,
                                     num_read,
                                     (num_read == 0) ? _("(connection closed by peer)") :
                                     gnutls_strerror (num_read));
                relay_client_set_status (client, RELAY_STATUS_DISCONNECTED);
            }
        }
        else
#endif /* HAVE_GNUTLS */
        {
            if ((num_read == 0)
                || ((errno != EAGAIN) && (errno != EWOULDBLOCK)))
            {
                weechat_printf_tags (NULL, "relay_client",
                                     _("%s%s: reading data on socket for "
                                       "client %s%s%s: error %d %s"),
                                     weechat_prefix ("error"), RELAY_PLUGIN_NAME,
                                     RELAY_COLOR_CHAT_CLIENT,
                                     client->desc,
                                     RELAY_COLOR_CHAT,
                                     errno,
                                     (num_read == 0) ? _("(connection closed by peer)") :
                                     strerror (errno));
                relay_client_set_status (client, RELAY_STATUS_DISCONNECTED);
            }
        }
