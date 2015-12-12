if (!set_gpass_option(ctx) ||
#if !defined(NO_SSL)
	    !set_ssl_option(ctx) ||
#endif
	    !set_ports_option(ctx) ||
#if !defined(_WIN32)
	    !set_uid_option(ctx) ||
#endif
	    !set_acl_option(ctx)) {
		free_context(ctx);
		pthread_setspecific(sTlsKey, NULL);
		return NULL;
	}
