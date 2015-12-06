module_t rlm_linelog = {
	.magic		= RLM_MODULE_INIT,
	.name		= "linelog",
	.type		= RLM_TYPE_HUP_SAFE,
	.inst_size	= sizeof(linelog_instance_t),
	.config		= module_config,
	.instantiate	= mod_instantiate,
	.detach		= mod_detach,
	.methods = {
		[MOD_AUTHENTICATE]	= mod_do_linelog,
		[MOD_AUTHORIZE]		= mod_do_linelog,
		[MOD_PREACCT]		= mod_do_linelog,
		[MOD_ACCOUNTING]	= mod_do_linelog,
		[MOD_PRE_PROXY]		= mod_do_linelog,
		[MOD_POST_PROXY]	= mod_do_linelog,
		[MOD_POST_AUTH]		= mod_do_linelog,
#ifdef WITH_COA
		[MOD_RECV_COA]		= mod_do_linelog,
		[MOD_SEND_COA]		= mod_do_linelog
#endif
	},
};
