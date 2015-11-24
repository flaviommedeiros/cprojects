static CONF_PARSER module_config[] = {

#define A(x) { FR_CONF_OFFSET("mod_" #x, PW_TYPE_STRING, rlm_python_t, x.module_name) }, \
	{ FR_CONF_OFFSET("func_" #x, PW_TYPE_STRING, rlm_python_t, x.function_name) },

	A(instantiate)
	A(authorize)
	A(authenticate)
	A(preacct)
	A(accounting)
	A(checksimul)
	A(pre_proxy)
	A(post_proxy)
	A(post_auth)
#ifdef WITH_COA
	A(recv_coa)
	A(send_coa)
#endif
	A(detach)

#undef A

	{ FR_CONF_OFFSET("python_path", PW_TYPE_STRING, rlm_python_t, python_path) },
	CONF_PARSER_TERMINATOR
};
