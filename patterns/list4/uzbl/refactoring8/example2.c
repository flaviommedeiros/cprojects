static const UzblSecurityField
    fields[] = {
        SECURITY_FIELD (local,            LOCAL),
        SECURITY_FIELD (no_access,        NO_ACCESS_TO_OTHER_SCHEME),
        SECURITY_FIELD (display_isolated, DISPLAY_ISOLATED),
        SECURITY_FIELD (secure,           SECURE),
        SECURITY_FIELD (cors_enabled,     CORS_ENABLED),
        SECURITY_FIELD (empty_document,   EMPTY_DOCUMENT),
#ifdef USE_WEBKIT2
        { NULL, NULL, NULL }
#else
        { NULL, 0 }
#endif
    };
