switch(i) {

		case 'B':
			big = atoi(optarg);
			break;

		case 'b':
			buflen = atol(optarg);
			if(buflen > MAXBUF) {
				fprintf(stderr,
					"Buffer (%ld) too big, set to %ld\n",
					buflen, MAXBUF);
				buflen = MAXBUF;
			}
			break;

		case 'e':
			eflag++;
			break;

		case 'F':
			fflag++;
			break;

		case 'f':
			nfiles = atoi(optarg);
			break;

		case 'h':
			hardcopy++;
			break;

		case 'n':
			nrec = atol(optarg);
			break;

		case 'q':
			quiet++;
			break;

		case 's':
			hardcopy = 0;
			break;

#ifdef	MTIO
		case 'R':
			rewindafter++;
			break;

		case 'r':
			rewind++;
			break;

		case 'U':
			unload_err++;
			break;

		case 'u':
			unload++;
			break;
#endif

		case '?':
		default:
			fprintf(stderr, "unknown flag '%c'\n", i);
			exit(1);
		}
