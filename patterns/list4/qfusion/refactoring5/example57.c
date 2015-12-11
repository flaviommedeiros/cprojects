#ifndef OPENSSL_NO_TLS1
if (tls1)
        meth = TLSv1_method();
    else
#endif
        meth = SSLv23_method();
