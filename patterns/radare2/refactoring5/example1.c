#ifdef	S_IFLNK
if ((ms->flags & R_MAGIC_SYMLINK) == 0)
		ret = lstat (fn, sb);
	else
#endif
	ret = stat (fn, sb);
