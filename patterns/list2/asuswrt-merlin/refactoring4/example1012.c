#ifndef NETSNMP_DISABLE_MIB_LOADING
if ((ret =
         _add_strings_to_oid(root, name, output, out_len,
                             max_out_len)) <= 0)
#else
    if ((ret =
         _add_strings_to_oid(NULL, name, output, out_len,
                             max_out_len)) <= 0)
#endif /* NETSNMP_DISABLE_MIB_LOADING */
    {
        if (ret == 0)
            ret = SNMPERR_UNKNOWN_OBJID;
        SET_SNMP_ERROR(ret);
        SNMP_FREE(name);
        return 0;
    }
