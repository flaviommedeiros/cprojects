if (ENABLE_FEATURE_TAR_GNU_EXTENSIONS
#if ULLONG_MAX > 0xffffffffffffffffLL /* 2^64-1 */
		 && (filesize <= 0x3fffffffffffffffffffffffLL)
#endif
		) {
	                /* GNU tar uses "base-256 encoding" for very large numbers.
	                 * Encoding is binary, with highest bit always set as a marker
	                 * and sign in next-highest bit:
	                 * 80 00 .. 00 - zero
	                 * bf ff .. ff - largest positive number
	                 * ff ff .. ff - minus 1
	                 * c0 00 .. 00 - smallest negative number
			 */
			char *p8 = header.size + sizeof(header.size);
			do {
				*--p8 = (uint8_t)filesize;
				filesize >>= 8;
			} while (p8 != header.size);
			*p8 |= 0x80;
		} else {
			bb_error_msg_and_die("can't store file '%s' "
				"of size %"OFF_FMT"u, aborting",
				fileName, statbuf->st_size);
		}
