#ifdef ASUS_DDNS
while((opt=xgetopt(argc, argv, "A:a:b:c:dDe:fF:h:i:L:m:M:N:o:p:P:qr:R:s:S:t:T:U:u:wHVCZ", long_options, NULL)) != -1)
#else   // !ASUS_DDNS
  while((opt=xgetopt(argc, argv, "a:b:c:dDe:fF:h:i:L:m:M:N:o:p:P:qr:R:s:S:t:T:U:u:wHVCZ", long_options, NULL)) != -1)
#endif  // ASUS_DDNS
  {
    switch (opt)
    {
      case 'a':
        option_handler(CMD_address, optarg);
        break;

//2007.03.14 Yau add
#ifdef ASUS_DDNS
      case 'A':
        option_handler(CMD_asus, optarg);
        break;
#endif  // ASUS_DDNS

      case 'b':
        option_handler(CMD_cache_file, optarg);
        break;

      case 'c':
        if(config_file) { free(config_file); }
        config_file = strdup(optarg);
        dprintf((stderr, "config_file: %s\n", config_file));
        if(config_file)
        {
          if(parse_conf_file(config_file, conf_commands) != 0)
          {
            show_message("error parsing config file \"%s\"\n", config_file);
            exit(1);
          }
        }
        break;

      case 'd':
        option_handler(CMD_daemon, optarg);
        break;

      case 'D':
        option_handler(CMD_debug, optarg);
        break;

      case 'e':
        option_handler(CMD_execute, optarg);
        break;

      case 'f':
        option_handler(CMD_foreground, optarg);
        break;

      case 'F':
        option_handler(CMD_pid_file, optarg);
        break;

      case 'g':
        option_handler(CMD_request, optarg);
        break;

      case 'h':
        option_handler(CMD_host, optarg);
        break;

      case 'i':
        option_handler(CMD_interface, optarg);
        break;

      case 'L':
        option_handler(CMD_cloak_title, optarg);
        break;

      case 'm':
        option_handler(CMD_mx, optarg);
        break;

      case 'M':
        option_handler(CMD_max_interval, optarg);
        break;

#ifdef SEND_EMAIL_CMD
      case 'N':
        option_handler(CMD_notify_email, optarg);
        break;
#endif

      case 'o':
        option_handler(CMD_offline, optarg);
        break;

      case 'p':
        option_handler(CMD_resolv_period, optarg);
        break;

      case 'P':
        option_handler(CMD_period, optarg);
        break;

      case 'q':
        option_handler(CMD_quiet, optarg);
        break;

      case 'Q':
        option_handler(CMD_run_as_euser, optarg);
        break;

      case 'r':
        option_handler(CMD_retrys, optarg);
        break;

      case 'R':
        option_handler(CMD_run_as_user, optarg);
        break;

      case 's':
        option_handler(CMD_server, optarg);
        break;

      case 'S':
        option_handler(CMD_service_type, optarg);
        break;

      case 't':
        option_handler(CMD_timeout, optarg);
        break;

      case 'T':
        option_handler(CMD_connection_type, optarg);
        break;

      case 'u':
        option_handler(CMD_user, optarg);
        break;

      case 'U':
        option_handler(CMD_url, optarg);
        break;

      case 'w':
        option_handler(CMD_wildcard, optarg);
        break;

      case 'H':
        print_usage();
        exit(0);
        break;

      case 'V':
        print_version();
        exit(0);
        break;

      case 'C':
        print_credits();
        exit(0);
        break;

#ifndef EMBED
      case 'Z':
        print_signalhelp();
        exit(0);
        break;
#endif

      case 'z':
        option_handler(CMD_partner, optarg);
        break;

      case '1':
        option_handler(CMD_once, optarg);
        break;

      default:
#ifdef HAVE_GETOPT_LONG
        fprintf(stderr, "Try `%s --help' for more information\n", argv[0]);
#else
        fprintf(stderr, "Try `%s -H' for more information\n", argv[0]);
        fprintf(stderr, "warning: this program was compilied without getopt_long\n");
        fprintf(stderr, "         as such all long options will not work!\n");
#endif
        exit(1);
        break;
    }
  }
