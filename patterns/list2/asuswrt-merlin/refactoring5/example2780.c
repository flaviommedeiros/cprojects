#ifndef NETSNMP_DISABLE_MD5
if (!strcmp(transform_type_input, "md5")) {
        transform_type = usmHMACMD5AuthProtocol;

    } else
#endif
        if (!strcmp(transform_type_input, "sha1")) {
        transform_type = usmHMACSHA1AuthProtocol;

    } else {
        fprintf(stderr,
                "Unrecognized hash transform: \"%s\".\n",
                transform_type_input);
        usage_synopsis(stderr);
        QUITFUN(SNMPERR_GENERR, main_quit);
    }
