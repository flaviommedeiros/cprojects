#ifdef NETSNMP_WITH_OPAQUE_SPECIAL_TYPES
if ((vp->type == ASN_OPAQUE_FLOAT) || (vp->type == ASN_OPAQUE_DOUBLE)
        || (vp->type == ASN_OPAQUE_I64) || (vp->type == ASN_OPAQUE_U64)
        || (vp->type == ASN_OPAQUE_COUNTER64)) {
        if (!agentx_realloc_build_short
            (buf, buf_len, out_len, allow_realloc,
             (unsigned short) ASN_OPAQUE, network_order)) {
            DEBUGINDENTLESS();
            DEBUGINDENTLESS();
            return 0;
        }
    } else
#endif
    if (vp->type == ASN_PRIV_INCL_RANGE || vp->type == ASN_PRIV_EXCL_RANGE) {
        if (!agentx_realloc_build_short
            (buf, buf_len, out_len, allow_realloc,
             (unsigned short) ASN_OBJECT_ID, network_order)) {
            DEBUGINDENTLESS();
            DEBUGINDENTLESS();
            return 0;
        }
    } else {
        if (!agentx_realloc_build_short
            (buf, buf_len, out_len, allow_realloc,
             (unsigned short) vp->type, network_order)) {
            DEBUGINDENTLESS();
            DEBUGINDENTLESS();
            return 0;
        }
    }
