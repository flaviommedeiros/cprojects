if(!ENGINE_set_id(e, engine_hwcrhk_id) ||
			!ENGINE_set_name(e, engine_hwcrhk_name) ||
#ifndef OPENSSL_NO_RSA
			!ENGINE_set_RSA(e, &hwcrhk_rsa) ||
#endif
#ifndef OPENSSL_NO_DH
			!ENGINE_set_DH(e, &hwcrhk_dh) ||
#endif
			!ENGINE_set_RAND(e, &hwcrhk_rand) ||
			!ENGINE_set_destroy_function(e, hwcrhk_destroy) ||
			!ENGINE_set_init_function(e, hwcrhk_init) ||
			!ENGINE_set_finish_function(e, hwcrhk_finish) ||
			!ENGINE_set_ctrl_function(e, hwcrhk_ctrl) ||
			!ENGINE_set_load_privkey_function(e, hwcrhk_load_privkey) ||
			!ENGINE_set_load_pubkey_function(e, hwcrhk_load_pubkey) ||
			!ENGINE_set_cmd_defns(e, hwcrhk_cmd_defns))
		return 0;
