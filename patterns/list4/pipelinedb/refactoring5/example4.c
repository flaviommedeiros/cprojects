#ifdef HAVE_LIBZ
if (compresslevel != 0)
		{
			snprintf(filename, sizeof(filename), "%s/%s.tar.gz", basedir,
					 PQgetvalue(res, rownum, 0));
			ztarfile = gzopen(filename, "wb");
			if (gzsetparams(ztarfile, compresslevel,
							Z_DEFAULT_STRATEGY) != Z_OK)
			{
				fprintf(stderr,
						_("%s: could not set compression level %d: %s\n"),
						progname, compresslevel, get_gz_error(ztarfile));
				disconnect_and_exit(1);
			}
		}
		else
#endif
		{
			snprintf(filename, sizeof(filename), "%s/%s.tar", basedir,
					 PQgetvalue(res, rownum, 0));
			tarfile = fopen(filename, "wb");
		}
