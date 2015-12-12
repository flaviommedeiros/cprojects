#if defined(_WIN32) && !defined(__CYGWIN__)
if (testprogdir[0] != '/' && testprogdir[0] != '\\' &&
	    !(((testprogdir[0] >= 'a' && testprogdir[0] <= 'z') ||
	       (testprogdir[0] >= 'A' && testprogdir[0] <= 'Z')) &&
		testprogdir[1] == ':' &&
		(testprogdir[2] == '/' || testprogdir[2] == '\\')))
#else
	if (testprogdir[0] != '/')
#endif
	{
		/* Fixup path for relative directories. */
		if ((testprogdir = (char *)realloc(testprogdir,
			strlen(pwd) + 1 + strlen(testprogdir) + 1)) == NULL)
		{
			fprintf(stderr, "ERROR: Out of memory.");
			exit(1);
		}
		memmove(testprogdir + strlen(pwd) + 1, testprogdir,
		    strlen(testprogdir));
		memcpy(testprogdir, pwd, strlen(pwd));
		testprogdir[strlen(pwd)] = '/';
	}
