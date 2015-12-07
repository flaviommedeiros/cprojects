#ifdef INODE_AVAILABLE
if(p->ino == 0)
#else
	if(p->dirname == NULL)
#endif /* INODE_AVAILABLE */
	{
	    /* Entry is removed.
	     * Save the entry to `q' which is reused for puting in new entry.
	     */
	    if(q != NULL)
		q = p;
	    continue;
	}
