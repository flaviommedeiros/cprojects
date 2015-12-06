if(!ENGINE_set_id(e, engine_atalla_id) ||
			!ENGINE_set_name(e, engine_atalla_name) ||
#ifndef OPENSSL_NO_RSA
			!ENGINE_set_RSA(e, &atalla_rsa) ||
#endif
#ifndef OPENSSL_NO_DSA
			!ENGINE_set_DSA(e, &atalla_dsa) ||
#endif
#ifndef OPENSSL_NO_DH
			!ENGINE_set_DH(e, &atalla_dh) ||
#endif
			!ENGINE_set_destroy_function(e, atalla_destroy) ||
			!ENGINE_set_init_function(e, atalla_init) ||
			!ENGINE_set_finish_function(e, atalla_finish) ||
			!ENGINE_set_ctrl_function(e, atalla_ctrl) ||
			!ENGINE_set_cmd_defns(e, atalla_cmd_defns))
		return 0;
