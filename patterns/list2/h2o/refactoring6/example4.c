if( e == EAI_FAMILY || e == EAI_NONAME
#ifdef EAI_ADDRFAMILY
        || e == EAI_ADDRFAMILY
#endif
#ifdef EAI_NODATA
        || e == EAI_NODATA
#endif
        ) {
        hint.ai_family = AF_INET6;
        // intentionally drop AI_ADDRCONFIG to support IPv6 link-local address.
        // see https://github.com/cybozu/yrmcds/issues/40
        hint.ai_flags = AI_NUMERICSERV|AI_V4MAPPED;
        e = getaddrinfo(node, sport, &hint, &res);
    }
