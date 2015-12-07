if (errno != EPERM
#ifdef EAGAIN	/* OpenBSD returns this */
	  && errno != EAGAIN
#endif
#ifdef ENOSYS	/* Some SCOs return this (function not implemented) */
	  && errno != ENOSYS
#endif
#ifdef ENOMEM  /* Linux might return this. */
            && errno != ENOMEM
#endif
	  )
	log_error ("can't lock memory: %s\n", strerror (err));
