pe_cluster_option crmd_opts[] = {
	/* name, old-name, validate, values, default, short description, long description */
	{ "dc-version", NULL, "string", NULL, "none", NULL,
          "Version of Pacemaker on the cluster's DC.",
          "Includes the hash which identifies the exact changeset it was built from.  Used for diagnostic purposes."
        },
	{ "cluster-infrastructure", NULL, "string", NULL, "heartbeat", NULL,
          "The messaging stack on which Pacemaker is currently running.",
          "Used for informational and diagnostic purposes." },
	{ XML_CONFIG_ATTR_DC_DEADTIME, "dc_deadtime", "time", NULL, "20s", &check_time,
          "How long to wait for a response from other nodes during startup.",
          "The \"correct\" value will depend on the speed/load of your network and the type of switches used."
        },
	{ XML_CONFIG_ATTR_RECHECK, "cluster_recheck_interval", "time",
	  "Zero disables polling.  Positive values are an interval in seconds (unless other SI units are specified. eg. 5min)",
          "15min", &check_timer,
	  "Polling interval for time based changes to options, resource parameters and constraints.",
	  "The Cluster is primarily event driven, however the configuration can have elements that change based on time."
	  "  To ensure these changes take effect, we can optionally poll the cluster's status for changes."
        },

	{ "notification-agent", NULL, "string", NULL, "/dev/null", &check_script,
          "Notification script or tool to be called after significant cluster events",
          "Full path to a script or binary that will be invoked when resources start/stop/fail, fencing occurs or nodes join/leave the cluster.\n"
          "Must exist on all nodes in the cluster."
        },
	{ "notification-recipient", NULL, "string", NULL, "", NULL,
          "Destination for notifications (Optional)",
          "Where should the supplied script send notifications to.  Useful to avoid hard-coding this in the script."
        },

	{ "load-threshold", NULL, "percentage", NULL, "80%", &check_utilization,
	  "The maximum amount of system resources that should be used by nodes in the cluster",
	  "The cluster will slow down its recovery process when the amount of system resources used"
          " (currently CPU) approaches this limit",
        },
	{ "node-action-limit", NULL, "integer", NULL, "0", &check_number,
          "The maximum number of jobs that can be scheduled per node. Defaults to 2x cores"},
	{ XML_CONFIG_ATTR_ELECTION_FAIL, "election_timeout", "time", NULL, "2min", &check_timer,
          "*** Advanced Use Only ***.", "If need to adjust this value, it probably indicates the presence of a bug."
        },
	{ XML_CONFIG_ATTR_FORCE_QUIT, "shutdown_escalation", "time", NULL, "20min", &check_timer,
          "*** Advanced Use Only ***.", "If need to adjust this value, it probably indicates the presence of a bug."
        },
	{ "crmd-integration-timeout", NULL, "time", NULL, "3min", &check_timer,
          "*** Advanced Use Only ***.", "If need to adjust this value, it probably indicates the presence of a bug."
        },
	{ "crmd-finalization-timeout", NULL, "time", NULL, "30min", &check_timer,
          "*** Advanced Use Only ***.", "If you need to adjust this value, it probably indicates the presence of a bug."
        },
	{ "crmd-transition-delay", NULL, "time", NULL, "0s", &check_timer,
          "*** Advanced Use Only ***\n"
          "Enabling this option will slow down cluster recovery under all conditions",
          "Delay cluster recovery for the configured interval to allow for additional/related events to occur.\n"
          "Useful if your configuration is sensitive to the order in which ping updates arrive."
        },
	{ "stonith-watchdog-timeout", NULL, "time", NULL, NULL, &check_timer,
	  "How long to wait before we can assume nodes are safely down", NULL
        },
	{ "no-quorum-policy", "no_quorum_policy", "enum", "stop, freeze, ignore, suicide", "stop", &check_quorum, NULL, NULL },

#if SUPPORT_PLUGIN
	{ XML_ATTR_EXPECTED_VOTES, NULL, "integer", NULL, "2", &check_number, "The number of nodes expected to be in the cluster", "Used to calculate quorum in openais based clusters." },
#endif
};
