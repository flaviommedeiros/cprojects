module_t rlm_utf8 = {
	.magic		= RLM_MODULE_INIT,
	.name		= "utf8",
	.type		= RLM_TYPE_THREAD_SAFE,
	.methods = {
		[MOD_AUTHORIZE]		= mod_utf8_clean,
		[MOD_PREACCT]		= mod_utf8_clean,
#ifdef WITH_COA
		[MOD_RECV_COA]		= mod_utf8_clean
#endif
	},
};
