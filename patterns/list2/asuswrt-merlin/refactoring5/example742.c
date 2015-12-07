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
