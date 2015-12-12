#ifdef WIN32
if (GetLastError() != ENOENT)
#else
	if (errno != ENOENT)
#endif
	{
#ifdef WIN32
		fprintf(stderr, "GetLastError() not thread-safe **\nexiting\n");
#else
		fprintf(stderr, "errno not thread-safe **\nexiting\n");
#endif
		exit(1);
	}
