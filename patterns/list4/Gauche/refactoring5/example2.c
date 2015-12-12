#ifdef CONFIG_SSL_ENABLE_CLIENT
if (IS_SET_SSL_FLAG(SSL_IS_CLIENT))
    {
        ret = do_client_connect(ssl);
    }
    else
#endif
    {
        send_packet(ssl, PT_HANDSHAKE_PROTOCOL, 
                g_hello_request, sizeof(g_hello_request));
        SET_SSL_FLAG(SSL_NEED_RECORD);
    }
