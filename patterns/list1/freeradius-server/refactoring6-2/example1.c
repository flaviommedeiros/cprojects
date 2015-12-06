while ((c = getopt(argc, argv, "46c:d:D:f:Fhi:l:n:p:qr:sS:t:vx"
#ifdef WITH_TCP
		"P:"
#endif
		)) != EOF) switch (c) {
		case '4':
			force_af = AF_INET;
			break;

		case '6':
			force_af = AF_INET6;
			break;

		case 'D':
			conf->dict_dir = optarg;
			break;

		case 'd':
			conf->radius_dir = optarg;
			break;

		case 'l':
		{
			int log_fd;

			if (strcmp(optarg, "stderr") == 0) {
				fr_log_fp = stderr;	/* stdout goes to netsnmp */
				break;
			}

			log_fd = open(optarg, O_WRONLY | O_APPEND | O_CREAT, 0640);
			if (log_fd < 0) {
				fprintf(stderr, "radsnmp: Failed to open log file %s: %s\n",
					optarg, fr_syserror(errno));
				exit(EXIT_FAILURE);
			}
			fr_log_fp = fdopen(log_fd, "a");
		}
			break;

#ifdef WITH_TCP
		case 'P':
			conf->proto_str = optarg;
			if (strcmp(conf->proto_str, "tcp") != 0) {
				if (strcmp(conf->proto_str, "udp") != 0) usage();
			} else {
				conf->proto = IPPROTO_TCP;
			}
			break;

#endif

		case 'r':
			if (!isdigit((int) *optarg)) usage();
			conf->retries = atoi(optarg);
			if ((conf->retries == 0) || (conf->retries > 1000)) usage();
			break;

		case 'S':
		{
			char *p;
			fp = fopen(optarg, "r");
			if (!fp) {
			       ERROR("Error opening %s: %s", optarg, fr_syserror(errno));
			       exit(EXIT_FAILURE);
			}
			if (fgets(filesecret, sizeof(filesecret), fp) == NULL) {
			       ERROR("Error reading %s: %s", optarg, fr_syserror(errno));
			       exit(EXIT_FAILURE);
			}
			fclose(fp);

			/* truncate newline */
			p = filesecret + strlen(filesecret) - 1;
			while ((p >= filesecret) &&
			      (*p < ' ')) {
			       *p = '\0';
			       --p;
			}

			if (strlen(filesecret) < 2) {
			       ERROR("Secret in %s is too short", optarg);
			       exit(EXIT_FAILURE);
			}
			conf->secret = filesecret;
		}
		       break;

		case 't':
			if (fr_timeval_from_str(&conf->timeout, optarg) < 0) {
				ERROR("Failed parsing timeout value: %s", fr_strerror());
				exit(EXIT_FAILURE);
			}
			break;

		case 'v':
			DEBUG("%s", radsnmp_version);
			exit(0);

		case 'x':
			fr_debug_lvl++;
			break;

		case 'h':
		default:
			usage();
	}
