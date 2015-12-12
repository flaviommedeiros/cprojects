if(!ENGINE_set_id(e, engine_aep_id) ||
		!ENGINE_set_name(e, engine_aep_name) ||
#ifndef OPENSSL_NO_RSA
		!ENGINE_set_RSA(e, &aep_rsa) ||
#endif
#ifndef OPENSSL_NO_DSA
		!ENGINE_set_DSA(e, &aep_dsa) ||
#endif
#ifndef OPENSSL_NO_DH
		!ENGINE_set_DH(e, &aep_dh) ||
#endif
#ifdef AEPRAND
		!ENGINE_set_RAND(e, &aep_random) ||
#endif
		!ENGINE_set_init_function(e, aep_init) ||
		!ENGINE_set_destroy_function(e, aep_destroy) ||
		!ENGINE_set_finish_function(e, aep_finish) ||
		!ENGINE_set_ctrl_function(e, aep_ctrl) ||
		!ENGINE_set_cmd_defns(e, aep_cmd_defns))
		return 0;
