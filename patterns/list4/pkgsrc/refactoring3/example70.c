switch (artyp) {
#ifdef SUPPORT_RMT
	case ISRMT:
		if ((res = rmtread_with_restart(arfd, buf, cnt)) > 0) {
			io_ok = 1;
			return res;
		}
		break;
#endif /* SUPPORT_RMT */
#ifdef SUPPORT_TAPE
	case ISTAPE:
		if ((res = read_with_restart(arfd, buf, cnt)) > 0) {
			/*
			 * CAUTION: tape systems may not always return the same
			 * sized records so we leave blksz == MAXBLK. The
			 * physical record size that a tape drive supports is
			 * very hard to determine in a uniform and portable
			 * manner.
			 */
			io_ok = 1;
			if (res != rdblksz) {
				/*
				 * Record size changed. If this happens on
				 * any record after the first, we probably have
				 * a tape drive which has a fixed record size
				 * (we are getting multiple records in a single
				 * read). Watch out for record blocking that
				 * violates pax spec (must be a multiple of
				 * BLKMULT).
				 */
				rdblksz = res;
				if (rdblksz % BLKMULT)
					invld_rec = 1;
			}
			return(res);
		}
		break;
#endif /* SUPPORT_TAPE */
	case ISREG:
	case ISBLK:
	case ISCHR:
	case ISPIPE:
	default:
		/*
		 * Files are so easy to deal with. These other things cannot
		 * be trusted at all. So when we are dealing with character
		 * devices and pipes we just take what they have ready for us
		 * and return. Trying to do anything else with them runs the
		 * risk of failure.
		 */
		if ((res = read_with_restart(arfd, buf, cnt)) > 0) {
			io_ok = 1;
			return(res);
		}
		break;
	}
