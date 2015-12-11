if (*pathbuf && (g_lstat(pathbuf, &sbuf, pglob) ||
	    !S_ISDIR(sbuf.st_mode)
#ifdef S_IFLINK
	     && ((globstar && !chase_symlinks) || !S_ISLNK(sbuf.st_mode))
#endif
	    ))
		return 0;
