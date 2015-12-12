switch(artyp) {
#ifdef SUPPORT_RMT
	case ISRMT:
#endif /* SUPPORT_RMT */
	case ISTAPE:
#ifdef SUPPORT_TAPE
		/*
		 * if the last i/o was a successful data transfer, we assume
		 * the fault is just a bad record on the tape that we are now
		 * past. If we did not get any data since the last resync try
		 * to move the tape forward one PHYSICAL record past any
		 * damaged tape section. Some tape drives are stubborn and need
		 * to be pushed.
		 */
		if (io_ok) {
			io_ok = 0;
			lstrval = 1;
			break;
		}
		mb.mt_op = MTFSR;
		mb.mt_count = 1;
#ifdef SUPPORT_RMT
		if (artyp == ISRMT) {
			if (rmtioctl(arfd, MTIOCTOP, &mb) < 0)
				break;
		} else {
#endif /* SUPPORT_RMT */
			if (ioctl(arfd, MTIOCTOP, &mb) < 0)
				break;
#ifdef SUPPORT_RMT
		}
#endif /* SUPPORT_RMT */
		lstrval = 1;
#else
		tty_warn(1, "System does not have tape support");
#endif /* SUPPORT_TAPE */
		break;
	case ISREG:
	case ISCHR:
	case ISBLK:
		/*
		 * try to step over the bad part of the device.
		 */
		io_ok = 0;
		if (((fsbz = arsb.st_blksize) <= 0) || (artyp != ISREG))
			fsbz = BLKMULT;
		if ((cpos = lseek(arfd, (off_t)0L, SEEK_CUR)) < 0)
			break;
		mpos = fsbz - (cpos % (off_t)fsbz);
		if (lseek(arfd, mpos, SEEK_CUR) < 0)
			break;
		lstrval = 1;
		break;
	case ISPIPE:
	default:
		/*
		 * cannot recover on these archive device types
		 */
		io_ok = 0;
		break;
	}
