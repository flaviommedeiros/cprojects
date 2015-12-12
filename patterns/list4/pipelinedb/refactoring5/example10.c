#ifdef HAVE_LIBZ
if (fp->compressedfp)
		return gzwrite(fp->compressedfp, ptr, size);
	else
#endif
		return fwrite(ptr, 1, size, fp->uncompressedfp);
