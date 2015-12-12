switch (ch) {
		case 'b':
			if (backup_type == none)
				backup_type = numbered_existing;
			if (optarg == NULL)
				break;
			if (verbose)
				say("Warning, the ``-b suffix'' option has been"
				    " obsoleted by the -z option.\n");
			/* FALLTHROUGH */
		case 'z':
			/* must directly follow 'b' case for backwards compat */
			simple_backup_suffix = savestr(optarg);
			break;
		case 'B':
			origprae = savestr(optarg);
			break;
		case 'c':
			diff_type = CONTEXT_DIFF;
			break;
		case 'C':
			check_only = true;
			break;
		case 'd':
			if (chdir(optarg) < 0)
				pfatal("can't cd to %s", optarg);
			break;
		case 'D':
			do_defines = true;
			if (!isalpha((unsigned char)*optarg) && *optarg != '_')
				fatal("argument to -D is not an identifier\n");
			snprintf(if_defined, sizeof if_defined,
			    "#ifdef %s\n", optarg);
			snprintf(not_defined, sizeof not_defined,
			    "#ifndef %s\n", optarg);
			snprintf(end_defined, sizeof end_defined,
			    "#endif /* %s */\n", optarg);
			break;
		case 'e':
			diff_type = ED_DIFF;
			break;
		case 'E':
			remove_empty_files = true;
			break;
		case 'f':
			force = true;
			break;
		case 'F':
			maxfuzz = atoi(optarg);
			break;
		case 'i':
			if (++filec == MAXFILEC)
				fatal("too many file arguments\n");
			filearg[filec] = savestr(optarg);
			break;
		case 'l':
			canonicalize = true;
			break;
		case 'n':
			diff_type = NORMAL_DIFF;
			break;
		case 'N':
			noreverse = true;
			break;
		case 'o':
			outname = savestr(optarg);
			break;
		case 'p':
			strippath = atoi(optarg);
			break;
		case 'r':
			if (strlcpy(rejname, optarg,
			    sizeof(rejname)) >= sizeof(rejname))
				fatal("argument for -r is too long\n");
			break;
		case 'R':
			reverse = true;
			reverse_flag_specified = true;
			break;
		case 's':
			verbose = false;
			break;
		case 't':
			batch = true;
			break;
		case 'u':
			diff_type = UNI_DIFF;
			break;
		case 'v':
			version();
			break;
		case 'V':
			backup_type = get_version(optarg);
			break;
#ifdef DEBUGGING
		case 'x':
			debug = atoi(optarg);
			break;
#endif
		default:
			if (ch != '\0')
				usage();
			break;
		}
