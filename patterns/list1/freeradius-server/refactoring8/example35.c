static const CONF_PARSER module_config[] = {
	{ FR_CONF_OFFSET("driver", PW_TYPE_STRING, rlm_sql_config_t, sql_driver_name), .dflt = "rlm_sql_null" },
	{ FR_CONF_OFFSET("server", PW_TYPE_STRING, rlm_sql_config_t, sql_server), .dflt = "" },	/* Must be zero length so drivers can determine if it was set */
	{ FR_CONF_OFFSET("port", PW_TYPE_INTEGER, rlm_sql_config_t, sql_port), .dflt = "0" },
	{ FR_CONF_OFFSET("login", PW_TYPE_STRING, rlm_sql_config_t, sql_login), .dflt = "" },
	{ FR_CONF_OFFSET("password", PW_TYPE_STRING | PW_TYPE_SECRET, rlm_sql_config_t, sql_password), .dflt = "" },
	{ FR_CONF_OFFSET("radius_db", PW_TYPE_STRING, rlm_sql_config_t, sql_db), .dflt = "radius" },
	{ FR_CONF_OFFSET("read_groups", PW_TYPE_BOOLEAN, rlm_sql_config_t, read_groups), .dflt = "yes" },
	{ FR_CONF_OFFSET("read_profiles", PW_TYPE_BOOLEAN, rlm_sql_config_t, read_profiles), .dflt = "yes" },
	{ FR_CONF_OFFSET("read_clients", PW_TYPE_BOOLEAN, rlm_sql_config_t, do_clients), .dflt = "no" },
	{ FR_CONF_OFFSET("delete_stale_sessions", PW_TYPE_BOOLEAN, rlm_sql_config_t, delete_stale_sessions), .dflt = "yes" },
	{ FR_CONF_OFFSET("sql_user_name", PW_TYPE_STRING | PW_TYPE_XLAT, rlm_sql_config_t, query_user), .dflt = "" },
	{ FR_CONF_OFFSET("group_attribute", PW_TYPE_STRING, rlm_sql_config_t, group_attribute) },
	{ FR_CONF_OFFSET("logfile", PW_TYPE_STRING | PW_TYPE_XLAT, rlm_sql_config_t, logfile) },
	{ FR_CONF_OFFSET("default_user_profile", PW_TYPE_STRING, rlm_sql_config_t, default_profile), .dflt = "" },
	{ FR_CONF_OFFSET("client_query", PW_TYPE_STRING, rlm_sql_config_t, client_query), .dflt = "SELECT id,nasname,shortname,type,secret FROM nas" },
	{ FR_CONF_OFFSET("open_query", PW_TYPE_STRING, rlm_sql_config_t, connect_query) },

	{ FR_CONF_OFFSET("authorize_check_query", PW_TYPE_STRING | PW_TYPE_XLAT | PW_TYPE_NOT_EMPTY, rlm_sql_config_t, authorize_check_query) },
	{ FR_CONF_OFFSET("authorize_reply_query", PW_TYPE_STRING | PW_TYPE_XLAT | PW_TYPE_NOT_EMPTY, rlm_sql_config_t, authorize_reply_query) },

	{ FR_CONF_OFFSET("authorize_group_check_query", PW_TYPE_STRING | PW_TYPE_XLAT | PW_TYPE_NOT_EMPTY, rlm_sql_config_t, authorize_group_check_query) },
	{ FR_CONF_OFFSET("authorize_group_reply_query", PW_TYPE_STRING | PW_TYPE_XLAT | PW_TYPE_NOT_EMPTY, rlm_sql_config_t, authorize_group_reply_query) },
	{ FR_CONF_OFFSET("group_membership_query", PW_TYPE_STRING | PW_TYPE_XLAT | PW_TYPE_NOT_EMPTY, rlm_sql_config_t, groupmemb_query) },
#ifdef WITH_SESSION_MGMT
	{ FR_CONF_OFFSET("simul_count_query", PW_TYPE_STRING | PW_TYPE_XLAT | PW_TYPE_NOT_EMPTY, rlm_sql_config_t, simul_count_query) },
	{ FR_CONF_OFFSET("simul_verify_query", PW_TYPE_STRING | PW_TYPE_XLAT | PW_TYPE_NOT_EMPTY, rlm_sql_config_t, simul_verify_query) },
#endif
	{ FR_CONF_OFFSET("safe_characters", PW_TYPE_STRING, rlm_sql_config_t, allowed_chars), .dflt = "@abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-_: /" },

	/*
	 *	This only works for a few drivers.
	 */
	{ FR_CONF_OFFSET("query_timeout", PW_TYPE_INTEGER, rlm_sql_config_t, query_timeout) },

	{ FR_CONF_POINTER("accounting", PW_TYPE_SUBSECTION, NULL), .dflt = (void const *) acct_config },

	{ FR_CONF_POINTER("post-auth", PW_TYPE_SUBSECTION, NULL), .dflt = (void const *) postauth_config },
	CONF_PARSER_TERMINATOR
};
