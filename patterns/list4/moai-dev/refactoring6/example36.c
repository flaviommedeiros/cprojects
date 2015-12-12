if(!ENGINE_set_id(e, engine_cluster_labs_id) ||
			!ENGINE_set_name(e, engine_cluster_labs_name) ||
#ifndef OPENSSL_NO_RSA
			!ENGINE_set_RSA(e, &cluster_labs_rsa) ||
#endif
#ifndef OPENSSL_NO_DSA
			!ENGINE_set_DSA(e, &cluster_labs_dsa) ||
#endif
#ifndef OPENSSL_NO_DH
			!ENGINE_set_DH(e, &cluster_labs_dh) ||
#endif
			!ENGINE_set_RAND(e, &cluster_labs_rand) ||
			!ENGINE_set_destroy_function(e, cluster_labs_destroy) ||
			!ENGINE_set_init_function(e, cluster_labs_init) ||
			!ENGINE_set_finish_function(e, cluster_labs_finish) ||
			!ENGINE_set_ctrl_function(e, cluster_labs_ctrl) ||
			!ENGINE_set_cmd_defns(e, cluster_labs_cmd_defns))
		return 0;
