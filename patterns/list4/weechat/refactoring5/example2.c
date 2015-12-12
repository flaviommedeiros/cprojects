#ifdef HAVE_GNUTLS
if (server->ssl_connected)
        {
            weechat_printf (
                server->buffer,
                _("%s%s: sending data to server: error %d %s"),
                weechat_prefix ("error"), IRC_PLUGIN_NAME,
                rc, gnutls_strerror (rc));
        }
        else
#endif /* HAVE_GNUTLS */
        {
            weechat_printf (
                server->buffer,
                _("%s%s: sending data to server: error %d %s"),
                weechat_prefix ("error"), IRC_PLUGIN_NAME,
                errno, strerror (errno));
        }
