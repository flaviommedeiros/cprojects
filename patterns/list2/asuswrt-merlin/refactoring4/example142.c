#ifdef HAVE_ACL_GET_PERM_NP
if (acl_get_perm_np(permset, ACL_EXECUTE))
#else
    if (acl_get_perm(permset, ACL_EXECUTE))
#endif
        rights |= AR_USEARCH;
