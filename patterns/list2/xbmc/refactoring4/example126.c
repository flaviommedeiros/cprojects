#ifdef __MACOS__
if(errno)
#else
	if(errno && errno != ENOENT)
#endif
	{
	    if(noise_mode)
		ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "%s: %s",
			  current_filename, strerror(errno));
	    return 0;
	  }
