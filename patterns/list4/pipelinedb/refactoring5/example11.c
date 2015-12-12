#ifdef HAVE_LIBZ
if (fp->compressedfp)
	{
		ret = gzgetc(fp->compressedfp);
		if (ret == EOF)
		{
			if (!gzeof(fp->compressedfp))
				exit_horribly(modulename,
					"could not read from input file: %s\n", strerror(errno));
			else
				exit_horribly(modulename,
							"could not read from input file: end of file\n");
		}
	}
	else
#endif
	{
		ret = fgetc(fp->uncompressedfp);
		if (ret == EOF)
			READ_ERROR_EXIT(fp->uncompressedfp);
	}
