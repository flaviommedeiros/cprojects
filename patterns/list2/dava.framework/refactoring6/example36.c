if(!ENGINE_set_id(e, engine_4758_cca_id) ||
			!ENGINE_set_name(e, engine_4758_cca_name) ||
#ifndef OPENSSL_NO_RSA
			!ENGINE_set_RSA(e, &ibm_4758_cca_rsa) ||
#endif
			!ENGINE_set_RAND(e, &ibm_4758_cca_rand) ||
			!ENGINE_set_destroy_function(e, ibm_4758_cca_destroy) ||
			!ENGINE_set_init_function(e, ibm_4758_cca_init) ||
			!ENGINE_set_finish_function(e, ibm_4758_cca_finish) ||
			!ENGINE_set_ctrl_function(e, ibm_4758_cca_ctrl) ||
#ifndef OPENSSL_NO_RSA
			!ENGINE_set_load_privkey_function(e, ibm_4758_load_privkey) ||
			!ENGINE_set_load_pubkey_function(e, ibm_4758_load_pubkey) ||
#endif
			!ENGINE_set_cmd_defns(e, cca4758_cmd_defns))
		return 0;
