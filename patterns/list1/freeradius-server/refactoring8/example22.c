static CONF_PARSER module_config[] = {
	{ FR_CONF_OFFSET("tls", PW_TYPE_STRING, rlm_eap_peap_t, tls_conf_name) },

	{ FR_CONF_OFFSET("default_eap_type", PW_TYPE_STRING, rlm_eap_peap_t, default_method_name), .dflt = "mschapv2" },

	{ FR_CONF_OFFSET("copy_request_to_tunnel", PW_TYPE_BOOLEAN, rlm_eap_peap_t, copy_request_to_tunnel), .dflt = "no" },

	{ FR_CONF_OFFSET("use_tunneled_reply", PW_TYPE_BOOLEAN, rlm_eap_peap_t, use_tunneled_reply), .dflt = "no" },

#ifdef WITH_PROXY
	{ FR_CONF_OFFSET("proxy_tunneled_request_as_eap", PW_TYPE_BOOLEAN, rlm_eap_peap_t, proxy_tunneled_request_as_eap), .dflt = "yes" },
#endif

	{ FR_CONF_OFFSET("virtual_server", PW_TYPE_STRING, rlm_eap_peap_t, virtual_server) },

	{ FR_CONF_OFFSET("soh", PW_TYPE_BOOLEAN, rlm_eap_peap_t, soh), .dflt = "no" },

	{ FR_CONF_OFFSET("require_client_cert", PW_TYPE_BOOLEAN, rlm_eap_peap_t, req_client_cert), .dflt = "no" },

	{ FR_CONF_OFFSET("soh_virtual_server", PW_TYPE_STRING, rlm_eap_peap_t, soh_virtual_server) },
	CONF_PARSER_TERMINATOR
};
