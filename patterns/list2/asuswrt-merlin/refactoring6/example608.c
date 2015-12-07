if (snmp_oid_compare
                    ((oid *) var_val, var_val_len / sizeof(oid),
                     usmNoPrivProtocol,
                     sizeof(usmNoPrivProtocol) / sizeof(oid)) != 0
#ifndef NETSNMP_DISABLE_DES
                 && snmp_oid_compare
                    ((oid *) var_val, var_val_len / sizeof(oid),
                     usmDESPrivProtocol,
                     sizeof(usmDESPrivProtocol) / sizeof(oid)) != 0
#endif
                 && snmp_oid_compare
                    ((oid *) var_val, var_val_len / sizeof(oid),
                     usmAESPrivProtocol,
                     sizeof(usmAESPrivProtocol) / sizeof(oid)) != 0) {
                    return SNMP_ERR_WRONGVALUE;
                }
