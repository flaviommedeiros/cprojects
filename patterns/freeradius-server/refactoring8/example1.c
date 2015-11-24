static const CONF_PARSER log_config[] = {
	{ FR_CONF_POINTER("stripped_names", PW_TYPE_BOOLEAN, &log_stripped_names), .dflt = "no" },
	{ FR_CONF_POINTER("auth", PW_TYPE_BOOLEAN, &main_config.log_auth), .dflt = "no" },
	{ FR_CONF_POINTER("auth_badpass", PW_TYPE_BOOLEAN, &main_config.log_auth_badpass), .dflt = "no" },
	{ FR_CONF_POINTER("auth_goodpass", PW_TYPE_BOOLEAN, &main_config.log_auth_goodpass), .dflt = "no" },
	{ FR_CONF_POINTER("msg_badpass", PW_TYPE_STRING, &main_config.auth_badpass_msg) },
	{ FR_CONF_POINTER("msg_goodpass", PW_TYPE_STRING, &main_config.auth_goodpass_msg) },
	{ FR_CONF_POINTER("colourise", PW_TYPE_BOOLEAN, &do_colourise) },
	{ FR_CONF_POINTER("use_utc", PW_TYPE_BOOLEAN, &log_dates_utc) },
	{ FR_CONF_POINTER("msg_denied", PW_TYPE_STRING, &main_config.denied_msg), .dflt = "You are already logged in - access denied" },
#ifdef WITH_CONF_WRITE
	{ FR_CONF_POINTER("write_dir", PW_TYPE_STRING, &main_config.write_dir), .dflt = NULL },
#endif
	CONF_PARSER_TERMINATOR
};
