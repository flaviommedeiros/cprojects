static opal_cmd_line_init_t cmd_line_init[] = {
    /* Various "obvious" options */
    { NULL, 'h', NULL, "help", 0,
      &myglobals.help, OPAL_CMD_LINE_TYPE_BOOL,
      "This help message" },
    { NULL, 'V', NULL, "version", 0,
      &myglobals.version, OPAL_CMD_LINE_TYPE_BOOL,
      "Print version and exit" },

    { NULL, '\0', "report-pid", "report-pid", 1,
      &myglobals.report_pid, OPAL_CMD_LINE_TYPE_STRING,
      "Printout pid on stdout [-], stderr [+], or a file [anything else]" },
    
    /* select stdin option */
    { NULL, '\0', "stdin", "stdin", 1,
      &myglobals.stdin_target, OPAL_CMD_LINE_TYPE_STRING,
      "Specify procs to receive stdin [rank, all, none] (default: 0, indicating rank 0)" },
    
    /* request that argv[0] be indexed */
    { NULL, '\0', "index-argv-by-rank", "index-argv-by-rank", 0,
      &myglobals.index_argv, OPAL_CMD_LINE_TYPE_BOOL,
      "Uniquely index argv[0] for each process using its rank" },

    /* Preload the binary on the remote machine */
    { NULL, 's', NULL, "preload-binary", 0,
      &myglobals.preload_binaries, OPAL_CMD_LINE_TYPE_BOOL,
      "Preload the binary on the remote machine before starting the remote process." },

    /* Preload files on the remote machine */
    { NULL, '\0', NULL, "preload-files", 1,
      &myglobals.preload_files, OPAL_CMD_LINE_TYPE_STRING,
      "Preload the comma separated list of files to the remote machines current working directory before starting the remote process." },

    /* Use an appfile */
    { NULL, '\0', NULL, "app", 1,
      &myglobals.appfile, OPAL_CMD_LINE_TYPE_STRING,
      "Provide an appfile; ignore all other command line options" },

    /* Number of processes; -c, -n, --n, -np, and --np are all
       synonyms */
    { NULL, 'c', "np", "np", 1,
      &myglobals.num_procs, OPAL_CMD_LINE_TYPE_INT,
      "Number of processes to run" },
    { NULL, '\0', "n", "n", 1,
      &myglobals.num_procs, OPAL_CMD_LINE_TYPE_INT,
      "Number of processes to run" },
    
    /* uri of Open MPI HNP, or at least where to get it */
    { NULL, '\0', "hnp", "hnp", 1,
      &myglobals.hnp, OPAL_CMD_LINE_TYPE_STRING,
      "Specify the URI of the Open MPI server, or the name of the file (specified as file:filename) that contains that info" },
    
    /* uri of Open MPI HNP, or at least where to get it */
    { NULL, '\0', "terminate", "terminate", 0,
      &myglobals.terminate, OPAL_CMD_LINE_TYPE_BOOL,
      "Terminate the DVM" },
    

    /* Export environment variables; potentially used multiple times,
       so it does not make sense to set into a variable */
    { NULL, 'x', NULL, NULL, 1,
      NULL, OPAL_CMD_LINE_TYPE_NULL,
      "Export an environment variable, optionally specifying a value (e.g., \"-x foo\" exports the environment variable foo and takes its value from the current environment; \"-x foo=bar\" exports the environment variable name foo and sets its value to \"bar\" in the started processes)" },

      /* Mapping controls */
    { NULL, 'H', "host", "host", 1,
      NULL, OPAL_CMD_LINE_TYPE_STRING,
      "List of hosts to invoke processes on" },
    { NULL, '\0', "nolocal", "nolocal", 0,
      &myglobals.nolocal, OPAL_CMD_LINE_TYPE_BOOL,
      "Do not run any MPI applications on the local node" },
    { NULL, '\0', "nooversubscribe", "nooversubscribe", 0,
      &myglobals.no_oversubscribe, OPAL_CMD_LINE_TYPE_BOOL,
      "Nodes are not to be oversubscribed, even if the system supports such operation"},
    { NULL, '\0', "oversubscribe", "oversubscribe", 0,
      &myglobals.oversubscribe, OPAL_CMD_LINE_TYPE_BOOL,
      "Nodes are allowed to be oversubscribed, even on a managed system, and overloading of processing elements"},
    { NULL, '\0', "cpus-per-proc", "cpus-per-proc", 1,
      &myglobals.cpus_per_proc, OPAL_CMD_LINE_TYPE_INT,
      "Number of cpus to use for each process [default=1]" },

    /* Nperxxx options that do not require topology and are always
     * available - included for backwards compatibility
     */
    { NULL, '\0', "pernode", "pernode", 0,
      &myglobals.pernode, OPAL_CMD_LINE_TYPE_BOOL,
      "Launch one process per available node" },
    { NULL, '\0', "npernode", "npernode", 1,
      &myglobals.npernode, OPAL_CMD_LINE_TYPE_INT,
      "Launch n processes per node on all allocated nodes" },
    { NULL, '\0', "N", NULL, 1,
      &myglobals.npernode, OPAL_CMD_LINE_TYPE_INT,
        "Launch n processes per node on all allocated nodes (synonym for npernode)" },

#if OPAL_HAVE_HWLOC
    /* declare hardware threads as independent cpus */
    { NULL, '\0', "use-hwthread-cpus", "use-hwthread-cpus", 0,
      &myglobals.use_hwthreads_as_cpus, OPAL_CMD_LINE_TYPE_BOOL,
      "Use hardware threads as independent cpus" },

    /* include npersocket for backwards compatibility */
    { NULL, '\0', "npersocket", "npersocket", 1,
      &myglobals.npersocket, OPAL_CMD_LINE_TYPE_INT,
      "Launch n processes per socket on all allocated nodes" },

    /* Mapping options */
    { NULL, '\0', NULL, "map-by", 1,
      &myglobals.mapping_policy, OPAL_CMD_LINE_TYPE_STRING,
      "Mapping Policy [slot | hwthread | core | socket (default) | numa | board | node]" },

      /* Ranking options */
    { NULL, '\0', NULL, "rank-by", 1,
      &myglobals.ranking_policy, OPAL_CMD_LINE_TYPE_STRING,
      "Ranking Policy [slot (default) | hwthread | core | socket | numa | board | node]" },

      /* Binding options */
    { NULL, '\0', NULL, "bind-to", 1,
      &myglobals.binding_policy, OPAL_CMD_LINE_TYPE_STRING,
      "Policy for binding processes. Allowed values: none, hwthread, core, l1cache, l2cache, l3cache, socket, numa, board (\"none\" is the default when oversubscribed, \"core\" is the default when np<=2, and \"socket\" is the default when np>2). Allowed qualifiers: overload-allowed, if-supported" },

    { NULL, '\0', "report-bindings", "report-bindings", 0,
      &myglobals.report_bindings, OPAL_CMD_LINE_TYPE_BOOL,
      "Whether to report process bindings to stderr" },

#else
    /* Mapping options */
    { NULL, '\0', NULL, "map-by", 1,
      &myglobals.mapping_policy, OPAL_CMD_LINE_TYPE_STRING,
      "Mapping Policy [slot (default) | node]" },

      /* Ranking options */
    { NULL, '\0', NULL, "rank-by", 1,
      &myglobals.ranking_policy, OPAL_CMD_LINE_TYPE_STRING,
      "Ranking Policy [slot (default) | node]" },
#endif

    /* mpiexec-like arguments */
    { NULL, '\0', "wdir", "wdir", 1,
      &myglobals.wdir, OPAL_CMD_LINE_TYPE_STRING,
      "Set the working directory of the started processes" },
    { NULL, '\0', "wd", "wd", 1,
      &myglobals.wdir, OPAL_CMD_LINE_TYPE_STRING,
      "Synonym for --wdir" },
    { NULL, '\0', "set-cwd-to-session-dir", "set-cwd-to-session-dir", 0,
      &myglobals.set_cwd_to_session_dir, OPAL_CMD_LINE_TYPE_BOOL,
      "Set the working directory of the started processes to their session directory" },
    { NULL, '\0', "path", "path", 1,
      &myglobals.path, OPAL_CMD_LINE_TYPE_STRING,
      "PATH to be used to look for executables to start processes" },

    { NULL, '\0', "enable-recovery", "enable-recovery", 0,
      &myglobals.enable_recovery, OPAL_CMD_LINE_TYPE_BOOL,
      "Enable recovery (resets all recovery options to on)" },

    { NULL, 'd', "debug-devel", "debug-devel", 0,
      &myglobals.debug, OPAL_CMD_LINE_TYPE_BOOL,
      "Enable debugging of OpenRTE" },
    
    { NULL, '\0', "allow-run-as-root", "allow-run-as-root", 0,
      &myglobals.run_as_root, OPAL_CMD_LINE_TYPE_BOOL,
      "Allow execution as root (STRONGLY DISCOURAGED)" },

    /* End of list */
    { NULL, '\0', NULL, NULL, 0,
      NULL, OPAL_CMD_LINE_TYPE_NULL, NULL }
};
