module_t rlm_realm = {
	.magic		= RLM_MODULE_INIT,
	.name		= "realm",
	.type		= RLM_TYPE_HUP_SAFE,
	.inst_size	= sizeof(struct rlm_realm_t),
	.config		= module_config,
	.instantiate	= mod_instantiate,
	.methods = {
		[MOD_AUTHORIZE]		= mod_authorize,
		[MOD_PREACCT]		= mod_preacct,
#ifdef WITH_COA
		[MOD_RECV_COA]		= mod_realm_recv_coa
#endif
	},
};
