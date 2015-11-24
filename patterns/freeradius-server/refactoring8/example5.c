static const CONF_PARSER bootstrap_config[] = {
	{ FR_CONF_POINTER("security", PW_TYPE_SUBSECTION, NULL), .dflt = (void const *) bootstrap_security_config },

	{ FR_CONF_POINTER("name", PW_TYPE_STRING, &my_name), .dflt = "radiusd" },
	{ FR_CONF_POINTER("prefix", PW_TYPE_STRING, &prefix), .dflt = "/usr/local" },
	{ FR_CONF_POINTER("localstatedir", PW_TYPE_STRING, &localstatedir), .dflt = "${prefix}/var"},

	{ FR_CONF_POINTER("logdir", PW_TYPE_STRING, &radlog_dir), .dflt = "${localstatedir}/log"},
	{ FR_CONF_POINTER("run_dir", PW_TYPE_STRING, &run_dir), .dflt = "${localstatedir}/run/${name}"},

	/*
	 *	For backwards compatibility.
	 */
#ifdef HAVE_SETUID
	{ FR_CONF_POINTER("user", PW_TYPE_STRING | PW_TYPE_DEPRECATED, &uid_name) },
	{ FR_CONF_POINTER("group", PW_TYPE_STRING | PW_TYPE_DEPRECATED, &gid_name) },
#endif
	{ FR_CONF_POINTER("chroot", PW_TYPE_STRING | PW_TYPE_DEPRECATED, &chroot_dir) },
	{ FR_CONF_POINTER("allow_core_dumps", PW_TYPE_BOOLEAN | PW_TYPE_DEPRECATED, &allow_core_dumps) },
	CONF_PARSER_TERMINATOR
};
