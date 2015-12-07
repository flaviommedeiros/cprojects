#ifndef __W32__
if(strncmp(path, fname, dirlen) != 0)
#else
    if(strncasecmp(path, fname, dirlen) != 0)
#endif /* __W32__ */
	return fname;
