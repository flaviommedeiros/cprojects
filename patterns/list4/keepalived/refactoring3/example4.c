switch (c) {
		case 'v':
			fprintf(stderr, VERSION_STRING);
			exit(0);
			break;
		case 'h':
			usage(argv[0]);
			exit(0);
			break;
		case 'l':
			__set_bit(LOG_CONSOLE_BIT, &debug);
			break;
		case 'n':
			__set_bit(DONT_FORK_BIT, &debug);
			break;
		case 'd':
			__set_bit(DUMP_CONF_BIT, &debug);
			break;
		case 'V':
			__set_bit(DONT_RELEASE_VRRP_BIT, &debug);
			break;
		case 'I':
			__set_bit(DONT_RELEASE_IPVS_BIT, &debug);
			break;
		case 'D':
			__set_bit(LOG_DETAIL_BIT, &debug);
			break;
		case 'R':
			__set_bit(DONT_RESPAWN_BIT, &debug);
			break;
		case 'X':
			__set_bit(RELEASE_VIPS_BIT, &debug);
			break;
		case 'S':
			log_facility = LOG_FACILITY[atoi(optarg)].facility;
			break;
		case 'f':
			conf_file = optarg;
			break;
		case 'P':
			daemon_mode |= 1;
			break;
		case 'C':
			daemon_mode |= 2;
			break;
		case 'p':
			main_pidfile = optarg;
			break;
		case 'c':
			checkers_pidfile = optarg;
			break;
		case 'r':
			vrrp_pidfile = optarg;
			break;
#ifdef _WITH_SNMP_
		case 'x':
			snmp = 1;
			break;
		case 'A':
			snmp_socket = optarg;
			break;
#endif
		default:
			exit(0);
			break;
		}
