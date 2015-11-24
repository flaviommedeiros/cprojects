static const CONF_PARSER module_config[] = {
	{ FR_CONF_OFFSET("id_length", PW_TYPE_INTEGER, rlm_yubikey_t, id_len), .dflt = "12" },
	{ FR_CONF_OFFSET("split", PW_TYPE_BOOLEAN, rlm_yubikey_t, split), .dflt = "yes" },
	{ FR_CONF_OFFSET("decrypt", PW_TYPE_BOOLEAN, rlm_yubikey_t, decrypt), .dflt = "no" },
	{ FR_CONF_OFFSET("validate", PW_TYPE_BOOLEAN, rlm_yubikey_t, validate), .dflt = "no" },
#ifdef HAVE_YKCLIENT
	{ FR_CONF_POINTER("validation", PW_TYPE_SUBSECTION, NULL), .dflt = (void const *) validation_config },
#endif
	CONF_PARSER_TERMINATOR
};
