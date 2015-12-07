# ifdef SO_REUSEADDR
if ((bind_mode == BIO_BIND_REUSEADDR_IF_UNUSED) &&
#  ifdef OPENSSL_SYS_WINDOWS
            /*
             * Some versions of Windows define EADDRINUSE to a dummy value.
             */
            (err_num == WSAEADDRINUSE))
#  else
            (err_num == EADDRINUSE)
