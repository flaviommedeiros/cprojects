if(!ENGINE_set_id(e, engine_e_rsax_id) ||
			!ENGINE_set_name(e, engine_e_rsax_name) ||
#ifndef OPENSSL_NO_RSA
			!ENGINE_set_RSA(e, &e_rsax_rsa) ||
#endif
			!ENGINE_set_destroy_function(e, e_rsax_destroy) ||
			!ENGINE_set_init_function(e, e_rsax_init) ||
			!ENGINE_set_finish_function(e, e_rsax_finish) ||
			!ENGINE_set_ctrl_function(e, e_rsax_ctrl) ||
			!ENGINE_set_cmd_defns(e, e_rsax_cmd_defns))
		return 0;
