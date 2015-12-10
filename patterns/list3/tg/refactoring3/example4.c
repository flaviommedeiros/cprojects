switch (opt) {
    case 'b':
      bot_mode ++;
      if (optarg) {
        bot_hash = optarg;
      }
      break;
    case 1000:
      tgl_allocator = &tgl_allocator_debug;
      break;
    case 1001:
      accept_any_tcp = 1;
      break;
    case 'u':
      set_default_username (optarg);
      break;
    case 'k':
      //rsa_public_key_name = tstrdup (optarg);
      tgl_set_rsa_key (TLS, optarg);
      break;
    case 'v':
      tgl_incr_verbosity (TLS);
      verbosity ++;
      break;
    case 'N':
      msg_num_mode ++;
      break;
#ifdef HAVE_LIBCONFIG
    case 'c':
      config_filename = tstrdup (optarg);
      break;
    case 'p':
      prefix = optarg;
      assert (strlen (prefix) <= 100);
      break;
#else
    case 'B':
      binlog_enabled = 1;
      break;
#endif
    case 'l':
      log_level = atoi (optarg);
      break;
    case 'f':
      sync_from_start = 1;
      break;
    case 'E':
      disable_auto_accept = 1;
      break;
    case 'w':
      allow_weak_random = 1;
      break;
#ifdef USE_LUA
    case 's':
      lua_file = strdup (optarg);
      break;
#endif
    case 'W':
      wait_dialog_list = 1;
      break;
#ifdef USE_PYTHON
    case 'Z':
      python_file = strdup (optarg);
      break;
#endif
    case 'C':
      disable_colors ++;
      break;
    case 'R':
      readline_disabled ++;
      break;
    case 'A':
      alert_sound = 1;
      break;
    case 'd':
      daemonize ++;
      break;
    case 'L':
      logname = optarg;
      break;
    case 'U':
      set_user_name = optarg;
      break;
    case 'G':
      set_group_name = optarg;
      break;
    case 'D':
      disable_output ++;
      break;
    case 'q':
      reset_authorization ++;
      break;
    case 'P':
      port = atoi (optarg);
      break;
    case 'S':
      unix_socket = optarg;
      break;
    case 'e':
      start_command = optarg;
      break;
    case 'I':
      use_ids ++;
      break;
    case '6':
      ipv6_enabled = 1;
      break;
    case 1002:
      disable_link_preview = 2;
      break;
    case 1003:
      enable_json = 1;
      break;
    case 'h':
    default:
      usage ();
      break;
    }
