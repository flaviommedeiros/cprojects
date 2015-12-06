#ifdef CONFIG_SSL_ENABLE_CLIENT
if (ssl_func_type == SSLv23_client_method ||
        ssl_func_type == SSLv3_client_method ||
        ssl_func_type == TLSv1_client_method)
    {
        SET_SSL_FLAG(SSL_IS_CLIENT);
    }
    else
#endif
    {
        ssl->next_state = HS_CLIENT_HELLO;
    }
