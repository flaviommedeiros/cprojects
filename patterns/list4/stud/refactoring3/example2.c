switch (c) {
      case 0:
        break;
#ifndef NO_CONFIG_FILE
      case CFG_PARAM_CFGFILE:
        if (!config_file_parse(optarg, cfg))
          config_die("%s", config_error_get());
        break;
      case CFG_PARAM_DEFCFG:
        config_print_default(stdout, cfg);
        exit(0);
        break;
#endif
      case CFG_PARAM_SYSLOG_FACILITY:
        config_param_validate(CFG_SYSLOG_FACILITY, optarg, cfg, NULL, 0);
        break;
      case 'c':
        config_param_validate(CFG_CIPHERS, optarg, cfg, NULL, 0);
        break;
      case 'e':
        config_param_validate(CFG_SSL_ENGINE, optarg, cfg, NULL, 0);
         break;
      case 'O':
        config_param_validate(CFG_PREFER_SERVER_CIPHERS, CFG_BOOL_ON, cfg, NULL, 0);
        break;
      case 'b':
        config_param_validate(CFG_BACKEND, optarg, cfg, NULL, 0);
        break;
      case 'f':
        config_param_validate(CFG_FRONTEND, optarg, cfg, NULL, 0);
        break;
      case 'n':
        config_param_validate(CFG_WORKERS, optarg, cfg, NULL, 0);
        break;
      case 'B':
        config_param_validate(CFG_BACKLOG, optarg, cfg, NULL, 0);
        break;
#ifdef USE_SHARED_CACHE
      case 'C':
        config_param_validate(CFG_SHARED_CACHE, optarg, cfg, NULL, 0);
        break;
      case 'U':
        config_param_validate(CFG_SHARED_CACHE_LISTEN, optarg, cfg, NULL, 0);
        break;
      case 'P':
        config_param_validate(CFG_SHARED_CACHE_PEER, optarg, cfg, NULL, 0);
        break;
      case 'M':
        config_param_validate(CFG_SHARED_CACHE_MCASTIF, optarg, cfg, NULL, 0);
        break;
#endif
      case 'k':
        config_param_validate(CFG_KEEPALIVE, optarg, cfg, NULL, 0);
        break;
      case 'r':
        config_param_validate(CFG_CHROOT, optarg, cfg, NULL, 0);
        break;
      case 'u':
        config_param_validate(CFG_USER, optarg, cfg, NULL, 0);
        break;
      case 'g':
        config_param_validate(CFG_GROUP, optarg, cfg, NULL, 0);
        break;
      case 'q':
        config_param_validate(CFG_QUIET, CFG_BOOL_ON, cfg, NULL, 0);
        break;
      case 's':
        config_param_validate(CFG_SYSLOG, CFG_BOOL_ON, cfg, NULL, 0);
        break;
      case 't':
        test_only = 1;
        break;
      case 'V':
        printf("%s %s\n", basename(argv[0]), STUD_VERSION);
        exit(0);
        break;
      case 'h':
        config_print_usage(argv[0], cfg);
        exit(0);
        break;

      default:
        config_die("Invalid command line parameters. Run %s --help for instructions.", basename(argv[0]));
    }
