switch (c) {
            case 'h':
                printf("Usage: %s [opts]\n%s", argv[0], help);
                return -1;
            case 'N':
                ext_body       = strdup(optarg);
                break;
            case 'a':
                bind_addr      = strdup(optarg);
                break;
            case 'p':
                bind_port      = atoi(optarg);
                break;
#ifndef EVHTP_DISABLE_EVTHR
            case 't':
                use_threads    = 1;
                break;
            case 'n':
                num_threads    = atoi(optarg);
                break;
#endif
#ifndef EVHTP_DISABLE_SSL
            case 's':
                ssl_pem        = strdup(optarg);
                break;
            case 'c':
                ssl_ca         = strdup(optarg);
                break;
            case 'C':
                ssl_capath     = strdup(optarg);
                break;
#endif
            case 'l':
                bw_limit       = atoll(optarg);
                break;
            case 'm':
                max_keepalives = atoll(optarg);
                break;
            case 'b':
                backlog        = atoll(optarg);
                break;
            default:
                printf("Unknown opt %s\n", optarg);
                return -1;
        }
