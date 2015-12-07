#ifndef NETSNMP_NO_WRITE_SUPPORT
if(MODE_IS_SET(agtreq_info->mode))
                    netsnmp_set_request_error(agtreq_info, current,
                                              SNMP_ERR_NOTWRITABLE);
                else
#endif /* NETSNMP_NO_WRITE_SUPPORT */
                    netsnmp_set_request_error(agtreq_info, current,
                                              SNMP_NOSUCHINSTANCE);
