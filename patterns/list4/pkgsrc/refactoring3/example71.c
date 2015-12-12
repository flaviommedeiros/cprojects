switch (artyp) {
	case ISREG:
		if ((res > 0) && (res % BLKMULT)) {
			/*
			 * try to fix up partial writes which are not BLKMULT
			 * in size by forcing the runt record to next archive
			 * volume
			 */
			if ((cpos = lseek(arfd, (off_t)0L, SEEK_CUR)) < 0)
				break;
			cpos -= (off_t)res;
			if (ftruncate(arfd, cpos) < 0)
				break;
			res = lstrval = 0;
			break;
		}
		if (res >= 0)
			break;
		/*
		 * if file is out of space, handle it like a return of 0
		 */
		if ((errno == ENOSPC) || (errno == EFBIG))
			res = lstrval = 0;
#ifdef EDQUOT
		if (errno == EDQUOT)
			res = lstrval = 0;
#endif
		break;
#ifdef SUPPORT_TAPE
	case ISTAPE:
#endif /* SUPPORT_TAPE */
	case ISCHR:
	case ISBLK:
#ifdef SUPPORT_RMT
	case ISRMT:
#endif /* SUPPORT_RMT */
		if (res >= 0)
			break;
		if (errno == EACCES) {
			tty_warn(0,
			    "Write failed, archive is write protected.");
			res = lstrval = 0;
			return 0;
		}
		/*
		 * see if we reached the end of media, if so force a change to
		 * the next volume
		 */
		if ((errno == ENOSPC) || (errno == EIO) || (errno == ENXIO))
			res = lstrval = 0;
		break;
	case ISPIPE:
	default:
		/*
		 * we cannot fix errors to these devices
		 */
		break;
	}
