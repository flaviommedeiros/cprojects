switch(artyp) {
	case ISPIPE:
		if (sksz <= 0)
			break;
		/*
		 * cannot go backwards on these critters
		 */
		tty_warn(1, "Reverse positioning on pipes is not supported.");
		lstrval = -1;
		return -1;
	case ISREG:
	case ISBLK:
	case ISCHR:
	default:
		if (sksz <= 0)
			break;

		/*
		 * For things other than files, backwards movement has a very
		 * high probability of failure as we really do not know the
		 * true attributes of the device we are talking to (the device
		 * may not even have the ability to lseek() in any direction).
		 * First we figure out where we are in the archive.
		 */
		if ((cpos = lseek(arfd, (off_t)0L, SEEK_CUR)) < 0) {
			syswarn(1, errno,
			   "Unable to obtain current archive byte offset");
			lstrval = -1;
			return -1;
		}

		/*
		 * we may try to go backwards past the start when the archive
		 * is only a single record. If this happens and we are on a
		 * multi-volume archive, we need to go to the end of the
		 * previous volume and continue our movement backwards from
		 * there.
		 */
		if ((cpos -= sksz) < (off_t)0L) {
			if (arvol > 1) {
				/*
				 * this should never happen
				 */
				tty_warn(1,
				    "Reverse position on previous volume.");
				lstrval = -1;
				return -1;
			}
			cpos = (off_t)0L;
		}
		if (lseek(arfd, cpos, SEEK_SET) < 0) {
			syswarn(1, errno, "Unable to seek archive backwards");
			lstrval = -1;
			return -1;
		}
		break;
	case ISTAPE:
#ifdef SUPPORT_RMT
	case ISRMT:
#endif /* SUPPORT_RMT */
#ifdef SUPPORT_TAPE
		/*
		 * Calculate and move the proper number of PHYSICAL tape
		 * blocks. If the sksz is not an even multiple of the physical
		 * tape size, we cannot do the move (this should never happen).
		 * (We also cannot handle trailers spread over two vols).
		 * get_phys() also makes sure we are in front of the filemark.
		 */
		if ((phyblk = get_phys()) <= 0) {
			lstrval = -1;
			return -1;
		}

		/*
		 * make sure future tape reads only go by physical tape block
		 * size (set rdblksz to the real size).
		 */
		rdblksz = phyblk;

		/*
		 * if no movement is required, just return (we must be after
		 * get_phys() so the physical blocksize is properly set)
		 */
		if (sksz <= 0)
			break;

		/*
		 * ok we have to move. Make sure the tape drive can do it.
		 */
		if (sksz % phyblk) {
			tty_warn(1,
			    "Tape drive unable to backspace requested amount");
			lstrval = -1;
			return -1;
		}

		/*
		 * move backwards the requested number of bytes
		 */
		mb.mt_op = MTBSR;
		mb.mt_count = sksz/phyblk;
		if (
#ifdef SUPPORT_RMT
		    rmtioctl(arfd, MTIOCTOP, &mb)
#else
		    ioctl(arfd, MTIOCTOP, &mb)
#endif /* SUPPORT_RMT */
		    < 0) {
			syswarn(1, errno, "Unable to backspace tape %ld blocks.",
			    (long) mb.mt_count);
			lstrval = -1;
			return -1;
		}
#else
		tty_warn(1, "System does not have tape support");
#endif /* SUPPORT_TAPE */
		break;
	}
