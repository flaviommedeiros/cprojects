if (!conf->collect_cache
			&& !conf->collect_connections
			&& !conf->collect_esi
			&& !conf->collect_backend
#ifdef HAVE_VARNISH_V3
			&& !conf->collect_dirdns
#endif
			&& !conf->collect_fetch
			&& !conf->collect_hcb
			&& !conf->collect_objects
#if HAVE_VARNISH_V2
			&& !conf->collect_purge
#else
			&& !conf->collect_ban
#endif
			&& !conf->collect_session
			&& !conf->collect_shm
			&& !conf->collect_sms
#if HAVE_VARNISH_V2
			&& !conf->collect_sma
			&& !conf->collect_sm
#endif
			&& !conf->collect_struct
			&& !conf->collect_totals
#if HAVE_VARNISH_V3 || HAVE_VARNISH_V4
			&& !conf->collect_uptime
#endif
			&& !conf->collect_vcl
			&& !conf->collect_workers
#if HAVE_VARNISH_V4
			&& !conf->collect_vsm
#endif
	)
	{
		WARNING ("Varnish plugin: No metric has been configured for "
				"instance \"%s\". Disabling this instance.",
				(conf->instance == NULL) ? "localhost" : conf->instance);
		return (EINVAL);
	}
