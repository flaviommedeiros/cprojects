switch (type) {

#ifndef NO_CYASSL_CLIENT
        case hello_request:
            if (ssl->msgsReceived.got_hello_request) {
                CYASSL_MSG("Duplicate HelloRequest received");
                return DUPLICATE_MSG_E;
            }
            ssl->msgsReceived.got_hello_request = 1;

            break;
#endif

#ifndef NO_CYASSL_SERVER
        case client_hello:
            if (ssl->msgsReceived.got_client_hello) {
                CYASSL_MSG("Duplicate ClientHello received");
                return DUPLICATE_MSG_E;
            }
            ssl->msgsReceived.got_client_hello = 1;

            break;
#endif

#ifndef NO_CYASSL_CLIENT
        case server_hello:
            if (ssl->msgsReceived.got_server_hello) {
                CYASSL_MSG("Duplicate ServerHello received");
                return DUPLICATE_MSG_E;
            }
            ssl->msgsReceived.got_server_hello = 1;

            break;
#endif

#ifndef NO_CYASSL_CLIENT
        case hello_verify_request:
            if (ssl->msgsReceived.got_hello_verify_request) {
                CYASSL_MSG("Duplicate HelloVerifyRequest received");
                return DUPLICATE_MSG_E;
            }
            ssl->msgsReceived.got_hello_verify_request = 1;

            break;
#endif

#ifndef NO_CYASSL_CLIENT
        case session_ticket:
            if (ssl->msgsReceived.got_session_ticket) {
                CYASSL_MSG("Duplicate SessionTicket received");
                return DUPLICATE_MSG_E;
            }
            ssl->msgsReceived.got_session_ticket = 1;

            break;
#endif

        case certificate:
            if (ssl->msgsReceived.got_certificate) {
                CYASSL_MSG("Duplicate Certificate received");
                return DUPLICATE_MSG_E;
            }
            ssl->msgsReceived.got_certificate = 1;

#ifndef NO_CYASSL_CLIENT
            if (ssl->options.side == CYASSL_CLIENT_END) {
                if ( ssl->msgsReceived.got_server_hello == 0) {
                    CYASSL_MSG("No ServerHello before Cert");
                    return OUT_OF_ORDER_E;
                }
            }
#endif
#ifndef NO_CYASSL_SERVER
            if (ssl->options.side == CYASSL_SERVER_END) {
                if ( ssl->msgsReceived.got_client_hello == 0) {
                    CYASSL_MSG("No ClientHello before Cert");
                    return OUT_OF_ORDER_E;
                }
            }
#endif
            break;

#ifndef NO_CYASSL_CLIENT
        case server_key_exchange:
            if (ssl->msgsReceived.got_server_key_exchange) {
                CYASSL_MSG("Duplicate ServerKeyExchange received");
                return DUPLICATE_MSG_E;
            }
            ssl->msgsReceived.got_server_key_exchange = 1;

            if ( ssl->msgsReceived.got_server_hello == 0) {
                CYASSL_MSG("No ServerHello before Cert");
                return OUT_OF_ORDER_E;
            }

            break;
#endif

#ifndef NO_CYASSL_CLIENT
        case certificate_request:
            if (ssl->msgsReceived.got_certificate_request) {
                CYASSL_MSG("Duplicate CertificateRequest received");
                return DUPLICATE_MSG_E;
            }
            ssl->msgsReceived.got_certificate_request = 1;

            break;
#endif

#ifndef NO_CYASSL_CLIENT
        case server_hello_done:
            if (ssl->msgsReceived.got_server_hello_done) {
                CYASSL_MSG("Duplicate ServerHelloDone received");
                return DUPLICATE_MSG_E;
            }
            ssl->msgsReceived.got_server_hello_done = 1;

            if (ssl->msgsReceived.got_certificate == 0) {
                if (ssl->specs.kea == psk_kea ||
                    ssl->specs.kea == dhe_psk_kea ||
                    ssl->options.usingAnon_cipher) {
                    CYASSL_MSG("No Cert required");
                } else {
                    CYASSL_MSG("No Certificate before ServerHelloDone");
                    return OUT_OF_ORDER_E;
                }
            }
            if (ssl->msgsReceived.got_server_key_exchange == 0) {
                if (ssl->specs.static_ecdh == 1 ||
                    ssl->specs.kea == rsa_kea ||
                    ssl->specs.kea == ntru_kea) {
                    CYASSL_MSG("No KeyExchange required");
                } else {
                    CYASSL_MSG("No ServerKeyExchange before ServerDone");
                    return OUT_OF_ORDER_E;
                }
            }
            break;
#endif

#ifndef NO_CYASSL_SERVER
        case certificate_verify:
            if (ssl->msgsReceived.got_certificate_verify) {
                CYASSL_MSG("Duplicate CertificateVerify received");
                return DUPLICATE_MSG_E;
            }
            ssl->msgsReceived.got_certificate_verify = 1;

            if ( ssl->msgsReceived.got_certificate == 0) {
                CYASSL_MSG("No Cert before CertVerify");
                return OUT_OF_ORDER_E;
            }
            break;
#endif

#ifndef NO_CYASSL_SERVER
        case client_key_exchange:
            if (ssl->msgsReceived.got_client_key_exchange) {
                CYASSL_MSG("Duplicate ClientKeyExchange received");
                return DUPLICATE_MSG_E;
            }
            ssl->msgsReceived.got_client_key_exchange = 1;

            if (ssl->msgsReceived.got_client_hello == 0) {
                CYASSL_MSG("No ClientHello before ClientKeyExchange");
                return OUT_OF_ORDER_E;
            }
            break;
#endif

        case finished:
            if (ssl->msgsReceived.got_finished) {
                CYASSL_MSG("Duplicate Finished received");
                return DUPLICATE_MSG_E;
            }
            ssl->msgsReceived.got_finished = 1;

            if (ssl->msgsReceived.got_change_cipher == 0) {
                CYASSL_MSG("Finished received before ChangeCipher");
                return NO_CHANGE_CIPHER_E;
            }

            break;

        case change_cipher_hs:
            if (ssl->msgsReceived.got_change_cipher) {
                CYASSL_MSG("Duplicate ChangeCipher received");
                return DUPLICATE_MSG_E;
            }
            ssl->msgsReceived.got_change_cipher = 1;

#ifndef NO_CYASSL_CLIENT
            if (ssl->options.side == CYASSL_CLIENT_END) {
                if (!ssl->options.resuming &&
                                 ssl->msgsReceived.got_server_hello_done == 0) {
                    CYASSL_MSG("No ServerHelloDone before ChangeCipher");
                    return OUT_OF_ORDER_E;
                }
            }
#endif
#ifndef NO_CYASSL_SERVER
            if (ssl->options.side == CYASSL_SERVER_END) {
                if (!ssl->options.resuming &&
                               ssl->msgsReceived.got_client_key_exchange == 0) {
                    CYASSL_MSG("No ClientKeyExchange before ChangeCipher");
                    return OUT_OF_ORDER_E;
                }
            }
#endif

            break;

        default:
            CYASSL_MSG("Unknown message type");
            return SANITY_MSG_E;
    }
