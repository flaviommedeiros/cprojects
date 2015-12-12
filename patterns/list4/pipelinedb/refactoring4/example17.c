#ifndef WIN32
if ((*dirpath)[strlen(*dirpath) - 1] == '/')
#else
	if ((*dirpath)[strlen(*dirpath) - 1] == '/' ||
		(*dirpath)[strlen(*dirpath) - 1] == '\\')
#endif
		(*dirpath)[strlen(*dirpath) - 1] = 0;
