if ((var->type != ASN_OPAQUE
#ifdef NETSNMP_WITH_OPAQUE_SPECIAL_TYPES
        && var->type != ASN_OPAQUE_COUNTER64
        && var->type != ASN_OPAQUE_U64
        && var->type != ASN_OPAQUE_I64
        && var->type != ASN_OPAQUE_FLOAT && var->type != ASN_OPAQUE_DOUBLE
#endif                          /* NETSNMP_WITH_OPAQUE_SPECIAL_TYPES */
        ) && (!netsnmp_ds_get_boolean(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_QUICKE_PRINT))) {
        if (snmp_cstrcat(buf, buf_len, out_len, allow_realloc, 
                         "Wrong Type (should be Opaque): ")) {
            return sprint_realloc_by_type(buf, buf_len, out_len,
                                          allow_realloc, var, NULL, NULL,
                                          NULL);
        } else {
            return 0;
        }
    }
