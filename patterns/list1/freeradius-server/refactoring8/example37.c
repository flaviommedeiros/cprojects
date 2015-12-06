module_t rlm_yubikey = {
	.magic		= RLM_MODULE_INIT,
	.name		= "yubikey",
	.type		= RLM_TYPE_THREAD_SAFE,
	.inst_size	= sizeof(rlm_yubikey_t),
	.config		= module_config,
	.bootstrap	= mod_bootstrap,
	.instantiate	= mod_instantiate,
#ifdef HAVE_YKCLIENT
	.detach		= mod_detach,
#endif
	.methods = {
		[MOD_AUTHENTICATE]	= mod_authenticate,
		[MOD_AUTHORIZE]		= mod_authorize
	},
};
