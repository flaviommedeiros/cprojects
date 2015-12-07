#ifdef HAVE_SYS_MMAN_H
if ((!strcmp(argv[i], "-memory")) || (!strcmp(argv[i], "--memory"))) {
	    memory++;
        } else
#endif
	if ((!strcmp(argv[i], "-noout")) || (!strcmp(argv[i], "--noout"))) {
	    noout++;
        }
