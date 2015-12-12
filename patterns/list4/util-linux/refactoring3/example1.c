switch (ch) {
		case 'f':		/* file to log */
			if (freopen(optarg, "r", stdin) == NULL)
				err(EXIT_FAILURE, _("file %s"), optarg);
			stdout_reopened = 1;
			break;
		case 'e':
			ctl.skip_empty_lines = 1;
			break;
		case 'i':		/* log process id also */
			ctl.pid = logger_getpid();
			break;
		case OPT_ID:
			if (optarg) {
				const char *p = optarg;

				if (*p == '=')
					p++;
				ctl.pid = strtoul_or_err(optarg, _("failed to parse id"));
			} else
				ctl.pid = logger_getpid();
			break;
		case 'p':		/* priority */
			ctl.pri = pencode(optarg);
			break;
		case 's':		/* log to standard error */
			ctl.stderr_printout = 1;
			break;
		case 't':		/* tag */
			ctl.tag = optarg;
			break;
		case 'u':		/* unix socket */
			ctl.unix_socket = optarg;
			break;
		case 'S':		/* max message size */
			ctl.max_message_size = strtosize_or_err(optarg,
				_("failed to parse message size"));
			break;
		case 'd':
			ctl.socket_type = TYPE_UDP;
			break;
		case 'T':
			ctl.socket_type = TYPE_TCP;
			break;
		case 'n':
			ctl.server = optarg;
			break;
		case 'P':
			ctl.port = optarg;
			break;
		case 'V':
			printf(UTIL_LINUX_VERSION);
			exit(EXIT_SUCCESS);
		case 'h':
			usage(stdout);
		case OPT_OCTET_COUNT:
			ctl.octet_count = 1;
			break;
		case OPT_PRIO_PREFIX:
			ctl.prio_prefix = 1;
			break;
		case OPT_RFC3164:
			ctl.syslogfp = syslog_rfc3164_header;
			break;
		case OPT_RFC5424:
			ctl.syslogfp = syslog_rfc5424_header;
			if (optarg)
				parse_rfc5424_flags(&ctl, optarg);
			break;
		case OPT_MSGID:
			if (strchr(optarg, ' '))
				errx(EXIT_FAILURE, _("--msgid cannot contain space"));
			ctl.msgid = optarg;
			break;
#ifdef HAVE_LIBSYSTEMD
		case OPT_JOURNALD:
			if (optarg) {
				jfd = fopen(optarg, "r");
				if (!jfd)
					err(EXIT_FAILURE, _("cannot open %s"),
					    optarg);
			} else
				jfd = stdin;
			break;
#endif
		case OPT_SOCKET_ERRORS:
			unix_socket_errors_mode = parse_unix_socket_errors_flags(optarg);
			break;
		case OPT_NOACT:
			ctl.noact = 1;
			break;
		case OPT_STRUCTURED_DATA_ID:
			if (!valid_structured_data_id(optarg))
				errx(EXIT_FAILURE, _("invalid structured data ID: '%s'"), optarg);
			add_structured_data_id(get_user_structured_data(&ctl), optarg);
			break;
		case OPT_STRUCTURED_DATA_PARAM:
			if (!valid_structured_data_param(optarg))
				errx(EXIT_FAILURE, _("invalid structured data parameter: '%s'"), optarg);
			add_structured_data_param(get_user_structured_data(&ctl), optarg);
			break;
		case '?':
		default:
			usage(stderr);
		}
