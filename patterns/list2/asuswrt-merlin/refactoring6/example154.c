if (snmp_oid_compare
                ((oid *) var_val, var_val_len / sizeof(oid),
                 usmNoAuthProtocol,
                 sizeof(usmNoAuthProtocol) / sizeof(oid)) == 0
#ifndef NETSNMP_DISABLE_MD5
                || snmp_oid_compare((oid *) var_val,
                                    var_val_len / sizeof(oid),
                                    usmHMACMD5AuthProtocol,
                                    sizeof(usmHMACMD5AuthProtocol) /
                                    sizeof(oid)) == 0
#endif
                || snmp_oid_compare((oid *) var_val,
                                    var_val_len / sizeof(oid),
                                    usmHMACSHA1AuthProtocol,
                                    sizeof(usmHMACSHA1AuthProtocol) /
                                    sizeof(oid)) == 0) {
                if (uptr->cloneFrom != NULL) {
                    optr = uptr->authProtocol;
                    olen = uptr->authProtocolLen;
                    resetOnFail = 1;
                    uptr->authProtocol =
                        snmp_duplicate_objid((oid *) var_val,
                                             var_val_len / sizeof(oid));
                    if (uptr->authProtocol == NULL) {
                        return SNMP_ERR_RESOURCEUNAVAILABLE;
                    }
                    uptr->authProtocolLen = var_val_len / sizeof(oid);
                }
            } else {
                /*
                 * Unknown authentication protocol.  
                 */
                return SNMP_ERR_WRONGVALUE;
            }
