switch (zip->codec) {
	case _7Z_COPY:
	{
		size_t bytes =
		    (t_avail_in > t_avail_out)?t_avail_out:t_avail_in;

		memcpy(t_next_out, t_next_in, bytes);
		t_avail_in -= bytes;
		t_avail_out -= bytes;
		if (o_avail_in == 0)
			ret = ARCHIVE_EOF;
		break;
	}
#ifdef HAVE_LZMA_H
	case _7Z_LZMA: case _7Z_LZMA2:
		zip->lzstream.next_in = t_next_in;
		zip->lzstream.avail_in = t_avail_in;
		zip->lzstream.next_out = t_next_out;
		zip->lzstream.avail_out = t_avail_out;

		r = lzma_code(&(zip->lzstream), LZMA_RUN);
		switch (r) {
		case LZMA_STREAM_END: /* Found end of stream. */
			lzma_end(&(zip->lzstream));
			zip->lzstream_valid = 0;
			ret = ARCHIVE_EOF;
			break;
		case LZMA_OK: /* Decompressor made some progress. */
			break;
		default:
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
				"Decompression failed(%d)",
			    r);
			return (ARCHIVE_FAILED);
		}
		t_avail_in = zip->lzstream.avail_in;
		t_avail_out = zip->lzstream.avail_out;
		break;
#endif
#if defined(HAVE_BZLIB_H) && defined(BZ_CONFIG_ERROR)
	case _7Z_BZ2:
		zip->bzstream.next_in = (char *)(uintptr_t)t_next_in;
		zip->bzstream.avail_in = t_avail_in;
		zip->bzstream.next_out = (char *)(uintptr_t)t_next_out;
		zip->bzstream.avail_out = t_avail_out;
		r = BZ2_bzDecompress(&(zip->bzstream));
		switch (r) {
		case BZ_STREAM_END: /* Found end of stream. */
			switch (BZ2_bzDecompressEnd(&(zip->bzstream))) {
			case BZ_OK:
				break;
			default:
				archive_set_error(&(a->archive),
				    ARCHIVE_ERRNO_MISC,
				    "Failed to clean up decompressor");
				return (ARCHIVE_FAILED);
			}
			zip->bzstream_valid = 0;
			ret = ARCHIVE_EOF;
			break;
		case BZ_OK: /* Decompressor made some progress. */
			break;
		default:
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "bzip decompression failed");
			return (ARCHIVE_FAILED);
		}
		t_avail_in = zip->bzstream.avail_in;
		t_avail_out = zip->bzstream.avail_out;
		break;
#endif
#ifdef HAVE_ZLIB_H
	case _7Z_DEFLATE:
		zip->stream.next_in = (Bytef *)(uintptr_t)t_next_in;
		zip->stream.avail_in = (uInt)t_avail_in;
		zip->stream.next_out = t_next_out;
		zip->stream.avail_out = (uInt)t_avail_out;
		r = inflate(&(zip->stream), 0);
		switch (r) {
		case Z_STREAM_END: /* Found end of stream. */
			ret = ARCHIVE_EOF;
			break;
		case Z_OK: /* Decompressor made some progress.*/
			break;
		default:
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "File decompression failed (%d)", r);
			return (ARCHIVE_FAILED);
		}
		t_avail_in = zip->stream.avail_in;
		t_avail_out = zip->stream.avail_out;
		break;
#endif
	case _7Z_PPMD:
	{
		uint64_t flush_bytes;

		if (!zip->ppmd7_valid || zip->ppmd7_stat < 0 ||
		    t_avail_out <= 0) {
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "Decompression internal error");
			return (ARCHIVE_FAILED);
		}
		zip->ppstream.next_in = t_next_in;
		zip->ppstream.avail_in = t_avail_in;
		zip->ppstream.next_out = t_next_out;
		zip->ppstream.avail_out = t_avail_out;
		if (zip->ppmd7_stat == 0) {
			zip->bytein.a = a;
			zip->bytein.Read = &ppmd_read;
			zip->range_dec.Stream = &zip->bytein;
			r = __archive_ppmd7_functions.Ppmd7z_RangeDec_Init(
				&(zip->range_dec));
			if (r == 0) {
				zip->ppmd7_stat = -1;
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Failed to initialize PPMd range decorder");
				return (ARCHIVE_FAILED);
			}
			if (zip->ppstream.overconsumed) {
				zip->ppmd7_stat = -1;
				return (ARCHIVE_FAILED);
			}
			zip->ppmd7_stat = 1;
		}

		if (t_avail_in == 0)
			/* XXX Flush out remaining decoded data XXX */
			flush_bytes = zip->folder_outbytes_remaining;
		else
			flush_bytes = 0;

		do {
			int sym;

			sym = __archive_ppmd7_functions.Ppmd7_DecodeSymbol(
				&(zip->ppmd7_context), &(zip->range_dec.p));
			if (sym < 0) {
				zip->ppmd7_stat = -1;
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Failed to decode PPMd");
				return (ARCHIVE_FAILED);
			}
			if (zip->ppstream.overconsumed) {
				zip->ppmd7_stat = -1;
				return (ARCHIVE_FAILED);
			}
			*zip->ppstream.next_out++ = (unsigned char)sym;
			zip->ppstream.avail_out--;
			zip->ppstream.total_out++;
			if (flush_bytes)
				flush_bytes--;
		} while (zip->ppstream.avail_out &&
			(zip->ppstream.avail_in || flush_bytes));

		t_avail_in = (size_t)zip->ppstream.avail_in;
		t_avail_out = (size_t)zip->ppstream.avail_out;
		break;
	}
	default:
		archive_set_error(&(a->archive), ARCHIVE_ERRNO_MISC,
		    "Decompression internal error");
		return (ARCHIVE_FAILED);
	}
