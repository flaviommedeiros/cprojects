if(sig == SIGSEGV) {
		fprintf(stderr, "segmentation fault\n");
		exit(EXIT_FAILURE);
#ifndef _WIN32
	} else if(sig == SIGBUS) {
		fprintf(stderr, "buserror\n");
		exit(EXIT_FAILURE);
#endif
	}
#endif
