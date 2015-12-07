while (optind < argc
		 && (argv[optind][0] != '-' || argv[optind][1] == '\0')
#ifdef GETOPT_COMPAT
		 && (longopts == NULL
		     || argv[optind][0] != '+' || argv[optind][1] == '\0')
#endif				/* GETOPT_COMPAT */
		 )
	    optind++;
