#ifdef WIN32
if (GetLastError() != ERROR_FILE_EXISTS)
#else
	if (errno != EEXIST)
#endif
	{
#ifdef WIN32
		fprintf(stderr, "GetLastError() not thread-safe **\nexiting\n");
#else
		fprintf(stderr, "errno not thread-safe **\nexiting\n");
#endif
		unlink(TEMP_FILENAME_1);
		exit(1);
	}
