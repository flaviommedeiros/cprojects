if(!ENGINE_set_id(e, engine_nuron_id) ||
			!ENGINE_set_name(e, engine_nuron_name) ||
#ifndef OPENSSL_NO_RSA
			!ENGINE_set_RSA(e, &nuron_rsa) ||
#endif
#ifndef OPENSSL_NO_DSA
			!ENGINE_set_DSA(e, &nuron_dsa) ||
#endif
#ifndef OPENSSL_NO_DH
			!ENGINE_set_DH(e, &nuron_dh) ||
#endif
			!ENGINE_set_destroy_function(e, nuron_destroy) ||
			!ENGINE_set_init_function(e, nuron_init) ||
			!ENGINE_set_finish_function(e, nuron_finish) ||
			!ENGINE_set_ctrl_function(e, nuron_ctrl) ||
			!ENGINE_set_cmd_defns(e, nuron_cmd_defns))
		return 0;
