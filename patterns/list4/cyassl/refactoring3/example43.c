switch (type) {

    case hello_request:
        CYASSL_MSG("processing hello request");
        ret = DoHelloRequest(ssl, input, inOutIdx, size, totalSz);
        break;

#ifndef NO_CYASSL_CLIENT
    case hello_verify_request:
        CYASSL_MSG("processing hello verify request");
        ret = DoHelloVerifyRequest(ssl, input,inOutIdx, size);
        break;

    case server_hello:
        CYASSL_MSG("processing server hello");
        ret = DoServerHello(ssl, input, inOutIdx, size);
        break;

#ifndef NO_CERTS
    case certificate_request:
        CYASSL_MSG("processing certificate request");
        ret = DoCertificateRequest(ssl, input, inOutIdx, size);
        break;
#endif

    case server_key_exchange:
        CYASSL_MSG("processing server key exchange");
        ret = DoServerKeyExchange(ssl, input, inOutIdx, size);
        break;

#ifdef HAVE_SESSION_TICKET
    case session_ticket:
        CYASSL_MSG("processing session ticket");
        ret = DoSessionTicket(ssl, input, inOutIdx, size);
        break;
#endif /* HAVE_SESSION_TICKET */
#endif

#ifndef NO_CERTS
    case certificate:
        CYASSL_MSG("processing certificate");
        ret =  DoCertificate(ssl, input, inOutIdx, size);
        break;
#endif

    case server_hello_done:
        CYASSL_MSG("processing server hello done");
        #ifdef CYASSL_CALLBACKS
            if (ssl->hsInfoOn)
                AddPacketName("ServerHelloDone", &ssl->handShakeInfo);
            if (ssl->toInfoOn)
                AddLateName("ServerHelloDone", &ssl->timeoutInfo);
        #endif
        ssl->options.serverState = SERVER_HELLODONE_COMPLETE;
        if (ssl->keys.encryptionOn) {
            *inOutIdx += ssl->keys.padSz;
        }
        break;

    case finished:
        CYASSL_MSG("processing finished");
        ret = DoFinished(ssl, input, inOutIdx, size, totalSz, NO_SNIFF);
        break;

#ifndef NO_CYASSL_SERVER
    case client_hello:
        CYASSL_MSG("processing client hello");
        ret = DoClientHello(ssl, input, inOutIdx, size);
        break;

    case client_key_exchange:
        CYASSL_MSG("processing client key exchange");
        ret = DoClientKeyExchange(ssl, input, inOutIdx, size);
        break;

#if !defined(NO_RSA) || defined(HAVE_ECC)
    case certificate_verify:
        CYASSL_MSG("processing certificate verify");
        ret = DoCertificateVerify(ssl, input, inOutIdx, size);
        break;
#endif /* !NO_RSA || HAVE_ECC */

#endif /* !NO_CYASSL_SERVER */

    default:
        CYASSL_MSG("Unknown handshake message type");
        ret = UNKNOWN_HANDSHAKE_TYPE;
        break;
    }
