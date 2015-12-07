#ifdef USE_VFORK
if (svr_ses.server_pid == getpid())
#endif
	{
		/* must be after we've done with username etc */
		session_cleanup();
	}
