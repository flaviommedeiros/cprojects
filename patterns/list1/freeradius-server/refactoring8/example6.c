static CONF_PARSER limit_config[] = {
	{ FR_CONF_OFFSET("max_pps", PW_TYPE_INTEGER, listen_socket_t, max_rate) },

#ifdef WITH_TCP
	{ FR_CONF_OFFSET("max_connections", PW_TYPE_INTEGER, listen_socket_t, limit.max_connections), .dflt = "16" },
	{ FR_CONF_OFFSET("lifetime", PW_TYPE_INTEGER, listen_socket_t, limit.lifetime), .dflt = "0" },
	{ FR_CONF_OFFSET("idle_timeout", PW_TYPE_INTEGER, listen_socket_t, limit.idle_timeout), .dflt = STRINGIFY(30) },
#endif
	CONF_PARSER_TERMINATOR
};
