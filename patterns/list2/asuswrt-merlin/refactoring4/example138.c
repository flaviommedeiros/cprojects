#ifdef HAVE_ACL_GET_PERM_NP
if (acl_get_perm_np(permset, ACL_READ))
#else
    if (acl_get_perm(permset, ACL_READ))
#endif
        rights = DARWIN_ACE_READ_DATA
            | DARWIN_ACE_READ_EXTATTRIBUTES
            | DARWIN_ACE_READ_ATTRIBUTES
            | DARWIN_ACE_READ_SECURITY;
