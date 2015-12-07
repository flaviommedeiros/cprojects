#ifndef NETSNMP_NO_WRITE_SUPPORT
if (reqinfo->mode == MODE_SET_RESERVE1)
                table_helper_cleanup(reqinfo, request,
                                     SNMP_ERR_NOTWRITABLE);
            else
#endif /* NETSNMP_NO_WRITE_SUPPORT */
            if (reqinfo->mode == MODE_GET)
                table_helper_cleanup(reqinfo, request,
                                     SNMP_NOSUCHOBJECT);
