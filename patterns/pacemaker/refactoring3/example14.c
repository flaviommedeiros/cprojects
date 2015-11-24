switch (flag) {
            case 'V':
                crm_bump_log_level(argc, argv);
                break;
            case '?':
            case '$':
                crm_help(flag, EX_OK);
                break;
            case 'n':
                attr_name = strdup(optarg);
                break;
            case 's':
                attr_set = strdup(optarg);
                break;
            case 'd':
                attr_dampen = strdup(optarg);
                break;
            case 'l':
            case 'S':
                attr_section = strdup(optarg);
                break;
            case 'N':
                attr_node = strdup(optarg);
                break;
#ifdef HAVE_ATOMIC_ATTRD
            case 'A':
                query_all = TRUE;
            case 'p':
                set_bit(attr_options, attrd_opt_private);
                break;
#endif
            case 'q':
                break;
#ifdef HAVE_ATOMIC_ATTRD
            case 'Q':
#endif
            case 'R':
            case 'D':
            case 'U':
            case 'v':
                command = flag;
                attr_value = optarg;
                crm_log_args(argc, argv); /* Too much? */
                break;
            default:
                ++argerr;
                break;
        }
