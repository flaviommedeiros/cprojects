static const CONF_PARSER bootstrap_security_config[] = {
#ifdef HAVE_SETUID
	{ FR_CONF_POINTER("user", PW_TYPE_STRING, &uid_name) },
	{ FR_CONF_POINTER("group", PW_TYPE_STRING, &gid_name) },
#endif
	{ FR_CONF_POINTER("chroot", PW_TYPE_STRING, &chroot_dir) },
	{ FR_CONF_POINTER("allow_core_dumps", PW_TYPE_BOOLEAN, &allow_core_dumps), .dflt = "no" },
	CONF_PARSER_TERMINATOR
};
