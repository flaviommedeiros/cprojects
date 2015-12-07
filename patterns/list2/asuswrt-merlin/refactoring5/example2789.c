#ifndef NETSNMP_DISABLE_MD5
if (snmp_oid_compare(uptr->authProtocol, uptr->authProtocolLen,
                                 usmHMACMD5AuthProtocol,
                                 sizeof(usmHMACMD5AuthProtocol) /
                                 sizeof(oid)) == 0) {
                if (var_val_len != 0 && var_val_len != 32) {
                    return SNMP_ERR_WRONGLENGTH;
                }
            } else
#endif
                if (snmp_oid_compare
                    (uptr->authProtocol, uptr->authProtocolLen,
                     usmHMACSHA1AuthProtocol,
                     sizeof(usmHMACSHA1AuthProtocol) / sizeof(oid)) == 0) {
                if (var_val_len != 0 && var_val_len != 40) {
                    return SNMP_ERR_WRONGLENGTH;
                }
            }
