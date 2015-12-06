#ifdef _WIN32
if (opt_extractdir && _chdir(dirname))
#else
        if (opt_extractdir && chdir(dirname))
#endif
        {
          printf("Error changing into %s, aborting\n", dirname);
          exit(-1);
        }
