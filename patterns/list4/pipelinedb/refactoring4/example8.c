#ifndef WIN32
if (S_ISLNK(statbuf.st_mode))
#else
				if (pgwin32_is_junction(pathbuf))
#endif
					statbuf.st_mode = S_IFDIR | S_IRWXU;
