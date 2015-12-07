#ifndef NETSNMP_DISABLE_MD5
if (strcasecmp(cptr, "MD5") == 0)
        defaultAuthType = usmHMACMD5AuthProtocol;
    else
#endif
        if (strcasecmp(cptr, "SHA") == 0)
        defaultAuthType = usmHMACSHA1AuthProtocol;
    else
        config_perror("Unknown authentication type");
