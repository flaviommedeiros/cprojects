switch (padding) {      /* check padding in software */
#   ifndef OPENSSL_NO_SHA
        case RSA_PKCS1_OAEP_PADDING:
            ret =
                RSA_padding_check_PKCS1_OAEP(to, tlen, (unsigned char *)buf,
                                             tlen, tlen, NULL, 0);
            break;
#   endif
        case RSA_SSLV23_PADDING:
            ret =
                RSA_padding_check_SSLv23(to, tlen, (unsigned char *)buf, flen,
                                         tlen);
            break;
        case RSA_NO_PADDING:
            ret =
                RSA_padding_check_none(to, tlen, (unsigned char *)buf, flen,
                                       tlen);
            break;
        default:
            SUREWAREerr(SUREWARE_F_SUREWAREHK_RSA_PRIV_DEC,
                        SUREWARE_R_UNKNOWN_PADDING_TYPE);
            goto err;
        }
