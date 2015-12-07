if (setrlimit(RLIMIT_NOFILE, &limit) == 0
#ifdef __APPLE__
                || (limit.rlim_cur = OPEN_MAX, setrlimit(RLIMIT_NOFILE, &limit)) == 0
#endif
                ) {
                fprintf(stderr, "[INFO] raised RLIMIT_NOFILE to %d\n", (int)limit.rlim_cur);
            }
