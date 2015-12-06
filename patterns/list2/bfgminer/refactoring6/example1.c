if (1 !=
#ifdef WIN32
	send(fd[1], "\0", 1, 0)
#else
	write(fd[1], "\0", 1)
#endif
	)
		applog(LOG_WARNING, "Error trying to wake notifier");
