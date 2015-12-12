#ifdef WIN32
if ((h1 = CreateFile(TEMP_FILENAME_1, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL)) ==
		INVALID_HANDLE_VALUE)
#else
	if ((fd = open(TEMP_FILENAME_1, O_RDWR | O_CREAT, 0600)) < 0)
#endif
	{
		fprintf(stderr, "Could not create file %s in current directory\n",
				TEMP_FILENAME_1);
		exit(1);
	}
