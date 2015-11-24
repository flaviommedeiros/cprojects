static const CONF_PARSER server_config[] = {
	/*
	 *	FIXME: 'prefix' is the ONLY one which should be
	 *	configured at compile time.  Hard-coding it here is
	 *	bad.  It will be cleaned up once we clean up the
	 *	hard-coded defines for the locations of the various
	 *	files.
	 */
	{ FR_CONF_POINTER("name", PW_TYPE_STRING, &my_name), .dflt = "radiusd" },
	{ FR_CONF_POINTER("prefix", PW_TYPE_STRING, &prefix), .dflt = "/usr/local" },
	{ FR_CONF_POINTER("localstatedir", PW_TYPE_STRING, &localstatedir), .dflt = "${prefix}/var"},
	{ FR_CONF_POINTER("sbindir", PW_TYPE_STRING, &sbindir), .dflt = "${prefix}/sbin"},
	{ FR_CONF_POINTER("logdir", PW_TYPE_STRING, &radlog_dir), .dflt = "${localstatedir}/log"},
	{ FR_CONF_POINTER("run_dir", PW_TYPE_STRING, &run_dir), .dflt = "${localstatedir}/run/${name}"},
	{ FR_CONF_POINTER("libdir", PW_TYPE_STRING, &radlib_dir), .dflt = "${prefix}/lib"},
	{ FR_CONF_POINTER("radacctdir", PW_TYPE_STRING, &radacct_dir), .dflt = "${logdir}/radacct" },
	{ FR_CONF_POINTER("panic_action", PW_TYPE_STRING, &main_config.panic_action) },
	{ FR_CONF_POINTER("hostname_lookups", PW_TYPE_BOOLEAN, &fr_dns_lookups), .dflt = "no" },
	{ FR_CONF_POINTER("max_request_time", PW_TYPE_INTEGER, &main_config.max_request_time), .dflt = STRINGIFY(MAX_REQUEST_TIME) },
	{ FR_CONF_POINTER("cleanup_delay", PW_TYPE_INTEGER, &main_config.cleanup_delay), .dflt = STRINGIFY(CLEANUP_DELAY) },
	{ FR_CONF_POINTER("continuation_timeout", PW_TYPE_INTEGER, &main_config.continuation_timeout), .dflt = "15" },
	{ FR_CONF_POINTER("max_requests", PW_TYPE_INTEGER, &main_config.max_requests), .dflt = STRINGIFY(MAX_REQUESTS) },
	{ FR_CONF_POINTER("pidfile", PW_TYPE_STRING, &main_config.pid_file), .dflt = "${run_dir}/radiusd.pid"},
	{ FR_CONF_POINTER("checkrad", PW_TYPE_STRING, &main_config.checkrad), .dflt = "${sbindir}/checkrad" },

	{ FR_CONF_POINTER("debug_level", PW_TYPE_INTEGER, &main_config.debug_level), .dflt = "0" },

#ifdef WITH_PROXY
	{ FR_CONF_POINTER("proxy_requests", PW_TYPE_BOOLEAN, &main_config.proxy_requests), .dflt = "yes" },
#endif
	{ FR_CONF_POINTER("log", PW_TYPE_SUBSECTION, NULL), .dflt = (void const *) log_config },

	{ FR_CONF_POINTER("resources", PW_TYPE_SUBSECTION, NULL), .dflt = (void const *) resources },

	/*
	 *	People with old configs will have these.  They are listed
	 *	AFTER the "log" section, so if they exist in radiusd.conf,
	 *	it will prefer "log_foo = bar" to "log { foo = bar }".
	 *	They're listed with default values of NULL, so that if they
	 *	DON'T exist in radiusd.conf, then the previously parsed
	 *	values for "log { foo = bar}" will be used.
	 */
	{ FR_CONF_POINTER("log_auth", PW_TYPE_BOOLEAN | PW_TYPE_DEPRECATED, &main_config.log_auth) },
	{ FR_CONF_POINTER("log_auth_badpass", PW_TYPE_BOOLEAN | PW_TYPE_DEPRECATED, &main_config.log_auth_badpass) },
	{ FR_CONF_POINTER("log_auth_goodpass", PW_TYPE_BOOLEAN | PW_TYPE_DEPRECATED, &main_config.log_auth_goodpass) },
	{ FR_CONF_POINTER("log_stripped_names", PW_TYPE_BOOLEAN | PW_TYPE_DEPRECATED, &log_stripped_names) },

	{ FR_CONF_POINTER("security", PW_TYPE_SUBSECTION, NULL), .dflt = (void const *) security_config },
	CONF_PARSER_TERMINATOR
};
