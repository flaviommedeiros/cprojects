#if defined(_WIN32) && !defined(__CYGWIN__)
if (strrchr(*argv, '/') > lafe_progname)
#endif
		lafe_progname = strrchr(*argv, '/');
