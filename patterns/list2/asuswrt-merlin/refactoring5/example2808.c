#ifndef NETSNMP_DISABLE_MD5
if (!strcasecmp(optarg, "MD5")) {
            session->securityAuthProto = usmHMACMD5AuthProtocol;
            session->securityAuthProtoLen = USM_AUTH_PROTO_MD5_LEN;
        } else
#endif
            if (!strcasecmp(optarg, "SHA")) {
            session->securityAuthProto = usmHMACSHA1AuthProtocol;
            session->securityAuthProtoLen = USM_AUTH_PROTO_SHA_LEN;
        } else {
            fprintf(stderr,
                    "Invalid authentication protocol specified after -3a flag: %s\n",
                    optarg);
            return (-1);
        }
