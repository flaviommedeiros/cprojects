static const CONF_PARSER module_config[] = {
	{ FR_CONF_OFFSET("server", PW_TYPE_STRING, rlm_ldap_t, config_server) },	/* Do not set to required */
	{ FR_CONF_OFFSET("port", PW_TYPE_SHORT, rlm_ldap_t, port) },

	{ FR_CONF_OFFSET("identity", PW_TYPE_STRING, rlm_ldap_t, admin_identity) },
	{ FR_CONF_OFFSET("password", PW_TYPE_STRING | PW_TYPE_SECRET, rlm_ldap_t, admin_password) },

	{ FR_CONF_OFFSET("sasl", PW_TYPE_SUBSECTION, rlm_ldap_t, admin_sasl), .dflt = (void const *) sasl_mech_static },

	{ FR_CONF_OFFSET("valuepair_attribute", PW_TYPE_STRING, rlm_ldap_t, valuepair_attr) },

#ifdef WITH_EDIR
	/* support for eDirectory Universal Password */
	{ FR_CONF_OFFSET("edir", PW_TYPE_BOOLEAN, rlm_ldap_t, edir) }, /* NULL defaults to "no" */

	/*
	 *	Attempt to bind with the cleartext password we got from eDirectory
	 *	Universal password for additional authorization checks.
	 */
	{ FR_CONF_OFFSET("edir_autz", PW_TYPE_BOOLEAN, rlm_ldap_t, edir_autz) }, /* NULL defaults to "no" */
#endif

	{ FR_CONF_OFFSET("read_clients", PW_TYPE_BOOLEAN, rlm_ldap_t, do_clients) }, /* NULL defaults to "no" */

	{ FR_CONF_POINTER("user", PW_TYPE_SUBSECTION, NULL), .dflt = (void const *) user_config },

	{ FR_CONF_POINTER("group", PW_TYPE_SUBSECTION, NULL), .dflt = (void const *) group_config },

	{ FR_CONF_POINTER("client", PW_TYPE_SUBSECTION, NULL), .dflt = (void const *) client_config },

	{ FR_CONF_POINTER("profile", PW_TYPE_SUBSECTION, NULL), .dflt = (void const *) profile_config },

	{ FR_CONF_POINTER("options", PW_TYPE_SUBSECTION, NULL), .dflt = (void const *) option_config },

	{ FR_CONF_POINTER("tls", PW_TYPE_SUBSECTION, NULL), .dflt = (void const *) tls_config },
	CONF_PARSER_TERMINATOR
};
