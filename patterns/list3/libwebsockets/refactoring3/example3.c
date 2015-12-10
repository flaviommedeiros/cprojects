switch (n) {
		case 'P':
			strncpy(passphrase, optarg, sizeof(passphrase));
			passphrase[sizeof(passphrase) - 1] = '\0';
			info.ssl_private_key_password = passphrase;
			break;
		case 'C':
			strncpy(ssl_cert, optarg, sizeof(ssl_cert));
			ssl_cert[sizeof(ssl_cert) - 1] = '\0';
			disallow_selfsigned = 1;
			break;
		case 'k':
			strncpy(ssl_key, optarg, sizeof(ssl_key));
			ssl_key[sizeof(ssl_key) - 1] = '\0';
			break;
		case 'u':
			strncpy(uri, optarg, sizeof(uri));
			uri[sizeof(uri) - 1] = '\0';
			break;
			
#ifndef LWS_NO_DAEMONIZE
		case 'D':
			daemonize = 1;
#ifndef _WIN32
			syslog_options &= ~LOG_PERROR;
#endif
			break;
#endif
#ifndef LWS_NO_CLIENT
		case 'c':
			client = 1;
			strncpy(address, optarg, sizeof(address) - 1);
			address[sizeof(address) - 1] = '\0';
			port = 80;
			break;
		case 'r':
			rate_us = atoi(optarg) * 1000;
			break;
#endif
		case 'd':
			debug_level = atoi(optarg);
			break;
		case 's':
			use_ssl = 1; /* 1 = take care about cert verification, 2 = allow anything */
			break;
		case 'p':
			port = atoi(optarg);
			break;
		case 'v':
			versa = 1;
			break;
		case 'i':
			strncpy(interface_name, optarg, sizeof interface_name);
			interface_name[(sizeof interface_name) - 1] = '\0';
