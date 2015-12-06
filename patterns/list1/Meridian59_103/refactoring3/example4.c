switch (zip->entry->compression) {
#ifdef HAVE_ZLIB_H
	case 8: /* Deflate compression. */
		while (!zip->end_of_entry) {
			int64_t offset = 0;
			const void *buff = NULL;
			size_t size = 0;
			int r;
			r =  zip_read_data_deflate(a, &buff, &size, &offset);
			if (r != ARCHIVE_OK)
				return (r);
		}
		return ARCHIVE_OK;
#endif
	default: /* Uncompressed or unknown. */
		/* Scan for a PK\007\010 signature. */
		zip_read_consume(a, zip->unconsumed);
		zip->unconsumed = 0;
		for (;;) {
			const char *p, *buff;
			ssize_t bytes_avail;
			buff = __archive_read_ahead(a, 16, &bytes_avail);
			if (bytes_avail < 16) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Truncated ZIP file data");
				return (ARCHIVE_FATAL);
			}
			p = buff;
			while (p <= buff + bytes_avail - 16) {
				if (p[3] == 'P') { p += 3; }
				else if (p[3] == 'K') { p += 2; }
				else if (p[3] == '\007') { p += 1; }
				else if (p[3] == '\010' && p[2] == '\007'
				    && p[1] == 'K' && p[0] == 'P') {
					zip_read_consume(a, p - buff + 16);
					return ARCHIVE_OK;
				} else { p += 4; }
			}
			zip_read_consume(a, p - buff);
		}
	}
