# ifndef OPENSSL_NO_DES
if (usecrypt)
        hash = DES_crypt(passwd, *salt_p);
