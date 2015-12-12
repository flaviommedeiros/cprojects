#ifndef WIN32
if (access(path, X_OK) != 0)
#else
	if ((buf.st_mode & S_IXUSR) == 0)
#endif
		pg_fatal("check for \"%s\" failed: cannot execute (permission denied)\n",
				 path);
