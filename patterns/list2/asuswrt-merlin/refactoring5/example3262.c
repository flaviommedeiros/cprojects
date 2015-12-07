#ifdef ENABLE_CLI_PUBKEY_AUTH
if (opt == OPT_AUTHKEY) {
			TRACE(("opt authkey"))
			loadidentityfile(&argv[i][j], 1);
		}
		else
#endif
#ifdef ENABLE_CLI_REMOTETCPFWD
		if (opt == OPT_REMOTETCPFWD) {
			TRACE(("opt remotetcpfwd"))
			addforward(&argv[i][j], cli_opts.remotefwds);
		}
		else
#endif
#ifdef ENABLE_CLI_LOCALTCPFWD
		if (opt == OPT_LOCALTCPFWD) {
			TRACE(("opt localtcpfwd"))
			addforward(&argv[i][j], cli_opts.localfwds);
		}
		else
#endif
#ifdef ENABLE_CLI_NETCAT
		if (opt == OPT_NETCAT) {
			TRACE(("opt netcat"))
			add_netcat(&argv[i][j]);
		}
		else
#endif
		if (next) {
			/* The previous flag set a value to assign */
			*next = &argv[i][j];
			if (*next == NULL)
				dropbear_exit("Invalid null argument");
			next = NULL;
		}
