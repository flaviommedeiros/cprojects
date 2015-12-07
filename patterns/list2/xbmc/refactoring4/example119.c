#ifdef INODE_AVAILABLE
if(s.st_dev == p->dev && s.st_ino == p->ino)
#else
	if(strcmp(p->dirname, dirname) == 0)
#endif /* INODE_AVAILABLE */

	{
	    /* found */
	    if(p->dir_mtime == s.st_mtime)
		return p;

	    /* Directory entry is updated */
	    free(p->fnames[0]);
	    free(p->fnames);
#ifndef INODE_AVAILABLE
	    free(p->dirname);
#endif /* !INODE_AVAILABLE */
	    return scan_cached_files(p, &s, dirname);
	}
