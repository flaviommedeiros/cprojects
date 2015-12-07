#ifdef HAVE_ACL_GET_PERM_NP
if (acl_get_perm_np(permset, ACL_WRITE))
#else
    if (acl_get_perm(permset, ACL_WRITE))
#endif
        rights |= AR_UWRITE;
