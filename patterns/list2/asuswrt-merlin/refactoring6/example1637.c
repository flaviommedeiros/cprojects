if (options->ce.remote || options->ifconfig_local
	  || options->ifconfig_remote_netmask
#ifdef ENABLE_CRYPTO
	  || options->shared_secret_file
#ifdef ENABLE_SSL
	  || options->tls_server || options->tls_client
#endif
#endif
	)
	msg (M_FATAL|M_OPTERR,
	     "options --mktun or --rmtun should only be used together with --dev");
