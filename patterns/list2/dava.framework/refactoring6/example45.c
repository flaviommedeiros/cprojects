if(!ENGINE_set_id(e, engine_sureware_id) ||
	   !ENGINE_set_name(e, engine_sureware_name) ||
#ifndef OPENSSL_NO_RSA
	   !ENGINE_set_RSA(e, &surewarehk_rsa) ||
#endif
#ifndef OPENSSL_NO_DSA
	   !ENGINE_set_DSA(e, &surewarehk_dsa) ||
#endif
#ifndef OPENSSL_NO_DH
	   !ENGINE_set_DH(e, &surewarehk_dh) ||
#endif
	   !ENGINE_set_RAND(e, &surewarehk_rand) ||
	   !ENGINE_set_destroy_function(e, surewarehk_destroy) ||
	   !ENGINE_set_init_function(e, surewarehk_init) ||
	   !ENGINE_set_finish_function(e, surewarehk_finish) ||
	   !ENGINE_set_ctrl_function(e, surewarehk_ctrl) ||
	   !ENGINE_set_load_privkey_function(e, surewarehk_load_privkey) ||
	   !ENGINE_set_load_pubkey_function(e, surewarehk_load_pubkey))
	  return 0;
