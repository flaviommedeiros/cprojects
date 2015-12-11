#ifndef OPENSSL_NO_SRP
if ((i == 2) && (type & SSL_kSRP))
                n += 1 + nr[i];
            else
#endif
                n += 2 + nr[i];
