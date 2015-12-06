switch (*option)
	{
		case '?':
			processHelpOption ("?", NULL);
			exit (0);
			break;
		case 'a':
			checkOptionOrder (option, FALSE);
			Option.append = TRUE;
			break;
#ifdef DEBUG
		case 'b':
			if (atol (parameter) < 0)
				error (FATAL, "-%s: Invalid line number", option);
			Option.breakLine = atol (parameter);
			break;
		case 'D':
			Option.debugLevel = strtol (parameter, NULL, 0);
			if (debug (DEBUG_STATUS))
				Option.verbose = TRUE;
			break;
#endif
		case 'B':
			Option.backward = TRUE;
			break;
		case 'e':
			checkOptionOrder (option, FALSE);
			setEtagsMode ();
			break;
		case 'f':
		case 'o':
			checkOptionOrder (option, FALSE);
			if (Option.tagFileName != NULL)
			{
				error (WARNING,
					"-%s option specified more than once, last value used",
					option);
				freeString (&Option.tagFileName);
			}
			else if (parameter [0] == '-'  &&  parameter [1] != '\0')
				error (FATAL, "output file name may not begin with a '-'");
			Option.tagFileName = stringCopy (parameter);
			break;
		case 'F':
			Option.backward = FALSE;
			break;
		case 'G':
			Option.guessLanguageEagerly = TRUE;
			break;
		case 'h':
			processHeaderListOption (*option, parameter);
			break;
		case 'I':
			processIgnoreOption (parameter);
			break;
		case 'L':
			if (Option.fileList != NULL)
			{
				error (WARNING,
					"-%s option specified more than once, last value used",
					option);
				freeString (&Option.fileList);
			}
			Option.fileList = stringCopy (parameter);
			break;
		case 'n':
			Option.locate = EX_LINENUM;
			break;
		case 'N':
			Option.locate = EX_PATTERN;
			break;
		case 'R':
#ifdef RECURSE_SUPPORTED
			Option.recurse = TRUE;
#else
			error (WARNING, "-%s option not supported on this host", option);
#endif
			break;
		case 'u':
			checkOptionOrder (option, FALSE);
			Option.sorted = SO_UNSORTED;
			break;
		case 'V':
			Option.verbose = TRUE;
			break;
		case 'w':
			/* silently ignored */
			break;
		case 'x':
			checkOptionOrder (option, FALSE);
			Option.xref = TRUE;
			break;
		default:
			error (FATAL, "Unknown option: -%s", option);
			break;
	}
