switch (type) {

    case hello_request:
        WOLFSSL_MSG("processing hello request");
        ret = DoHelloRequest(ssl, input, inOutIdx, size, totalSz);
        break;

#ifndef NO_WOLFSSL_CLIENT
    case hello_verify_request:
        WOLFSSL_MSG("processing hello verify request");
        ret = DoHelloVerifyRequest(ssl, input,inOutIdx, size);
        break;

    case server_hello:
        WOLFSSL_MSG("processing server hello");
        ret = DoServerHello(ssl, input, inOutIdx, size);
        break;

#ifndef NO_CERTS
    case certificate_request:
        WOLFSSL_MSG("processing certificate request");
        ret = DoCertificateRequest(ssl, input, inOutIdx, size);
        break;
#endif

    case server_key_exchange:
        WOLFSSL_MSG("processing server key exchange");
        ret = DoServerKeyExchange(ssl, input, inOutIdx, size);
        break;

#ifdef HAVE_SESSION_TICKET
    case session_ticket:
        WOLFSSL_MSG("processing session ticket");
        ret = DoSessionTicket(ssl, input, inOutIdx, size);
        break;
#endif /* HAVE_SESSION_TICKET */
#endif

#ifndef NO_CERTS
    case certificate:
        WOLFSSL_MSG("processing certificate");
        ret = DoCertificate(ssl, input, inOutIdx, size);
        break;

    case certificate_status:
        WOLFSSL_MSG("processing certificate status");
        ret = DoCertificateStatus(ssl, input, inOutIdx, size);
        break;
#endif

    case server_hello_done:
        WOLFSSL_MSG("processing server hello done");
        #ifdef WOLFSSL_CALLBACKS
            if (ssl->hsInfoOn)
                AddPacketName("ServerHelloDone", &ssl->handShakeInfo);
            if (ssl->toInfoOn)
                AddLateName("ServerHelloDone", &ssl->timeoutInfo);
        #endif
        ssl->options.serverState = SERVER_HELLODONE_COMPLETE;
        if (IsEncryptionOn(ssl, 0)) {
            *inOutIdx += ssl->keys.padSz;
        }
        if (ssl->options.resuming) {
            WOLFSSL_MSG("Not resuming as thought");
            ssl->options.resuming = 0;
        }
        break;

    case finished:
        WOLFSSL_MSG("processing finished");
        ret = DoFinished(ssl, input, inOutIdx, size, totalSz, NO_SNIFF);
        break;

#ifndef NO_WOLFSSL_SERVER
    case client_hello:
        WOLFSSL_MSG("processing client hello");
        ret = DoClientHello(ssl, input, inOutIdx, size);
        break;

    case client_key_exchange:
        WOLFSSL_MSG("processing client key exchange");
        ret = DoClientKeyExchange(ssl, input, inOutIdx, size);
        break;

#if !defined(NO_RSA) || defined(HAVE_ECC)
    case certificate_verify:
        WOLFSSL_MSG("processing certificate verify");
        ret = DoCertificateVerify(ssl, input, inOutIdx, size);
        break;
#endif /* !NO_RSA || HAVE_ECC */

#endif /* !NO_WOLFSSL_SERVER */

    default:
        WOLFSSL_MSG("Unknown handshake message type");
        ret = UNKNOWN_HANDSHAKE_TYPE;
        break;
    }
