switch (padding) {
    case RSA_PKCS1_PADDING:
        r = RSA_padding_check_PKCS1_type_2(to, num, buf, j, num);
        break;
# ifndef OPENSSL_NO_SHA
    case RSA_PKCS1_OAEP_PADDING:
        r = RSA_padding_check_PKCS1_OAEP(to, num, buf, j, num, NULL, 0);
        break;
# endif
    case RSA_SSLV23_PADDING:
        r = RSA_padding_check_SSLv23(to, num, buf, j, num);
        break;
    case RSA_NO_PADDING:
        r = RSA_padding_check_none(to, num, buf, j, num);
        break;
    default:
        RSAerr(RSA_F_RSA_EAY_PRIVATE_DECRYPT, RSA_R_UNKNOWN_PADDING_TYPE);
        goto err;
    }
