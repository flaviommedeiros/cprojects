#ifdef HAVE_LIBZ
if (fp->compressedfp)
		return gzeof(fp->compressedfp);
	else
#endif
		return feof(fp->uncompressedfp);
