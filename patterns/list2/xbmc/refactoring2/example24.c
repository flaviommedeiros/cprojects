#ifdef __linux__
if (dlderr)
#endif
    {
	dlderr = dld_init(dld_find_executable(argv[0]));
        if (dlderr) {
            char *msg = dld_strerror(dlderr);
            fprintf(stderr, "dld_init(%s) failed: %s\n", argv[0], msg);
        }
    }
