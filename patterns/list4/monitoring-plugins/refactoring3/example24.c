switch (c) {
		case 'h':									/* help */
			print_help ();
			exit (STATE_UNKNOWN);
		case 'V':									/* version */
			print_revision (progname, NP_VERSION);
			exit (STATE_UNKNOWN);
		case 't':									/* timeout period */
			if (!is_intnonneg (optarg))
				usage2 (_("Timeout interval must be a positive integer"), optarg);
			else
				socket_timeout = atoi (optarg);
			break;
		case 'H':
			ld_host = optarg;
			break;
		case 'b':
			ld_base = optarg;
			break;
		case 'p':
			ld_port = atoi (optarg);
			break;
		case 'a':
			ld_attr = optarg;
			break;
		case 'D':
			ld_binddn = optarg;
			break;
		case 'P':
			ld_passwd = optarg;
			break;
		case 'w':
			warn_time = strtod (optarg, NULL);
			break;
		case 'c':
			crit_time = strtod (optarg, NULL);
			break;
		case 'W':
			warn_entries = optarg;
			break;
		case 'C':
			crit_entries = optarg;
			break;
#ifdef HAVE_LDAP_SET_OPTION
		case '2':
			ld_protocol = 2;
			break;
		case '3':
			ld_protocol = 3;
			break;
#endif
		case '4':
			address_family = AF_INET;
			break;
		case 'v':
			verbose++;
			break;
		case 'T':
			if (! ssl_on_connect)
				starttls = TRUE;
			else
				usage_va(_("%s cannot be combined with %s"), "-T/--starttls", "-S/--ssl");
			break;
		case 'S':
			if (! starttls) {
				ssl_on_connect = TRUE;
				if (ld_port == -1)
					ld_port = LDAPS_PORT;
			} else
				usage_va(_("%s cannot be combined with %s"), "-S/--ssl", "-T/--starttls");
			break;
		case '6':
#ifdef USE_IPV6
			address_family = AF_INET6;
#else
			usage (_("IPv6 support not available\n"));
#endif
			break;
		default:
			usage5 ();
		}
