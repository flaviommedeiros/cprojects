if ((server->prog == prog) &&
#if CONFIG_MSM_AMSS_VERSION >= 6350
		    msm_rpc_is_compatible_version(server->vers, vers)) {
#else
		    server->vers == vers) {
#endif
			mutex_unlock(&rpc_server_list_lock);
			return server;
		}
