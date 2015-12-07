#ifndef OPENSSL_NO_SSL_TRACE
if (s_msg == 2)
            SSL_set_msg_callback(con, SSL_trace);
        else
#endif
            SSL_set_msg_callback(con, msg_cb);
