#ifndef WIN32
if ((r = ldap_start_tls_s(*ldap, NULL, NULL)) != LDAP_SUCCESS)
#else
		static __ldap_start_tls_sA _ldap_start_tls_sA = NULL;
