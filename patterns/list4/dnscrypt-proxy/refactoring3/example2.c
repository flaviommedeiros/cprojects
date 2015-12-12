switch (opt_flag) {
        case 'a':
            proxy_context->local_ip = optarg;
            break;
        case 'd':
            proxy_context->daemonize = 1;
            break;
        case 'e': {
            char *endptr;
            const unsigned long edns_payload_size = strtoul(optarg, &endptr, 10);

            if (*optarg == 0 || *endptr != 0 ||
                edns_payload_size > DNS_MAX_PACKET_SIZE_UDP_RECV) {
                logger(proxy_context, LOG_ERR,
                       "Invalid EDNS payload size: [%s]", optarg);
                exit(1);
            }
            if (edns_payload_size <= DNS_MAX_PACKET_SIZE_UDP_NO_EDNS_SEND) {
                proxy_context->edns_payload_size = (size_t) 0U;
                proxy_context->udp_max_size = DNS_MAX_PACKET_SIZE_UDP_NO_EDNS_SEND;
            } else {
                proxy_context->edns_payload_size = (size_t) edns_payload_size;
                assert(proxy_context->udp_max_size >=
                       DNS_MAX_PACKET_SIZE_UDP_NO_EDNS_SEND);
                if (proxy_context->edns_payload_size > DNS_MAX_PACKET_SIZE_UDP_NO_EDNS_SEND) {
                    proxy_context->udp_max_size =
                        proxy_context->edns_payload_size;
                }
            }
            break;
        }
        case 'E':
            proxy_context->ephemeral_keys = 1;
            break;
        case 'h':
            options_usage();
            exit(0);
        case 'k':
            proxy_context->provider_publickey_s = optarg;
            break;
        case 'K':
            proxy_context->client_key_file = optarg;
            break;
        case 'l':
            proxy_context->log_file = optarg;
            break;
        case 'L':
            proxy_context->resolvers_list = optarg;
            break;
        case 'R':
            proxy_context->resolver_name = optarg;
            break;
        case 'S':
            proxy_context->syslog = 1;
            break;
        case 'm': {
            char *endptr;
            const long max_log_level = strtol(optarg, &endptr, 10);

            if (*optarg == 0 || *endptr != 0 || max_log_level < 0) {
                logger(proxy_context, LOG_ERR,
                       "Invalid max log level: [%s]", optarg);
                exit(1);
            }
            proxy_context->max_log_level = max_log_level;
            break;
        }
        case 'n': {
            char *endptr;
            const unsigned long connections_count_max =
                strtoul(optarg, &endptr, 10);

            if (*optarg == 0 || *endptr != 0 ||
                connections_count_max <= 0U ||
                connections_count_max > UINT_MAX) {
                logger(proxy_context, LOG_ERR,
                       "Invalid max number of active request: [%s]", optarg);
                exit(1);
            }
            proxy_context->connections_count_max =
                (unsigned int) connections_count_max;
            break;
        }
        case 'p':
            proxy_context->pid_file = optarg;
            break;
        case 'r':
            proxy_context->resolver_ip = optarg;
            break;
        case 't': {
            char *endptr;
            const unsigned long margin =
                strtoul(optarg, &endptr, 10);

            if (*optarg == 0 || *endptr != 0 ||
                margin > UINT32_MAX / 60U) {
                logger(proxy_context, LOG_ERR,
                       "Invalid certificate grace period: [%s]", optarg);
                exit(1);
            }
            proxy_context->test_cert_margin = (time_t) margin * (time_t) 60U;
            proxy_context->test_only = 1;
            break;
        }
#ifdef HAVE_GETPWNAM
        case 'u': {
            const struct passwd * const pw = getpwnam(optarg);
            if (pw == NULL) {
                logger(proxy_context, LOG_ERR, "Unknown user: [%s]", optarg);
                exit(1);
            }
            proxy_context->user_id = pw->pw_uid;
            proxy_context->user_group = pw->pw_gid;
            proxy_context->user_dir = strdup(pw->pw_dir);
            break;
        }
#endif
        case 'N':
            proxy_context->provider_name = optarg;
            break;
        case 'T':
            proxy_context->tcp_only = 1;
            break;
        case 'V':
            options_version();
            exit(0);
        case 'X':
#ifndef PLUGINS
            logger_noformat(proxy_context, LOG_ERR,
                            "Support for plugins hasn't been compiled in");
            exit(1);
#else
            if (plugin_options_parse_str
                (proxy_context->app_context->dcps_context, optarg) != 0) {
                logger_noformat(proxy_context, LOG_ERR,
                                "Error while parsing plugin options");
                exit(2);
            }
#endif
            break;
#ifdef _WIN32
        case WIN_OPTION_INSTALL:
        case WIN_OPTION_REINSTALL:
            option_install = 1;
            break;
        case WIN_OPTION_UNINSTALL:
            if (windows_service_uninstall() != 0) {
                logger_noformat(NULL, LOG_ERR, "Unable to uninstall the service");
                exit(1);
            } else {
                logger_noformat(NULL, LOG_INFO, "The " WINDOWS_SERVICE_NAME
                                " service has been removed from this system");
                exit(0);
            }
            break;
#endif
        default:
            options_usage();
            exit(1);
        }
