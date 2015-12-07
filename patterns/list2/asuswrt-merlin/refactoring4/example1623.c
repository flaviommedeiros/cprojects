#ifdef HAVE_FCHOWN
if ((fchown(ofd, source_stats.st_ex_uid, source_stats.st_ex_gid) == -1) && (errno != EPERM))
#else
	if ((chown(dest, source_stats.st_ex_uid, source_stats.st_ex_gid) == -1) && (errno != EPERM))
#endif
		goto err;
