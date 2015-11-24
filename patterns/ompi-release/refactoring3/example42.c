switch (c) {
		case 'p':
			if (i+1 >= argc || !argv[i+1]) {
				fprintf(stderr, "Missing port\n");
				exit(1);
			}
			port = (int)strtol(argv[i+1], &endptr, 10);
			if (*endptr != '\0') {
				fprintf(stderr, "Bad port\n");
				exit(1);
			}
			break;
		case 'l':
			if (i+1 >= argc || !argv[i+1]) {
				fprintf(stderr, "Missing content length\n");
				exit(1);
			}
			content_len = (size_t)strtol(argv[i+1], &endptr, 10);
			if (*endptr != '\0' || content_len == 0) {
				fprintf(stderr, "Bad content length\n");
				exit(1);
			}
			break;
#ifdef WIN32
		case 'i':
			use_iocp = 1;
			evthread_use_windows_threads();
			event_config_set_flag(cfg,EVENT_BASE_FLAG_STARTUP_IOCP);
			break;
#endif
		default:
			fprintf(stderr, "Illegal argument \"%c\"\n", c);
			exit(1);
		}
