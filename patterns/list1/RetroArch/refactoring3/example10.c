switch (c)
      {
         case 'h':
            print_help(argv[0]);
            exit(0);

         case 'd':
         {
            unsigned id = 0;
            struct string_list *list = string_split(optarg, ":");

            port = 0;

            if (list && list->size == 2)
            {
               port = strtol(list->elems[0].data, NULL, 0);
               id = strtoul(list->elems[1].data, NULL, 0);
            }
            string_list_free(list);

            if (port < 1 || port > MAX_USERS)
            {
               RARCH_ERR("Connect device to a valid port.\n");
               print_help(argv[0]);
               retro_fail(1, "parse_input()");
            }
            settings->input.libretro_device[port - 1] = id;
            global->has_set.libretro_device[port - 1] = true;
            break;
         }

         case 'A':
            port = strtol(optarg, NULL, 0);
            if (port < 1 || port > MAX_USERS)
            {
               RARCH_ERR("Connect dualanalog to a valid port.\n");
               print_help(argv[0]);
               retro_fail(1, "parse_input()");
            }
            settings->input.libretro_device[port - 1] = RETRO_DEVICE_ANALOG;
            global->has_set.libretro_device[port - 1] = true;
            break;

         case 's':
            strlcpy(global->name.savefile, optarg,
                  sizeof(global->name.savefile));
            global->has_set.save_path = true;
            break;

         case 'f':
            global->force_fullscreen = true;
            break;

         case 'S':
            strlcpy(global->name.savestate, optarg,
                  sizeof(global->name.savestate));
            global->has_set.state_path = true;
            break;

         case 'v':
            {
               bool *verbosity = retro_main_verbosity();
               if (verbosity)
                  *verbosity = true;
               global->has_set.verbosity = true;
            }
            break;

         case 'N':
            port = strtol(optarg, NULL, 0);
            if (port < 1 || port > MAX_USERS)
            {
               RARCH_ERR("Disconnect device from a valid port.\n");
               print_help(argv[0]);
               retro_fail(1, "parse_input()");
            }
            settings->input.libretro_device[port - 1] = RETRO_DEVICE_NONE;
            global->has_set.libretro_device[port - 1] = true;
            break;

         case 'c':
            strlcpy(global->path.config, optarg,
                  sizeof(global->path.config));
            break;

         case 'r':
            strlcpy(global->record.path, optarg,
                  sizeof(global->record.path));
            {
               bool *recording_enabled = recording_is_enabled();

               if (recording_enabled)
                  *recording_enabled = true;
            }
            break;

#ifdef HAVE_DYNAMIC
         case 'L':
            if (path_is_directory(optarg))
            {
               *settings->libretro = '\0';
               strlcpy(settings->libretro_directory, optarg,
                     sizeof(settings->libretro_directory));
               global->has_set.libretro = true;
               global->has_set.libretro_directory = true;
               RARCH_WARN("Using old --libretro behavior. Setting libretro_directory to \"%s\" instead.\n", optarg);
            }
            else
            {
               rarch_main_ctl(RARCH_MAIN_CTL_SET_LIBRETRO_PATH, optarg);
               global->has_set.libretro = true;
            }
            break;
#endif
         case 'P':
         case 'R':
            strlcpy(global->bsv.movie_start_path, optarg,
                  sizeof(global->bsv.movie_start_path));
            global->bsv.movie_start_playback  = (c == 'P');
            global->bsv.movie_start_recording = (c == 'R');
            break;

         case 'M':
            if (!strcmp(optarg, "noload-nosave"))
            {
               global->sram.load_disable = true;
               global->sram.save_disable = true;
            }
            else if (!strcmp(optarg, "noload-save"))
               global->sram.load_disable = true;
            else if (!strcmp(optarg, "load-nosave"))
               global->sram.save_disable = true;
            else if (strcmp(optarg, "load-save") != 0)
            {
               RARCH_ERR("Invalid argument in --sram-mode.\n");
               print_help(argv[0]);
               retro_fail(1, "parse_input()");
            }
            break;

#ifdef HAVE_NETPLAY
         case 'H':
            global->has_set.netplay_ip_address = true;
            global->netplay.enable = true;
            *global->netplay.server = '\0';
            break;

         case 'C':
            global->has_set.netplay_ip_address = true;
            global->netplay.enable = true;
            strlcpy(global->netplay.server, optarg,
                  sizeof(global->netplay.server));
            break;

         case 'F':
            global->netplay.sync_frames = strtol(optarg, NULL, 0);
            global->has_set.netplay_delay_frames = true;
            break;
#endif

         case RA_OPT_BPS:
            strlcpy(global->name.bps, optarg,
                  sizeof(global->name.bps));
            global->patch.bps_pref   = true;
            global->has_set.bps_pref = true;
            break;

         case 'U':
            strlcpy(global->name.ups, optarg,
                  sizeof(global->name.ups));
            global->patch.ups_pref   = true;
            global->has_set.ups_pref = true;
            break;

         case RA_OPT_IPS:
            strlcpy(global->name.ips, optarg,
                  sizeof(global->name.ips));
            global->patch.ips_pref   = true;
            global->has_set.ips_pref = true;
            break;

         case RA_OPT_NO_PATCH:
            global->patch.block_patch = true;
            break;

         case 'D':
#if defined(_WIN32) && !defined(_XBOX)
            FreeConsole();
#endif
            break;

         case RA_OPT_MENU:
            global->inited.core.type        = CORE_TYPE_DUMMY;
            break;

#ifdef HAVE_NETPLAY
         case RA_OPT_PORT:
            global->has_set.netplay_ip_port = true;
            global->netplay.port = strtoul(optarg, NULL, 0);
            break;

         case RA_OPT_SPECTATE:
            global->has_set.netplay_mode = true;
            global->netplay.is_spectate = true;
            break;

#endif
         case RA_OPT_NICK:
            global->has_set.username = true;
            strlcpy(settings->username, optarg,
                  sizeof(settings->username));
            break;

#if defined(HAVE_NETWORK_CMD) && defined(HAVE_NETPLAY)
         case RA_OPT_COMMAND:
            if (network_cmd_send(optarg))
               exit(0);
            else
               retro_fail(1, "network_cmd_send()");
            break;
#endif

         case RA_OPT_APPENDCONFIG:
            strlcpy(global->path.append_config, optarg,
                  sizeof(global->path.append_config));
            break;

         case RA_OPT_SIZE:
         {
            if (sscanf(optarg, "%ux%u", &global->record.width,
                     &global->record.height) != 2)
            {
               RARCH_ERR("Wrong format for --size.\n");
               print_help(argv[0]);
               retro_fail(1, "parse_input()");
            }
            break;
         }

         case RA_OPT_RECORDCONFIG:
            strlcpy(global->record.config, optarg,
                  sizeof(global->record.config));
            break;

         case RA_OPT_MAX_FRAMES:
            {
               unsigned max_frames = strtoul(optarg, NULL, 10);
               rarch_main_ctl(RARCH_MAIN_CTL_SET_MAX_FRAMES, &max_frames);
            }
            break;

         case RA_OPT_SUBSYSTEM:
            strlcpy(global->subsystem, optarg, sizeof(global->subsystem));
            break;

         case RA_OPT_FEATURES:
            print_features();
            exit(0);

         case RA_OPT_EOF_EXIT:
            global->bsv.eof_exit = true;
            break;

         case RA_OPT_VERSION:
            print_version();
            exit(0);

#ifdef HAVE_FILE_LOGGER
         case RA_OPT_LOG_FILE:
            global->log_file = fopen(optarg, "wb");
            break;
#endif

         case '?':
            print_help(argv[0]);
            retro_fail(1, "parse_input()");

         default:
            RARCH_ERR("Error parsing arguments.\n");
            retro_fail(1, "parse_input()");
      }
