opal_cmd_line_init_t cmd_line_opts[] = {
    { NULL,
      'h', NULL, "help", 
      0,
      &orte_restart_globals.help, OPAL_CMD_LINE_TYPE_BOOL,
      "This help message" },

    { NULL,
      'v', NULL, "verbose", 
      0,
      &orte_restart_globals.verbose, OPAL_CMD_LINE_TYPE_BOOL,
      "Be Verbose" },

    { NULL,
      '\0', NULL, "fork", 
      0,
      &orte_restart_globals.forked, OPAL_CMD_LINE_TYPE_BOOL,
      "Fork off a new process which is the restarted process instead of "
      "replacing orte_restart" },

    { NULL,
      's', NULL, "seq", 
      1,
      &orte_restart_globals.seq_number, OPAL_CMD_LINE_TYPE_INT,
      "The sequence number of the checkpoint to start from. "
      "(Default: -1, or most recent)" },

    { NULL,
      '\0', "hostfile", "hostfile", 
      1,
      &orte_restart_globals.hostfile, OPAL_CMD_LINE_TYPE_STRING,
      "Provide a hostfile to use for launch" },

    { NULL,
      '\0', "machinefile", "machinefile", 
      1,
      &orte_restart_globals.hostfile, OPAL_CMD_LINE_TYPE_STRING,
      "Provide a hostfile to use for launch" },

    { NULL,
      'i', NULL, "info", 
      0,
      &orte_restart_globals.info_only, OPAL_CMD_LINE_TYPE_BOOL,
      "Display information about the checkpoint" },

    { NULL,
      'a', NULL, "apponly", 
      0,
      &orte_restart_globals.app_only, OPAL_CMD_LINE_TYPE_BOOL,
      "Only create the app context file, do not restart from it" },

    { NULL,
      '\0', NULL, "showme", 
      0,
      &orte_restart_globals.showme, OPAL_CMD_LINE_TYPE_BOOL,
      "Display the full command line that would have been exec'ed." },

    { NULL,
      '\0', "mpirun_opts", "mpirun_opts", 
      1,
      &orte_restart_globals.mpirun_opts, OPAL_CMD_LINE_TYPE_STRING,
      "Command line options to pass directly to mpirun (be sure to quote long strings, and escape internal quotes)" },

#if OPAL_ENABLE_CRDEBUG == 1
    { NULL,
      '\0', "crdebug", "crdebug",
      0,
      &orte_restart_globals.enable_crdebug, OPAL_CMD_LINE_TYPE_BOOL,
      "Enable C/R Enhanced Debugging" },
#endif

    /* End of list */
    { NULL,
      '\0', NULL, NULL, 
      0,
      NULL, OPAL_CMD_LINE_TYPE_NULL,
      NULL }
};
