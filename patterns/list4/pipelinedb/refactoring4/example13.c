#ifdef WIN32
if (CreateFile(TEMP_FILENAME_1, GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL)
		!= INVALID_HANDLE_VALUE)
#else
	if (open(TEMP_FILENAME_1, O_RDWR | O_CREAT | O_EXCL, 0600) >= 0)
#endif
	{
		fprintf(stderr,
				"Could not generate failure for exclusive file create of %s in current directory **\nexiting\n",
				TEMP_FILENAME_1);
		exit(1);
	}
