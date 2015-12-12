if (!ENGINE_set_id(e, padlock_id) ||
	    !ENGINE_set_name(e, padlock_name) ||

	    !ENGINE_set_init_function(e, padlock_init) ||
#ifndef OPENSSL_NO_AES
	    (padlock_use_ace && !ENGINE_set_ciphers (e, padlock_ciphers)) ||
#endif
	    (padlock_use_rng && !ENGINE_set_RAND (e, &padlock_rand))) {
		return 0;
	}
