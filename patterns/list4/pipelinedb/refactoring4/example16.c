#ifdef HAVE_GETRLIMIT
if (getrlimit(RLIMIT_NOFILE, &rlim) == -1)
#else							/* but BSD doesn't ... */
				if (getrlimit(RLIMIT_OFILE, &rlim) == -1)
#endif   /* RLIMIT_NOFILE */
				{
					fprintf(stderr, "getrlimit failed: %s\n", strerror(errno));
					exit(1);
				}
