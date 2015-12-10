switch (code) {
	case 0:
		PARSE_ERR("invalid argument: %s", arg);
	/* general options */
	case 'h':
		if (!arg || !strlen(arg))
			usage(EXIT_SUCCESS);
		else if (!strcmp(arg, "socket"))
			usage_sockopt();
		else if (!strcmp(arg, "traffic"))
			usage_trafgenopt();
		else
			PARSE_ERR("invalid argument '%s' for %s", arg, opt_string);
		break;
	case 'v':
		fprintf(stdout, "%s %s\n%s\n%s\n\n%s\n", progname,
			FLOWGRIND_VERSION, FLOWGRIND_COPYRIGHT,
			FLOWGRIND_COPYING, FLOWGRIND_AUTHORS);
		exit(EXIT_SUCCESS);

	/* controller options */
	case 'c':
		parse_colon_option(arg);
		break;
#ifdef DEBUG
	case 'd':
		increase_debuglevel();
		break;
#endif /* DEBUG */
	case 'e':
		copt.dump_prefix = strdup(arg);
		break;
	case 'i':
		if (sscanf(arg, "%lf", &copt.reporting_interval) != 1 ||
					copt.reporting_interval <= 0)
			PARSE_ERR("option %s needs a positive number "
				  "(in seconds)", opt_string);
		break;
	case LOG_FILE_OPTION:
		copt.log_to_file = true;
		if (arg)
			log_filename = strdup(arg);
		break;
	case 'm':
		copt.mbyte = true;
		column_info[COL_THROUGH].header.unit = " [MiB/s]";
		break;
	case 'n':
		if (sscanf(arg, "%hd", &copt.num_flows) != 1 ||
			   copt.num_flows > MAX_FLOWS)
			PARSE_ERR("option %s (number of flows) must be within "
				  "[1..%d]", opt_string, MAX_FLOWS);
		break;
	case 'o':
		copt.clobber = true;
		break;
	case 'p':
		copt.symbolic = false;
		break;
	case 'q':
		copt.log_to_stdout = false;
		break;
	case 's':
		if (!strcmp(arg, "segment"))
			copt.force_unit = SEGMENT_BASED;
		else if (!strcmp(arg, "byte"))
			copt.force_unit = BYTE_BASED;
		else
			PARSE_ERR("invalid argument '%s' for option %s",
				  arg, opt_string);
		break;
	case 'w':
		copt.log_to_file = true;
		break;
	/* unknown option or missing option-argument */
	default:
		PARSE_ERR("uncaught option: %s", arg);
		break;
	}
