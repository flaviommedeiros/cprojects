#ifdef PATH_MAX
if ((rsize - off) > PATH_MAX)
				end = off + PATH_MAX;
			else
#endif
				end = rsize;
