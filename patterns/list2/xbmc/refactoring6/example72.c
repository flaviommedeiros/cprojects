if (env->plugin_listeners == NULL
			|| env->loggers == NULL
#ifdef CP_THREADS
			|| env->mutex == NULL
#endif
			|| env->plugin_dirs == NULL
			|| env->infos == NULL
			|| env->plugins == NULL
			|| env->started_plugins == NULL
			|| env->ext_points == NULL
			|| env->extensions == NULL
			|| env->run_funcs == NULL) {
			status = CP_ERR_RESOURCE;
			break;
		}
