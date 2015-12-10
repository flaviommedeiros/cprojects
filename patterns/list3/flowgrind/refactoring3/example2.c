switch (code) {
		case 0:
			PARSE_ERR("invalid argument: %s", arg);
		case 'b':
			rpc_bind_addr = strdup(arg);
			if (sscanf(arg, "%s", rpc_bind_addr) != 1)
				PARSE_ERR("failed to parse bind address");
			break;
		case 'c':
			if (sscanf(arg, "%u", &core) != 1)
				PARSE_ERR("failed to parse CPU number");
			break;
		case 'd':
#ifdef DEBUG
			increase_debuglevel();
#endif /* DEBUG */
			break;
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		case 'p':
			if (sscanf(arg, "%u", &port) != 1)
				PARSE_ERR("failed to parse port number");
			break;
#ifdef HAVE_LIBPCAP
		case 'w':
			dump_dir = strdup(arg);
			break;
#endif /* HAVE_LIBPCAP */
		case 'v':
			fprintf(stdout, "%s %s\%s\n%s\n\n%s\n", progname,
				FLOWGRIND_VERSION, FLOWGRIND_COPYRIGHT,
				FLOWGRIND_COPYING, FLOWGRIND_AUTHORS);
			exit(EXIT_SUCCESS);
			break;
		default:
			PARSE_ERR("uncaught option: %s", arg);
			break;
		}
