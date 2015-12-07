#ifndef NETSNMP_DISABLE_MD5
if (strncmp(cp, "MD5", 3) == 0) {
        memcpy(newuser->authProtocol, usmHMACMD5AuthProtocol,
               sizeof(usmHMACMD5AuthProtocol));
    } else
#endif
        if (strncmp(cp, "SHA", 3) == 0) {
        memcpy(newuser->authProtocol, usmHMACSHA1AuthProtocol,
               sizeof(usmHMACSHA1AuthProtocol));
    } else {
        config_perror("Unknown authentication protocol");
        usm_free_user(newuser);
        return;
    }
