#ifdef HAVE_LIBZ
if (fp->compressedfp)
	{
		result = gzclose(fp->compressedfp);
		fp->compressedfp = NULL;
	}
	else
#endif
	{
		result = fclose(fp->uncompressedfp);
		fp->uncompressedfp = NULL;
	}
