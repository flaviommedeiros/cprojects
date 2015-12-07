#ifndef NETSNMP_NO_WRITE_SUPPORT
if (reqinfo->mode != MODE_SET_RESERVE1)
#endif /* !NETSNMP_NO_WRITE_SUPPORT */
                    snmp_set_var_typed_value(requests->requestvb,
                                             cvp->type, access, len);
