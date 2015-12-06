module_t rlm_krb5 = {
	.magic		= RLM_MODULE_INIT,
	.name		= "krb5",
	.type		= RLM_TYPE_HUP_SAFE
#ifdef KRB5_IS_THREAD_SAFE
	| RLM_TYPE_THREAD_SAFE
#endif
	,
	.inst_size	= sizeof(rlm_krb5_t),
	.config		= module_config,
	.instantiate	= mod_instantiate,
	.detach		= mod_detach,
	.methods = {
		[MOD_AUTHENTICATE]	= mod_authenticate
	},
};
