#ifdef ENABLE_CLI_PROXYCMD
if (cli_opts.proxycmd) {
		cli_proxy_cmd(&sock_in, &sock_out);
		m_free(cli_opts.proxycmd);
	} else
#endif
	{
		progress = connect_remote(cli_opts.remotehost, cli_opts.remoteport, cli_connected, &ses);
		sock_in = sock_out = -1;
	}
