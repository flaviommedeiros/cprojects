#ifdef __GNUC__
while ((c = getopt(argc, argv, "+c:e:n:h:osuvE")) != EOF)
#else
  while ((c = getopt(argc, argv,  "c:e:n:h:osuvE")) != EOF)
#endif
    {
    switch (c)
      {

      case 'c':

        ncopies = atoi(optarg);

        if (ncopies <= 0)
          {
          err = TRUE;
          }

        break;

      case 'e':

        // pull in selected environment variables and ones set by caller
        //  reserve 3 slots in ioenv
        //  Note: For common variable names specified both by -e and read by -E processing:
        //    If -E processed first, -e set values will prevail in the final environment.
        if ((rc = getvars_from_string(optarg, ioenv, env_count - 3, &env_index,
                    have_E, err_msg_buf, sizeof(err_msg_buf))) != 0)
          {
          fprintf(stderr, "%s: %s\n", id, err_msg_buf);
          exit(rc);
          }

        break;

      case 'E':

        if (! have_E)
          {
          // pull in all environment variables once
          //  reserve 3 slots in ioenv
          //  Note: For common variable names specified both by -e and read by -E processing:
          //    If -e processed first, -E read values will prevail in the final environment.
          if ((rc = getallvars_from_env((const char **)envp, ioenv, env_count - 3,
                      &env_index, err_msg_buf, sizeof(err_msg_buf))) != 0)
            {
            fprintf(stderr, "%s: %s\n", id, err_msg_buf);
            exit(rc);
            }

          // set the flag that we've seen this option
          have_E = true;
          }

        break;

      case 'h':

        targethost = strdup(optarg); /* run on this 1 hostname */

        break;

      case 'n':

        onenode = atoi(optarg);

        if (onenode < 0)
          {
          err = TRUE;
          }

        break;

      case 'o':

        // redirect tasks' stdout and stderr to this proc's stdout and stderr streams
        // instead of job's streams
        grabstdoe = TRUE;

        break;

      case 's':

        sync = TRUE; /* force synchronous spawns */

        break;

      case 'u':

        pernode = TRUE; /* run once per node (unique hostnames) */

        break;

      case 'v':

        verbose = TRUE; /* turn on verbose output */

        break;

      default:

        err = TRUE;

        break;
      }  /* END switch (c) */

    }
