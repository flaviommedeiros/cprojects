if (errno != EEXIST
#ifdef EISDIR
	  && errno != EISDIR
#endif
	 )
	/* Fatal error (EPERM, ENOSPC etc).  Doesn't make sense to loop.  */
	break;
