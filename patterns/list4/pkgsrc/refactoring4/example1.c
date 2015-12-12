#if defined(HAVE_DIRFD)
if (fts_safe_changedir(sp, cur, dirfd(dirp), NULL))
#else
		if (fts_safe_changedir(sp, cur, -1, cur->fts_accpath))
#endif
		{
			if (nlinks && type == BREAD)
				cur->fts_errno = errno;
			cur->fts_flags |= FTS_DONTCHDIR;
			descend = 0;
			cderrno = errno;
		} else
			descend = 1;
