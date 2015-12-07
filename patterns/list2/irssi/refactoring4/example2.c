#ifndef WIN32
if (mkdir(dir, mode) == -1)
#else
			if (_mkdir(dir) == -1)
#endif
			{
				g_free(dir);
				return -1;
			}
