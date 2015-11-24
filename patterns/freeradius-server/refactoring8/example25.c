static const CONF_PARSER module_config[] = {
	/*
	 *	Cache the password by default.
	 */
	{ FR_CONF_OFFSET("use_mppe", PW_TYPE_BOOLEAN, rlm_mschap_t, use_mppe), .dflt = "yes" },
	{ FR_CONF_OFFSET("require_encryption", PW_TYPE_BOOLEAN, rlm_mschap_t, require_encryption), .dflt = "no" },
	{ FR_CONF_OFFSET("require_strong", PW_TYPE_BOOLEAN, rlm_mschap_t, require_strong), .dflt = "no" },
	{ FR_CONF_OFFSET("with_ntdomain_hack", PW_TYPE_BOOLEAN, rlm_mschap_t, with_ntdomain_hack), .dflt = "yes" },
	{ FR_CONF_OFFSET("ntlm_auth", PW_TYPE_STRING | PW_TYPE_XLAT, rlm_mschap_t, ntlm_auth) },
	{ FR_CONF_OFFSET("ntlm_auth_timeout", PW_TYPE_INTEGER, rlm_mschap_t, ntlm_auth_timeout) },
	{ FR_CONF_POINTER("passchange", PW_TYPE_SUBSECTION, NULL), .dflt = (void const *) passchange_config },
	{ FR_CONF_OFFSET("allow_retry", PW_TYPE_BOOLEAN, rlm_mschap_t, allow_retry), .dflt = "yes" },
	{ FR_CONF_OFFSET("retry_msg", PW_TYPE_STRING, rlm_mschap_t, retry_msg) },
	{ FR_CONF_OFFSET("winbind_username", PW_TYPE_TMPL, rlm_mschap_t, wb_username) },
	{ FR_CONF_OFFSET("winbind_domain", PW_TYPE_TMPL, rlm_mschap_t, wb_domain) },
#ifdef __APPLE__
	{ FR_CONF_OFFSET("use_open_directory", PW_TYPE_BOOLEAN, rlm_mschap_t, open_directory), .dflt = "yes" },
#endif
	CONF_PARSER_TERMINATOR
};
