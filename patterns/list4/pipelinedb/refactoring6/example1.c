if (numWorkers <= 0
#ifdef WIN32
		|| numWorkers > MAXIMUM_WAIT_OBJECTS
#endif
		)
		exit_horribly(NULL, "%s: invalid number of parallel jobs\n", progname);
