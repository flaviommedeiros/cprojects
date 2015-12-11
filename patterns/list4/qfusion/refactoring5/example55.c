#ifndef OPENSSL_NO_SSL2
if (ssl2)
        meth = SSLv2_method();
    else
#endif
#ifndef OPENSSL_NO_SSL3
    if (ssl3)
        meth = SSLv3_method();
    else
#endif
#ifndef OPENSSL_NO_TLS1
    if (tls1)
        meth = TLSv1_method();
    else
#endif
        meth = SSLv23_method();
