FR_NAME_NUMBER const ldap_scope[] = {
	{ "sub",	LDAP_SCOPE_SUB	},
	{ "one",	LDAP_SCOPE_ONE	},
	{ "base",	LDAP_SCOPE_BASE },
#ifdef LDAP_SCOPE_CHILDREN
	{ "children",	LDAP_SCOPE_CHILDREN },
#endif
	{  NULL , -1 }
};
