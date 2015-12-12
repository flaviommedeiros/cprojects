#ifdef HAVE_LIBZ
if (fp->compressedfp)
		return gzgets(fp->compressedfp, buf, len);
	else
#endif
		return fgets(buf, len, fp->uncompressedfp);
