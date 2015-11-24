static const CONF_PARSER module_config[] = {
	{ FR_CONF_OFFSET("filename", PW_TYPE_FILE_INPUT, rlm_files_t, filename) },
	{ FR_CONF_OFFSET("usersfile", PW_TYPE_FILE_INPUT, rlm_files_t, usersfile) },
	{ FR_CONF_OFFSET("acctusersfile", PW_TYPE_FILE_INPUT, rlm_files_t, acctusersfile) },
#ifdef WITH_PROXY
	{ FR_CONF_OFFSET("preproxy_usersfile", PW_TYPE_FILE_INPUT, rlm_files_t, preproxy_usersfile) },
	{ FR_CONF_OFFSET("postproxy_usersfile", PW_TYPE_FILE_INPUT, rlm_files_t, postproxy_usersfile) },
#endif
	{ FR_CONF_OFFSET("auth_usersfile", PW_TYPE_FILE_INPUT, rlm_files_t, auth_usersfile) },
	{ FR_CONF_OFFSET("postauth_usersfile", PW_TYPE_FILE_INPUT, rlm_files_t, postauth_usersfile) },
	{ FR_CONF_OFFSET("compat", PW_TYPE_STRING | PW_TYPE_DEPRECATED, rlm_files_t, compat_mode) },
	{ FR_CONF_OFFSET("key", PW_TYPE_STRING | PW_TYPE_XLAT, rlm_files_t, key) },
	CONF_PARSER_TERMINATOR
};
