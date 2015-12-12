switch((char)ch) {
		case 'a':
			afterinstallcmd = strdup(optarg);
			if (afterinstallcmd == NULL)
				errx(1, "%s", strerror(ENOMEM));
			break;
		case 'B':
			suffix = optarg;
			numberedbackup = 0;
			{
				/* Check if given suffix really generates
				   different suffixes - catch e.g. ".%" */
				char suffix_expanded0[FILENAME_MAX],
				     suffix_expanded1[FILENAME_MAX];
				(void)snprintf(suffix_expanded0, FILENAME_MAX,
					       suffix, 0);
				(void)snprintf(suffix_expanded1, FILENAME_MAX,
					       suffix, 1);
				if (strcmp(suffix_expanded0, suffix_expanded1)
				    != 0)
					numberedbackup = 1;
			}
			/* fall through; -B implies -b */
			/*FALLTHROUGH*/
		case 'b':
			dobackup = 1;
			break;
		case 'c':
			/* ignored; was "docopy" which is now the default. */
			break;
		case 'd':
			dodir = 1;
			break;
		case 'D':
			destdir = optarg;
			break;
#if SUPPORT_FLAGS
		case 'f':
			haveopt_f = 1;
			fflags = optarg;
			break;
#endif
		case 'g':
			haveopt_g = 1;
			group = optarg;
			break;
		case 'h':
			digest = optarg;
			break;
		case 'l':
			for (p = optarg; *p; p++)
				switch (*p) {
				case 's':
					dolink &= ~(LN_HARD|LN_MIXED);
					dolink |= LN_SYMBOLIC;
					break;
				case 'h':
					dolink &= ~(LN_SYMBOLIC|LN_MIXED);
					dolink |= LN_HARD;
					break;
				case 'm':
					dolink &= ~(LN_SYMBOLIC|LN_HARD);
					dolink |= LN_MIXED;
					break;
				case 'a':
					dolink &= ~LN_RELATIVE;
					dolink |= LN_ABSOLUTE;
					break;
				case 'r':
					dolink &= ~LN_ABSOLUTE;
					dolink |= LN_RELATIVE;
					break;
				default:
					errx(1, "%c: invalid link type", *p);
					/* NOTREACHED */
				}
			break;
		case 'm':
			haveopt_m = 1;
			if (!(set = setmode(optarg)))
				err(1, "Cannot set file mode `%s'", optarg);
			mode = getmode(set, 0);
			free(set);
			break;
#ifdef SUPPORT_MTREE
		case 'M':
			metafile = optarg;
			break;
		case 'N':
			if (! setup_getid(optarg))
				errx(1,
			    "Unable to use user and group databases in `%s'",
				    optarg);
			break;
#endif
		case 'o':
			haveopt_o = 1;
			owner = optarg;
			break;
		case 'p':
			dopreserve = 1;
			break;
		case 'r':
			dorename = 1;
			break;
		case 'S':
			stripArgs = strdup(optarg);
			if (stripArgs == NULL)
				errx(1, "%s", strerror(ENOMEM));
			/* fall through; -S implies -s */
			/*FALLTHROUGH*/
		case 's':
			dostrip = 1;
			break;
		case 'T':
			tags = optarg;
			break;
		case 'U':
			dounpriv = 1;
			break;
		case '?':
		default:
			usage();
		}
