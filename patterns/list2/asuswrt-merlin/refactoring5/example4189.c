#ifdef LIBXML_DEBUG_ENABLED
if ((!strcmp(argv[i], "-debug")) || (!strcmp(argv[i], "--debug")))
	    debug++;
	else
#endif
	    if ((!strcmp(argv[i], "-copy")) || (!strcmp(argv[i], "--copy")))
	    copy++;
#ifdef LIBXML_PUSH_ENABLED
	else if ((!strcmp(argv[i], "-push")) || (!strcmp(argv[i], "--push")))
	    push++;
#endif /* LIBXML_PUSH_ENABLED */
	else if ((!strcmp(argv[i], "-sax")) || (!strcmp(argv[i], "--sax")))
	    sax++;
	else if ((!strcmp(argv[i], "-noout")) || (!strcmp(argv[i], "--noout")))
	    noout++;
	else if ((!strcmp(argv[i], "-repeat")) ||
	         (!strcmp(argv[i], "--repeat")))
	    repeat++;
	else if ((!strcmp(argv[i], "-encode")) ||
	         (!strcmp(argv[i], "--encode"))) {
	    i++;
	    encoding = argv[i];
        }
