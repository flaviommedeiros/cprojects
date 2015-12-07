#if defined(HAVE_FSTAT64) && !defined(__OSX_AVAILABLE_BUT_DEPRECATED)
if (fstat64(fd, &st) == 0)
#else
		struct stat	st;
