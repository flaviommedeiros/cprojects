#if defined(HAVE_FCHMOD)
if (fchmod (ofd, source_stats.st_mode & 07777))
#else
	if (chmod (dest, source_stats.st_mode & 07777))
#endif
		goto err;
