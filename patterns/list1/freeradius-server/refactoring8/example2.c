static const CONF_PARSER security_config[] = {
	{ FR_CONF_POINTER("max_attributes", PW_TYPE_INTEGER, &fr_max_attributes), .dflt = STRINGIFY(0) },
	{ FR_CONF_POINTER("reject_delay", PW_TYPE_TIMEVAL, &main_config.reject_delay), .dflt = STRINGIFY(0) },
	{ FR_CONF_POINTER("status_server", PW_TYPE_BOOLEAN, &main_config.status_server), .dflt = "no" },
#ifdef ENABLE_OPENSSL_VERSION_CHECK
	{ FR_CONF_POINTER("allow_vulnerable_openssl", PW_TYPE_STRING, &main_config.allow_vulnerable_openssl), .dflt = "no" },
#endif
	{ FR_CONF_POINTER("state_seed", PW_TYPE_INTEGER, &main_config.state_seed) },
	CONF_PARSER_TERMINATOR
};
