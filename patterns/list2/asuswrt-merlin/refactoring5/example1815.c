#ifdef ENABLE_CLI_NETCAT
if (cli_opts.netcat_host) {
				cli_send_netcat_request();
			} else 
#endif
			if (!cli_opts.no_cmd) {
				cli_send_chansess_request();
			}
