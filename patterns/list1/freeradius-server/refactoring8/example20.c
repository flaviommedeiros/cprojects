module_t rlm_passwd = {
	.magic		= RLM_MODULE_INIT,
	.name		= "passwd",
	.type		= RLM_TYPE_HUP_SAFE,
	.inst_size	= sizeof(rlm_passwd_t),
	.config		= module_config,
	.instantiate	= mod_instantiate,
	.detach		= mod_detach,
	.methods = {
		[MOD_AUTHORIZE]		= mod_passwd_map,
		[MOD_ACCOUNTING]	= mod_passwd_map,
		[MOD_POST_AUTH]		= mod_passwd_map,
		[MOD_PRE_PROXY]		= mod_passwd_map,
		[MOD_POST_PROXY]  	= mod_passwd_map,
#ifdef WITH_COA
		[MOD_RECV_COA]		= mod_passwd_map,
		[MOD_SEND_COA]		= mod_passwd_map
#endif
	},
};
