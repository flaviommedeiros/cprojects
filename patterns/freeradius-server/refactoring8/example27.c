static CONF_PARSER module_config[] = {
	{ FR_CONF_OFFSET("format", PW_TYPE_STRING, rlm_realm_t, format_string), .dflt = "suffix" },
	{ FR_CONF_OFFSET("delimiter", PW_TYPE_STRING, rlm_realm_t, delim), .dflt = "@" },
	{ FR_CONF_OFFSET("ignore_default", PW_TYPE_BOOLEAN, rlm_realm_t, ignore_default), .dflt = "no" },
	{ FR_CONF_OFFSET("ignore_null", PW_TYPE_BOOLEAN, rlm_realm_t, ignore_null), .dflt = "no" },

#ifdef HAVE_TRUST_ROUTER_TR_DH_H
	{ FR_CONF_OFFSET("default_community", PW_TYPE_STRING, rlm_realm_t, default_community), .dflt = "none" },
	{ FR_CONF_OFFSET("rp_realm", PW_TYPE_STRING, rlm_realm_t, rp_realm), .dflt = "none" },
	{ FR_CONF_OFFSET("trust_router", PW_TYPE_STRING, rlm_realm_t, trust_router), .dflt = "none" },
	{ FR_CONF_OFFSET("tr_port", PW_TYPE_INTEGER, rlm_realm_t, tr_port), .dflt = "0" },
#endif
	CONF_PARSER_TERMINATOR
};
