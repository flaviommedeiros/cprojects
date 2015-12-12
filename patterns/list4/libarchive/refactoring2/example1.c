#if defined(_WIN32) && !defined(__CYGWIN__)
if (strrchr(name, '/') > lafe_progname)
#endif
	lafe_progname = strrchr(name, '/');
