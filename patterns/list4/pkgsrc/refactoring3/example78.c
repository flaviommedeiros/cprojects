switch(c) {
		case 'a':
			/*
			 * preserve access time on filesystem nodes we read
			 */
			tflag = 1;
			flg |= TF;
			break;
#ifdef notyet
		case 'b':
			/*
			 * swap bytes and half-words when reading data
			 */
			break;
#endif
		case 'c':
			/*
			 * ASCII cpio header
			 */
			frmt = &fsub[F_SV4CPIO];
			break;
		case 'd':
			/*
			 * create directories as needed
			 * pax does this by default ..
			 */
			nodirs = 0;
			break;
		case 'f':
			/*
			 * inverse match on patterns
			 */
			cflag = 1;
			flg |= CF;
			break;
		case 'i':
			/*
			 * read the archive
			 */
			act = EXTRACT;
			flg |= RF;
			break;
#ifdef notyet
		case 'k':
			break;
#endif
		case 'l':
			/*
			 * try to link src to dest with copy (-rw)
			 */
			lflag = 1;
			flg |= LF;
			break;
		case 'm':
			/*
			 * preserve mtime
			 */
			flg |= PF;
			pmtime = 1;
			break;
		case 'o':
			/*
			 * write an archive
			 */
			act = ARCHIVE;
			frmt = &(fsub[F_SV4CRC]);
			flg |= WF;
			break;
		case 'p':
			/*
			 * cpio -p is like pax -rw
			 */
			act = COPY;
			flg |= RF | WF;
			break;
		case 'r':
			/*
			 * interactive file rename
			 */
			iflag = 1;
			flg |= IF;
			break;
#ifdef notyet
		case 's':
			/*
			 * swap bytes after reading data
			 */
			break;
#endif
		case 't':
			/*
			 * list contents of archive
			 */
			act = LIST;
			listf = stdout;
			flg &= ~RF;
			break;
		case 'u':
			/*
			 * don't ignore those older files
			 */
			uflag = 0;
			kflag = 0;
			flg |= UF;
			break;
		case 'v':
			/*
			 * verbose operation mode
			 */
			vflag = 1;
			flg |= VF;
			break;
		case 'z':
			/*
			 * use gzip.  Non standard option.
			 */
			gzip_program = GZIP_CMD;
			break;
		case 'A':
			/*
			 * append to an archive
			 */
			act = APPND;
			flg |= AF;
			break;
		case 'B':
			/*
			 * set blocksize to 5120
			 */
			blksz = 5120;
			break;
		case 'C':
			/*
			 * specify blocksize
			 */
			if ((blksz = (int)str_offt(optarg)) <= 0) {
				tty_warn(1, "Invalid block size %s", optarg);
				cpio_usage();
			}
			break;
		case 'E':
			/*
			 * file with patterns to extract or list
			 */
			if ((fp = fopen(optarg, "r")) == NULL) {
				tty_warn(1, "Unable to open file '%s' for read",
				    optarg);
				cpio_usage();
			}
			while ((str = get_line(fp)) != NULL) {
				pat_add(str, NULL);
			}
			fclose(fp);
			if (getline_error) {
				tty_warn(1, "Problem with file '%s'", optarg);
				cpio_usage();
			}
			break;
		case 'H':
			/*
			 * specify an archive format on write
			 */
			tmp.name = optarg;
			frmt = (FSUB *)bsearch((void *)&tmp, (void *)fsub,
			    sizeof(fsub)/sizeof(FSUB), sizeof(FSUB), c_frmt);
			if (frmt != NULL) {
				flg |= XF;
				break;
			}
			tty_warn(1, "Unknown -H format: %s", optarg);
			(void)fputs("cpio: Known -H formats are:", stderr);
			for (i = 0; i < (sizeof(fsub)/sizeof(FSUB)); ++i)
				(void)fprintf(stderr, " %s", fsub[i].name);
			(void)fputs("\n\n", stderr);
			cpio_usage();
			break;
		case 'I':
		case 'O':
			/*
			 * filename where the archive is stored
			 */
			if ((optarg[0] == '-') && (optarg[1]== '\0')) {
				/*
				 * treat a - as stdin
				 */
				arcname = NULL;
				break;
			}
			arcname = optarg;
			break;
		case 'L':
			/*
			 * follow symlinks
			 */
			Lflag = 1;
			flg |= CLF;
			break;
#ifdef notyet
		case 'M':
			arg = optarg;
			break;
		case 'R':
			arg = optarg;
			break;
#endif
		case 'S':
			/*
			 * swap halfwords after reading data
			 */
			cpio_swp_head = 1;
			break;
#ifdef notyet
		case 'V':
			break;
#endif
		case 'Z':
			/*
			 * use compress.  Non standard option.
			 */
			gzip_program = COMPRESS_CMD;
			break;
		case '6':
			/*
			 * process Version 6 cpio format
			 */
			frmt = &(fsub[F_BCPIO]);
		case OPT_FORCE_LOCAL:
			forcelocal = 1;
			break;
		case OPT_INSECURE:
			secure = 0;
			break;

		case OPT_SPARSE:
			/* do nothing; we already generate sparse files */
			break;
		default:
			cpio_usage();
			break;
		}
