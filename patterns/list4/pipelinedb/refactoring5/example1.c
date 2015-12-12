#ifdef HAVE_LIBZ
if (ztarfile != NULL)
	{
		if (gzwrite(ztarfile, buf, r) != r)
		{
			fprintf(stderr,
					_("%s: could not write to compressed file \"%s\": %s\n"),
					progname, current_file, get_gz_error(ztarfile));
			disconnect_and_exit(1);
		}
	}
	else
#endif
	{
		if (fwrite(buf, r, 1, tarfile) != 1)
		{
			fprintf(stderr, _("%s: could not write to file \"%s\": %s\n"),
					progname, current_file, strerror(errno));
			disconnect_and_exit(1);
		}
	}
