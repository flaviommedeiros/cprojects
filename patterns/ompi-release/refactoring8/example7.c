opal_cmd_line_init_t cmd_line_opts[] = {
    { NULL,
      'h', NULL, "help", 
      0,
      &orte_checkpoint_globals.help, OPAL_CMD_LINE_TYPE_BOOL,
      "This help message" },

    { NULL,
      'v', NULL, "verbose", 
      0,
      &orte_checkpoint_globals.verbose, OPAL_CMD_LINE_TYPE_BOOL,
      "Be Verbose" },

    { NULL,
      'V', NULL, NULL, 
      1,
      &orte_checkpoint_globals.verbose_level, OPAL_CMD_LINE_TYPE_INT,
      "Set the verbosity level (For additional debugging information)" },

    { NULL,
      '\0', NULL, "term", 
      0,
      &(orte_checkpoint_globals.term), OPAL_CMD_LINE_TYPE_BOOL,
      "Terminate the application after checkpoint (Cannot be used with --stop)" },

    { NULL,
      '\0', NULL, "stop", 
      0,
      &(orte_checkpoint_globals.stop), OPAL_CMD_LINE_TYPE_BOOL,
      "Send SIGSTOP to application just after checkpoint (checkpoint will not finish until SIGCONT is sent) (Cannot be used with --term)" },

    { NULL,
      'w', NULL, "nowait", 
      0,
      &orte_checkpoint_globals.nowait, OPAL_CMD_LINE_TYPE_BOOL,
      "Do not wait for the application to finish checkpointing before returning" },

    { NULL,
      's', NULL, "status", 
      0,
      &orte_checkpoint_globals.status, OPAL_CMD_LINE_TYPE_BOOL,
      "Display status messages describing the progression of the checkpoint" },

    { "hnp-jobid",
      '\0', NULL, "hnp-jobid", 
      1,
      &orte_checkpoint_globals.req_hnp, OPAL_CMD_LINE_TYPE_INT,
      "This should be the jobid of the HNP whose applications you wish "
      "to checkpoint." },

    { "hnp-pid",
      '\0', NULL, "hnp-pid", 
      1,
      &orte_checkpoint_globals.pid, OPAL_CMD_LINE_TYPE_INT,
      "This should be the pid of the mpirun whose applications you wish "
      "to checkpoint." },

    { NULL,
      'l', NULL, "list", 
      0,
      &orte_checkpoint_globals.list_only, OPAL_CMD_LINE_TYPE_BOOL,
      "Display a list of checkpoint files available on this machine" },

#if OPAL_ENABLE_CRDEBUG == 1
    { NULL,
      '\0', "crdebug", "crdebug",
      0,
      &orte_checkpoint_globals.enable_crdebug, OPAL_CMD_LINE_TYPE_BOOL,
      "Enable C/R Enhanced Debugging" },

    { NULL,
      '\0', "attach", "attach", 
      0,
      &(orte_checkpoint_globals.attach_debugger), OPAL_CMD_LINE_TYPE_BOOL,
      "Wait for the debugger to attach directly after taking the checkpoint." },

    { NULL,
      '\0', "detach", "detach", 
      0,
      &(orte_checkpoint_globals.detach_debugger), OPAL_CMD_LINE_TYPE_BOOL,
      "Do not wait for the debugger to reattach after taking the checkpoint." },
#endif

    /* End of list */
    { NULL, '\0', NULL, NULL, 0,
      NULL, OPAL_CMD_LINE_TYPE_NULL,
      NULL }
};
