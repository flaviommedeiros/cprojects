#ifdef HAVE_LDAP
if (ldap_uuid_string)
        uuidmask = ldap_uuid_string;
    else
#endif
        uuidmask = "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx";
