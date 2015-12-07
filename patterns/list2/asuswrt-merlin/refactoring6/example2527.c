if (*type != ASN_COUNTER64
#ifdef NETSNMP_WITH_OPAQUE_SPECIAL_TYPES
            && *type != ASN_OPAQUE_COUNTER64 && *type != ASN_OPAQUE_U64
#endif
            ) {
        _asn_type_err(errpre, *type);
        return NULL;
    }
