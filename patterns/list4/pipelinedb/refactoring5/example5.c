#ifdef HAVE_LIBZ
if (compresslevel != 0)
	{
		if (!ztarfile)
		{
			/* Compression is in use */
			fprintf(stderr,
					_("%s: could not create compressed file \"%s\": %s\n"),
					progname, filename, get_gz_error(ztarfile));
			disconnect_and_exit(1);
		}
	}
	else
#endif
	{
		/* Either no zlib support, or zlib support but compresslevel = 0 */
		if (!tarfile)
		{
			fprintf(stderr, _("%s: could not create file \"%s\": %s\n"),
					progname, filename, strerror(errno));
			disconnect_and_exit(1);
		}
	}
