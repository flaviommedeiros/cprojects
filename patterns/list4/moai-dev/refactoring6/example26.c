if(!ENGINE_set_id(e, engine_cswift_id) ||
			!ENGINE_set_name(e, engine_cswift_name) ||
#ifndef OPENSSL_NO_RSA
			!ENGINE_set_RSA(e, &cswift_rsa) ||
#endif
#ifndef OPENSSL_NO_DSA
			!ENGINE_set_DSA(e, &cswift_dsa) ||
#endif
#ifndef OPENSSL_NO_DH
			!ENGINE_set_DH(e, &cswift_dh) ||
#endif
			!ENGINE_set_RAND(e, &cswift_random) ||
			!ENGINE_set_destroy_function(e, cswift_destroy) ||
			!ENGINE_set_init_function(e, cswift_init) ||
			!ENGINE_set_finish_function(e, cswift_finish) ||
			!ENGINE_set_ctrl_function(e, cswift_ctrl) ||
			!ENGINE_set_cmd_defns(e, cswift_cmd_defns))
		return 0;
