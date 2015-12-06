if ((map = mmap(NULL, orig_size,
	    PROT_READ,
#ifdef MAP_NOCORE
	    MAP_NOCORE |
#endif
	    MAP_PRIVATE,
	    fh->fd, (wt_off_t)0)) == MAP_FAILED) {
		WT_RET_MSG(session, __wt_errno(),
		    "%s map error: failed to map %" WT_SIZET_FMT " bytes",
		    fh->name, orig_size);
	}
