#ifdef HAVE_LIBZ
if (ztarfile != NULL)
			{
				if (gzclose(ztarfile) != 0)
				{
					fprintf(stderr,
					   _("%s: could not close compressed file \"%s\": %s\n"),
							progname, filename, get_gz_error(ztarfile));
					disconnect_and_exit(1);
				}
			}
			else
#endif
			{
				if (strcmp(basedir, "-") != 0)
				{
					if (fclose(tarfile) != 0)
					{
						fprintf(stderr,
								_("%s: could not close file \"%s\": %s\n"),
								progname, filename, strerror(errno));
						disconnect_and_exit(1);
					}
				}
			}
