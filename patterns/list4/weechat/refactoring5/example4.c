#ifdef HAVE_GNUTLS
if (server->ssl_connected)
            {
                if ((num_read == 0)
                    || ((num_read != GNUTLS_E_AGAIN)
                        && (num_read != GNUTLS_E_INTERRUPTED)))
                {
                    weechat_printf (
                        server->buffer,
                        _("%s%s: reading data on socket: error %d %s"),
                        weechat_prefix ("error"), IRC_PLUGIN_NAME,
                        num_read,
                        (num_read == 0) ? _("(connection closed by peer)") :
                        gnutls_strerror (num_read));
                    weechat_printf (
                        server->buffer,
                        _("%s%s: disconnecting from server..."),
                        weechat_prefix ("network"), IRC_PLUGIN_NAME);
                    irc_server_disconnect (server, !server->is_connected, 1);
                }
            }
            else
#endif /* HAVE_GNUTLS */
            {
                if ((num_read == 0)
                    || ((errno != EAGAIN) && (errno != EWOULDBLOCK)))
                {
                    weechat_printf (
                        server->buffer,
                        _("%s%s: reading data on socket: error %d %s"),
                        weechat_prefix ("error"), IRC_PLUGIN_NAME,
                        errno,
                        (num_read == 0) ? _("(connection closed by peer)") :
                        strerror (errno));
                    weechat_printf (
                        server->buffer,
                        _("%s%s: disconnecting from server..."),
                        weechat_prefix ("network"), IRC_PLUGIN_NAME);
                    irc_server_disconnect (server, !server->is_connected, 1);
                }
            }
