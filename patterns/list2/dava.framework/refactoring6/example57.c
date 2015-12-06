if(!ENGINE_set_id(e, engine_ibmca_id) ||
		!ENGINE_set_name(e, engine_ibmca_name) ||
#ifndef OPENSSL_NO_RSA
		!ENGINE_set_RSA(e, &ibmca_rsa) ||
#endif
#ifndef OPENSSL_NO_DSA
		!ENGINE_set_DSA(e, &ibmca_dsa) ||
#endif
#ifndef OPENSSL_NO_DH
		!ENGINE_set_DH(e, &ibmca_dh) ||
#endif
		!ENGINE_set_RAND(e, &ibmca_rand) ||
		!ENGINE_set_destroy_function(e, ibmca_destroy) ||
		!ENGINE_set_init_function(e, ibmca_init) ||
		!ENGINE_set_finish_function(e, ibmca_finish) ||
		!ENGINE_set_ctrl_function(e, ibmca_ctrl) ||
		!ENGINE_set_cmd_defns(e, ibmca_cmd_defns))
		return 0;
