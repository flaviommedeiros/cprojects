switch (l->compression) {
	case COMPRESSION_STORE:
		/* Setting compressed and uncompressed sizes even when
		 * specification says to set to zero when using data
		 * descriptors. Otherwise the end of the data for an
		 * entry is rather difficult to find. */
		archive_le32enc(&h[LOCAL_FILE_HEADER_COMPRESSED_SIZE],
		    (uint32_t)size);
		archive_le32enc(&h[LOCAL_FILE_HEADER_UNCOMPRESSED_SIZE],
		    (uint32_t)size);
		break;
#ifdef HAVE_ZLIB_H
	case COMPRESSION_DEFLATE:
		archive_le32enc(&h[LOCAL_FILE_HEADER_UNCOMPRESSED_SIZE],
		    (uint32_t)size);

		zip->stream.zalloc = Z_NULL;
		zip->stream.zfree = Z_NULL;
		zip->stream.opaque = Z_NULL;
		zip->stream.next_out = zip->buf;
		zip->stream.avail_out = (uInt)zip->len_buf;
		if (deflateInit2(&zip->stream, Z_DEFAULT_COMPRESSION,
		    Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY) != Z_OK) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't init deflate compressor");
			return (ARCHIVE_FATAL);
		}
		break;
#endif
	}
