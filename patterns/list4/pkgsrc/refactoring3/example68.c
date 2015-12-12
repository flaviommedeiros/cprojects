switch(artyp) {
#ifdef SUPPORT_TAPE
	case ISTAPE:
		/*
		 * Tape drives come in at least two flavors. Those that support
		 * variable sized records and those that have fixed sized
		 * records. They must be treated differently. For tape drives
		 * that support variable sized records, we must make large
		 * reads to make sure we get the entire record, otherwise we
		 * will just get the first part of the record (up to size we
		 * asked). Tapes with fixed sized records may or may not return
		 * multiple records in a single read. We really do not care
		 * what the physical record size is UNLESS we are going to
		 * append. (We will need the physical block size to rewrite
		 * the trailer). Only when we are appending do we go to the
		 * effort to figure out the true PHYSICAL record size.
		 */
		blksz = rdblksz = MAXBLK;
		break;
#endif /* SUPPORT_TAPE */
	case ISPIPE:
	case ISBLK:
	case ISCHR:
		/*
		 * Blocksize is not a major issue with these devices (but must
		 * be kept a multiple of 512). If the user specified a write
		 * block size, we use that to read. Under append, we must
		 * always keep blksz == rdblksz. Otherwise we go ahead and use
		 * the device optimal blocksize as (and if) returned by stat
		 * and if it is within pax specs.
		 */
		if ((act == APPND) && wrblksz) {
			blksz = rdblksz = wrblksz;
			break;
		}

		if ((arsb.st_blksize > 0) && (arsb.st_blksize < MAXBLK) &&
		    ((arsb.st_blksize % BLKMULT) == 0))
			rdblksz = arsb.st_blksize;
		else
			rdblksz = DEVBLK;
		/*
		 * For performance go for large reads when we can without harm
		 */
		if ((act == APPND) || (artyp == ISCHR))
			blksz = rdblksz;
		else
			blksz = MAXBLK;
		break;
	case ISREG:
		/*
		 * if the user specified wrblksz works, use it. Under appends
		 * we must always keep blksz == rdblksz
		 */
		if ((act == APPND) && wrblksz && ((arsb.st_size%wrblksz)==0)){
			blksz = rdblksz = wrblksz;
			break;
		}
		/*
		 * See if we can find the blocking factor from the file size
		 */
		for (rdblksz = MAXBLK; rdblksz > 0; rdblksz -= BLKMULT)
			if ((arsb.st_size % rdblksz) == 0)
				break;
		/*
		 * When we cannot find a match, we may have a flawed archive.
		 */
		if (rdblksz <= 0)
			rdblksz = FILEBLK;
		/*
		 * for performance go for large reads when we can
		 */
		if (act == APPND)
			blksz = rdblksz;
		else
			blksz = MAXBLK;
		break;
	default:
		/*
		 * should never happen, worst case, slow...
		 */
		blksz = rdblksz = BLKMULT;
		break;
	}
