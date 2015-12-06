switch (c) {
		case '4':
			force_af = AF_INET;
			break;

		case '6':
			force_af = AF_INET6;
			break;

		case 'c':
			if (!isdigit((int) *optarg))
				usage();
			resend_count = atoi(optarg);
			break;

		case 'D':
			dict_dir = optarg;
			break;

		case 'd':
			radius_dir = optarg;
			break;

		case 'f':
		{
			char const *p;
			rc_file_pair_t *files;

			files = talloc(talloc_autofree_context(), rc_file_pair_t);
			if (!files) goto oom;

			p = strchr(optarg, ':');
			if (p) {
				files->packets = talloc_strndup(files, optarg, p - optarg);
				if (!files->packets) goto oom;
				files->filters = p + 1;
			} else {
				files->packets = optarg;
				files->filters = NULL;
			}
			rbtree_insert(filename_tree, (void *) files);
		}
			break;

		case 'F':
			print_filename = true;
			break;

		case 'i':	/* currently broken */
			if (!isdigit((int) *optarg))
				usage();
			last_used_id = atoi(optarg);
			if ((last_used_id < 0) || (last_used_id > 255)) {
				usage();
			}
			break;

		case 'n':
			persec = atoi(optarg);
			if (persec <= 0) usage();
			break;

			/*
			 *	Note that sending MANY requests in
			 *	parallel can over-run the kernel
			 *	queues, and Linux will happily discard
			 *	packets.  So even if the server responds,
			 *	the client may not see the reply.
			 */
		case 'p':
			parallel = atoi(optarg);
			if (parallel <= 0) usage();
			break;

#ifdef WITH_TCP
		case 'P':
			proto = optarg;
			if (strcmp(proto, "tcp") != 0) {
				if (strcmp(proto, "udp") == 0) {
					proto = NULL;
				} else {
					usage();
				}
			} else {
				ipproto = IPPROTO_TCP;
			}
			break;

#endif

		case 'q':
			do_output = false;
			fr_log_fp = NULL; /* no output from you, either! */
			break;

		case 'r':
			if (!isdigit((int) *optarg)) usage();
			retries = atoi(optarg);
			if ((retries == 0) || (retries > 1000)) usage();
			break;

		case 's':
			do_summary = true;
			break;

		case 'S':
		{
			char *p;
			fp = fopen(optarg, "r");
			if (!fp) {
			       ERROR("Error opening %s: %s", optarg, fr_syserror(errno));
			       exit(1);
			}
			if (fgets(filesecret, sizeof(filesecret), fp) == NULL) {
			       ERROR("Error reading %s: %s", optarg, fr_syserror(errno));
			       exit(1);
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
			       exit(1);
			}
			secret = filesecret;
		}
		       break;

		case 't':
			if (!isdigit((int) *optarg))
				usage();
			timeout = atof(optarg);
			break;

		case 'v':
			fr_debug_lvl = 1;
			DEBUG("%s", radclient_version);
			exit(0);

		case 'x':
			fr_debug_lvl++;
			break;

		case 'h':
		default:
			usage();
	}
