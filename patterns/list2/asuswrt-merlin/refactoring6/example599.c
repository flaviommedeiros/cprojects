if (!table_info
#ifndef NETSNMP_NO_WRITE_SUPPORT
                || !MODE_IS_SET(reqinfo->mode)
#endif /* !NETSNMP_NO_WRITE_SUPPORT */
                ) {
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHINSTANCE);
                continue;
            }
