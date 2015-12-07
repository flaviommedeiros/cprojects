#ifndef OPENSSL_NO_SSL_TRACE
if (c_msg == 2)
            SSL_set_msg_callback(con, SSL_trace);
        else
#endif
            SSL_set_msg_callback(con, msg_cb);
