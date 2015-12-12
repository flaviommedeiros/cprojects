#ifdef HAVE_LIBZ
if (fp->compressedfp)
	{
		ret = gzread(fp->compressedfp, ptr, size);
		if (ret != size && !gzeof(fp->compressedfp))
			exit_horribly(modulename,
					"could not read from input file: %s\n", strerror(errno));
	}
	else
#endif
	{
		ret = fread(ptr, 1, size, fp->uncompressedfp);
		if (ret != size && !feof(fp->uncompressedfp))
			READ_ERROR_EXIT(fp->uncompressedfp);
	}
