switch (c) {
		case 'D':
			++debug;
			break;
		case 'a':
			adjust = TRUE;
			break;
		case 'c':
			compare = TRUE;
			break;
		case 'r':
			show = TRUE;
			break;
		case 's':
			hctosys = TRUE;
			break;
		case 'u':
			utc = TRUE;
			break;
		case 'w':
			systohc = TRUE;
			break;
#ifdef __alpha__
		case 'A':
			ARCconsole = TRUE;
			break;
		case 'J':
			Jensen = TRUE;
			break;
		case 'S':
			SRM = TRUE;
			break;
		case 'F':
			funky_toy = TRUE;
			break;
#endif
		case OPT_SET:
			set = TRUE;
			break;
#ifdef __linux__
		case OPT_GETEPOCH:
			getepoch = TRUE;
			break;
		case OPT_SETEPOCH:
			setepoch = TRUE;
			break;
#endif
		case OPT_NOADJFILE:
			noadjfile = TRUE;
			break;
		case OPT_LOCALTIME:
			local_opt = TRUE;	/* --localtime */
			break;
		case OPT_BADYEAR:
			badyear = TRUE;
			break;
		case OPT_DIRECTISA:
			directisa = TRUE;
			break;
		case OPT_TEST:
			testing = TRUE;		/* --test */
			break;
		case OPT_DATE:
			date_opt = optarg;	/* --date */
			break;
		case OPT_EPOCH:
			epoch_option =		/* --epoch */
			    strtoul_or_err(optarg, _("invalid epoch argument"));
			break;
		case OPT_ADJFILE:
			adj_file_name = optarg;	/* --adjfile */
			break;
		case OPT_SYSTZ:
			systz = TRUE;		/* --systz */
			break;
		case OPT_PREDICT_HC:
			predict = TRUE;		/* --predict-hc */
			break;
		case OPT_GET:
			get = TRUE;		/* --get */
			break;
		case OPT_UPDATE:
			update = TRUE;		/* --update-drift */
			break;
#ifdef __linux__
		case 'f':
			rtc_dev_name = optarg;	/* --rtc */
			break;
#endif
		case 'v':			/* --version */
		case 'V':
			out_version();
			return 0;
		case 'h':			/* --help */
		case '?':
		default:
			usage(NULL);
		}
