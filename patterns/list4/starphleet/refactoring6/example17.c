if (n == SSL_R_BAD_CHANGE_CIPHER_SPEC                        /*  103 */
            || n == SSL_R_BLOCK_CIPHER_PAD_IS_WRONG                  /*  129 */
            || n == SSL_R_DIGEST_CHECK_FAILED                        /*  149 */
            || n == SSL_R_ERROR_IN_RECEIVED_CIPHER_LIST              /*  151 */
            || n == SSL_R_EXCESSIVE_MESSAGE_SIZE                     /*  152 */
            || n == SSL_R_LENGTH_MISMATCH                            /*  159 */
            || n == SSL_R_NO_CIPHERS_PASSED                          /*  182 */
            || n == SSL_R_NO_CIPHERS_SPECIFIED                       /*  183 */
            || n == SSL_R_NO_COMPRESSION_SPECIFIED                   /*  187 */
            || n == SSL_R_NO_SHARED_CIPHER                           /*  193 */
            || n == SSL_R_RECORD_LENGTH_MISMATCH                     /*  213 */
#ifdef SSL_R_PARSE_TLSEXT
            || n == SSL_R_PARSE_TLSEXT                               /*  227 */
#endif
            || n == SSL_R_UNEXPECTED_MESSAGE                         /*  244 */
            || n == SSL_R_UNEXPECTED_RECORD                          /*  245 */
            || n == SSL_R_UNKNOWN_ALERT_TYPE                         /*  246 */
            || n == SSL_R_UNKNOWN_PROTOCOL                           /*  252 */
            || n == SSL_R_WRONG_VERSION_NUMBER                       /*  267 */
            || n == SSL_R_DECRYPTION_FAILED_OR_BAD_RECORD_MAC        /*  281 */
#ifdef SSL_R_RENEGOTIATE_EXT_TOO_LONG
            || n == SSL_R_RENEGOTIATE_EXT_TOO_LONG                   /*  335 */
            || n == SSL_R_RENEGOTIATION_ENCODING_ERR                 /*  336 */
            || n == SSL_R_RENEGOTIATION_MISMATCH                     /*  337 */
#endif
#ifdef SSL_R_UNSAFE_LEGACY_RENEGOTIATION_DISABLED
            || n == SSL_R_UNSAFE_LEGACY_RENEGOTIATION_DISABLED       /*  338 */
#endif
#ifdef SSL_R_SCSV_RECEIVED_WHEN_RENEGOTIATING
            || n == SSL_R_SCSV_RECEIVED_WHEN_RENEGOTIATING           /*  345 */
#endif
            || n == 1000 /* SSL_R_SSLV3_ALERT_CLOSE_NOTIFY */
            || n == SSL_R_SSLV3_ALERT_UNEXPECTED_MESSAGE             /* 1010 */
            || n == SSL_R_SSLV3_ALERT_BAD_RECORD_MAC                 /* 1020 */
            || n == SSL_R_TLSV1_ALERT_DECRYPTION_FAILED              /* 1021 */
            || n == SSL_R_TLSV1_ALERT_RECORD_OVERFLOW                /* 1022 */
            || n == SSL_R_SSLV3_ALERT_DECOMPRESSION_FAILURE          /* 1030 */
            || n == SSL_R_SSLV3_ALERT_HANDSHAKE_FAILURE              /* 1040 */
            || n == SSL_R_SSLV3_ALERT_NO_CERTIFICATE                 /* 1041 */
            || n == SSL_R_SSLV3_ALERT_BAD_CERTIFICATE                /* 1042 */
            || n == SSL_R_SSLV3_ALERT_UNSUPPORTED_CERTIFICATE        /* 1043 */
            || n == SSL_R_SSLV3_ALERT_CERTIFICATE_REVOKED            /* 1044 */
            || n == SSL_R_SSLV3_ALERT_CERTIFICATE_EXPIRED            /* 1045 */
            || n == SSL_R_SSLV3_ALERT_CERTIFICATE_UNKNOWN            /* 1046 */
            || n == SSL_R_SSLV3_ALERT_ILLEGAL_PARAMETER              /* 1047 */
            || n == SSL_R_TLSV1_ALERT_UNKNOWN_CA                     /* 1048 */
            || n == SSL_R_TLSV1_ALERT_ACCESS_DENIED                  /* 1049 */
            || n == SSL_R_TLSV1_ALERT_DECODE_ERROR                   /* 1050 */
            || n == SSL_R_TLSV1_ALERT_DECRYPT_ERROR                  /* 1051 */
            || n == SSL_R_TLSV1_ALERT_EXPORT_RESTRICTION             /* 1060 */
            || n == SSL_R_TLSV1_ALERT_PROTOCOL_VERSION               /* 1070 */
            || n == SSL_R_TLSV1_ALERT_INSUFFICIENT_SECURITY          /* 1071 */
            || n == SSL_R_TLSV1_ALERT_INTERNAL_ERROR                 /* 1080 */
            || n == SSL_R_TLSV1_ALERT_USER_CANCELLED                 /* 1090 */
            || n == SSL_R_TLSV1_ALERT_NO_RENEGOTIATION)              /* 1100 */
        {
            switch (c->log_error) {

            case NGX_ERROR_IGNORE_ECONNRESET:
            case NGX_ERROR_INFO:
                level = NGX_LOG_INFO;
                break;

            case NGX_ERROR_ERR:
                level = NGX_LOG_ERR;
                break;

            default:
                break;
            }
        }
