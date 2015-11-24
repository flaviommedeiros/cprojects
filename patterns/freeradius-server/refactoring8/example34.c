static const CONF_PARSER module_config[] = {
	{ FR_CONF_OFFSET("huntgroups", PW_TYPE_FILE_INPUT, rlm_preprocess_t, huntgroup_file) },
	{ FR_CONF_OFFSET("hints", PW_TYPE_FILE_INPUT, rlm_preprocess_t, hints_file) },
	{ FR_CONF_OFFSET("with_ascend_hack", PW_TYPE_BOOLEAN, rlm_preprocess_t, with_ascend_hack), .dflt = "no" },
	{ FR_CONF_OFFSET("ascend_channels_per_line", PW_TYPE_INTEGER, rlm_preprocess_t, ascend_channels_per_line), .dflt = "23" },

	{ FR_CONF_OFFSET("with_ntdomain_hack", PW_TYPE_BOOLEAN, rlm_preprocess_t, with_ntdomain_hack), .dflt = "no" },
	{ FR_CONF_OFFSET("with_specialix_jetstream_hack", PW_TYPE_BOOLEAN, rlm_preprocess_t, with_specialix_jetstream_hack), .dflt = "no" },
	{ FR_CONF_OFFSET("with_cisco_vsa_hack", PW_TYPE_BOOLEAN, rlm_preprocess_t, with_cisco_vsa_hack), .dflt = "no" },
	{ FR_CONF_OFFSET("with_alvarion_vsa_hack", PW_TYPE_BOOLEAN, rlm_preprocess_t, with_alvarion_vsa_hack), .dflt = "no" },
#if 0
	{ FR_CONF_OFFSET("with_cablelabs_vsa_hack", PW_TYPE_BOOLEAN, rlm_preprocess_t, with_cablelabs_vsa_hack) },
#endif
	CONF_PARSER_TERMINATOR
};
