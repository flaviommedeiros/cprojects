switch (compress) {
#ifndef NO_BZIP2_CREATE
	case 'j': case 'y':
		archive_write_set_compression_bzip2(a);
		break;
#endif
#ifndef NO_COMPRESS_CREATE
	case 'Z':
		archive_write_set_compression_compress(a);
		break;
#endif
#ifndef NO_GZIP_CREATE
	case 'z':
		archive_write_set_compression_gzip(a);
		break;
#endif
	default:
		archive_write_set_compression_none(a);
		break;
	}
