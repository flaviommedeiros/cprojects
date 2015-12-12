switch(c) {
		case 'b':
			/*
			 * specify blocksize in 512-byte blocks
			 */
			if ((wrblksz = (int)str_offt(optarg)) <= 0) {
				tty_warn(1, "Invalid block size %s", optarg);
				tar_usage();
			}
			wrblksz *= 512;		/* XXX - check for int oflow */
			break;
		case 'c':
			/*
			 * create an archive
			 */
			act = ARCHIVE;
			break;
		case 'e':
			/*
			 * stop after first error
			 */
			maxflt = 0;
			break;
		case 'f':
			/*
			 * filename where the archive is stored
			 */
			if ((optarg[0] == '-') && (optarg[1]== '\0')) {
				/*
				 * treat a - as stdin
				 */
				fstdin = 1;
				arcname = NULL;
				break;
			}
			fstdin = 0;
			arcname = optarg;
			break;
		case 'h':
			/*
			 * follow symlinks
			 */
			Lflag = 1;
			break;
		case 'j':
			/*
			 * pass through bzip2. not a standard option
			 */
			jflag = 1;
			gzip_program = BZIP2_CMD;
			break;
		case 'k':
			/*
			 * do not clobber files that exist
			 */
			kflag = 1;
			break;
		case 'l':
			/*
			 * do not pass over mount points in the file system
			 */
			Xflag = 1;
			break;
		case 'm':
			/*
			 * do not preserve modification time
			 */
			pmtime = 0;
			break;
		case 'o':
			/*
			 * This option does several things based on whether
			 * this is a create or extract operation.
			 */
			if (act == ARCHIVE) {
				/* GNU tar: write V7 format archives. */
				Oflag = 1;
				/* 4.2BSD: don't add directory entries. */
				if (opt_add("write_opt=nodir") < 0)
					tar_usage();

			} else {
				/* SUS: don't preserve owner/group. */
				pids = 0;
				nopids = 1;
			}
			break;
		case 'O':
			Oflag = 1;
			break;
		case 'p':
			/*
			 * preserve user id, group id, file
			 * mode, access/modification times
			 */
			if (!nopids)
				pids = 1;
			pmode = 1;
			patime = 1;
			pmtime = 1;
			break;
		case 'q':
			/*
			 * select first match for a pattern only
			 */
			nflag = 1;
			break;
		case 'r':
		case 'u':
			/*
			 * append to the archive
			 */
			act = APPND;
			break;
		case 's':
			/*
			 * file name substitution name pattern
			 */
			if (rep_add(optarg) < 0) {
				tar_usage();
				break;
			}
			break;
		case 't':
			/*
			 * list contents of the tape
			 */
			act = LIST;
			break;
		case 'v':
			/*
			 * verbose operation mode
			 */
			vflag = 1;
			break;
		case 'w':
			/*
			 * interactive file rename
			 */
			iflag = 1;
			break;
		case 'x':
			/*
			 * extract an archive, preserving mode,
			 * and mtime if possible.
			 */
			act = EXTRACT;
			pmtime = 1;
			break;
		case 'z':
			/*
			 * use gzip.  Non standard option.
			 */
			zflag = 1;
			gzip_program = GZIP_CMD;
			break;
		case 'B':
			/*
			 * Nothing to do here, this is pax default
			 */
			break;
		case 'C':
			chdname = optarg;
			break;
		case 'H':
			/*
			 * follow command line symlinks only
			 */
			Hflag = 1;
			break;
		case 'I':
		case 'T':
			if (++nincfiles > incfiles_max) {
				incfiles_max = nincfiles + 3;
				incfiles = realloc(incfiles,
				    sizeof(*incfiles) * incfiles_max);
				if (incfiles == NULL) {
					tty_warn(0, "Unable to allocate space "
					    "for option list");
					exit(1);
				}
			}
			incfiles[nincfiles - 1].file = optarg;
			incfiles[nincfiles - 1].dir = chdname;
			break;
		case 'P':
			/*
			 * do not remove leading '/' from pathnames
			 */
			rmleadslash = 0;
			Aflag = 1;
			break;
		case 'S':
			/* do nothing; we already generate sparse files */
			break;
		case 'X':
			/*
			 * GNU tar compat: exclude the files listed in optarg
			 */
			if (tar_gnutar_X_compat(optarg) != 0)
				tar_usage();
			break;
		case 'Z':
			/*
			 * use compress.
			 */
			zflag = 1;
			gzip_program = COMPRESS_CMD;
			break;
		case '0':
			arcname = DEV_0;
			break;
		case '1':
			arcname = DEV_1;
			break;
		case '4':
			arcname = DEV_4;
			break;
		case '5':
			arcname = DEV_5;
			break;
		case '7':
			arcname = DEV_7;
			break;
		case '8':
			arcname = DEV_8;
			break;
		case OPT_ATIME_PRESERVE:
			patime = 1;
			break;
		case OPT_UNLINK:
			/* Just ignore -- we always unlink first. */
			break;
		case OPT_USE_COMPRESS_PROGRAM:
			zflag = 1;
			gzip_program = optarg;
			break;
		case OPT_FORCE_LOCAL:
			forcelocal = 1;
			break;
		case OPT_INSECURE:
			secure = 0;
			break;
		case OPT_STRICT:
			/* disable gnu extensions */
			is_gnutar = 0;
			break;
		case OPT_EXCLUDE:
			if (tar_gnutar_minus_minus_exclude(optarg) != 0)
				tar_usage();
			break;
		case OPT_NORECURSE:
			dflag = 1;
			break;
#if !HAVE_NBTOOL_CONFIG_H
#ifdef HAVE_FCHROOT
		case OPT_CHROOT:
			do_chroot = 1;
			break;
#endif /* HAVE_FCHROOT */
#endif
		default:
			tar_usage();
			break;
		}
