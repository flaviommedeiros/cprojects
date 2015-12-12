if ( !ENGINE_set_id ( e, engine_zencod_id ) ||
			!ENGINE_set_name ( e, engine_zencod_name ) ||
#ifndef OPENSSL_NO_RSA
			!ENGINE_set_RSA ( e, &zencod_rsa ) ||
#endif
#ifndef OPENSSL_NO_DSA
			!ENGINE_set_DSA ( e, &zencod_dsa ) ||
#endif
#ifndef OPENSSL_NO_DH
			!ENGINE_set_DH ( e, &zencod_dh ) ||
#endif
			!ENGINE_set_RAND ( e, &zencod_rand ) ||

			!ENGINE_set_destroy_function ( e, zencod_destroy ) ||
			!ENGINE_set_init_function ( e, zencod_init ) ||
			!ENGINE_set_finish_function ( e, zencod_finish ) ||
			!ENGINE_set_ctrl_function ( e, zencod_ctrl ) ||
			!ENGINE_set_cmd_defns ( e, zencod_cmd_defns ) ||
			!ENGINE_set_digests ( e, engine_digests ) ||
			!ENGINE_set_ciphers ( e, engine_ciphers ) ) {
		return 0 ;
	}
