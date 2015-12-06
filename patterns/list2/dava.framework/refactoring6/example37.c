if(!ENGINE_set_id(e, engine_ubsec_id) ||
			!ENGINE_set_name(e, engine_ubsec_name) ||
#ifndef OPENSSL_NO_RSA
			!ENGINE_set_RSA(e, &ubsec_rsa) ||
#endif
#ifndef OPENSSL_NO_DSA
			!ENGINE_set_DSA(e, &ubsec_dsa) ||
#endif
#ifndef OPENSSL_NO_DH
			!ENGINE_set_DH(e, &ubsec_dh) ||
#endif
			!ENGINE_set_destroy_function(e, ubsec_destroy) ||
			!ENGINE_set_init_function(e, ubsec_init) ||
			!ENGINE_set_finish_function(e, ubsec_finish) ||
			!ENGINE_set_ctrl_function(e, ubsec_ctrl) ||
			!ENGINE_set_cmd_defns(e, ubsec_cmd_defns))
		return 0;
