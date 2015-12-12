static struct config_enum ConfigureNamesEnum[] =
{
	{
		{"backslash_quote", PGC_USERSET, COMPAT_OPTIONS_PREVIOUS,
			gettext_noop("Sets whether \"\\'\" is allowed in string literals."),
			NULL
		},
		&backslash_quote,
		BACKSLASH_QUOTE_SAFE_ENCODING, backslash_quote_options,
		NULL, NULL, NULL
	},

	{
		{"bytea_output", PGC_USERSET, CLIENT_CONN_STATEMENT,
			gettext_noop("Sets the output format for bytea."),
			NULL
		},
		&bytea_output,
		BYTEA_OUTPUT_HEX, bytea_output_options,
		NULL, NULL, NULL
	},

	{
		{"client_min_messages", PGC_USERSET, LOGGING_WHEN,
			gettext_noop("Sets the message levels that are sent to the client."),
			gettext_noop("Each level includes all the levels that follow it. The later"
						 " the level, the fewer messages are sent.")
		},
		&client_min_messages,
		NOTICE, client_message_level_options,
		NULL, NULL, NULL
	},

	{
		{"constraint_exclusion", PGC_USERSET, QUERY_TUNING_OTHER,
			gettext_noop("Enables the planner to use constraints to optimize queries."),
			gettext_noop("Table scans will be skipped if their constraints"
						 " guarantee that no rows match the query.")
		},
		&constraint_exclusion,
		CONSTRAINT_EXCLUSION_PARTITION, constraint_exclusion_options,
		NULL, NULL, NULL
	},

	{
		{"default_transaction_isolation", PGC_USERSET, CLIENT_CONN_STATEMENT,
			gettext_noop("Sets the transaction isolation level of each new transaction."),
			NULL
		},
		&DefaultXactIsoLevel,
		XACT_READ_COMMITTED, isolation_level_options,
		NULL, NULL, NULL
	},

	{
		{"IntervalStyle", PGC_USERSET, CLIENT_CONN_LOCALE,
			gettext_noop("Sets the display format for interval values."),
			NULL,
			GUC_REPORT
		},
		&IntervalStyle,
		INTSTYLE_POSTGRES, intervalstyle_options,
		NULL, NULL, NULL
	},

	{
		{"log_error_verbosity", PGC_SUSET, LOGGING_WHAT,
			gettext_noop("Sets the verbosity of logged messages."),
			NULL
		},
		&Log_error_verbosity,
		PGERROR_DEFAULT, log_error_verbosity_options,
		NULL, NULL, NULL
	},

	{
		{"log_min_messages", PGC_SUSET, LOGGING_WHEN,
			gettext_noop("Sets the message levels that are logged."),
			gettext_noop("Each level includes all the levels that follow it. The later"
						 " the level, the fewer messages are sent.")
		},
		&log_min_messages,
		WARNING, server_message_level_options,
		NULL, NULL, NULL
	},

	{
		{"log_min_error_statement", PGC_SUSET, LOGGING_WHEN,
			gettext_noop("Causes all statements generating error at or above this level to be logged."),
			gettext_noop("Each level includes all the levels that follow it. The later"
						 " the level, the fewer messages are sent.")
		},
		&log_min_error_statement,
		ERROR, server_message_level_options,
		NULL, NULL, NULL
	},

	{
		{"log_statement", PGC_SUSET, LOGGING_WHAT,
			gettext_noop("Sets the type of statements logged."),
			NULL
		},
		&log_statement,
		LOGSTMT_NONE, log_statement_options,
		NULL, NULL, NULL
	},

	{
		{"syslog_facility", PGC_SIGHUP, LOGGING_WHERE,
			gettext_noop("Sets the syslog \"facility\" to be used when syslog enabled."),
			NULL
		},
		&syslog_facility,
#ifdef HAVE_SYSLOG
		LOG_LOCAL0,
#else
		0,
#endif
		syslog_facility_options,
		NULL, assign_syslog_facility, NULL
	},

	{
		{"session_replication_role", PGC_SUSET, CLIENT_CONN_STATEMENT,
			gettext_noop("Sets the session's behavior for triggers and rewrite rules."),
			NULL
		},
		&SessionReplicationRole,
		SESSION_REPLICATION_ROLE_ORIGIN, session_replication_role_options,
		NULL, assign_session_replication_role, NULL
	},

	{
		{"synchronous_commit", PGC_USERSET, WAL_SETTINGS,
			gettext_noop("Sets the current transaction's synchronization level."),
			NULL
		},
		&synchronous_commit,
		SYNCHRONOUS_COMMIT_ON, synchronous_commit_options,
		NULL, assign_synchronous_commit, NULL
	},

	{
		{"trace_recovery_messages", PGC_SIGHUP, DEVELOPER_OPTIONS,
			gettext_noop("Enables logging of recovery-related debugging information."),
			gettext_noop("Each level includes all the levels that follow it. The later"
						 " the level, the fewer messages are sent.")
		},
		&trace_recovery_messages,

		/*
		 * client_message_level_options allows too many values, really, but
		 * it's not worth having a separate options array for this.
		 */
		LOG, client_message_level_options,
		NULL, NULL, NULL
	},

	{
		{"track_functions", PGC_SUSET, STATS_COLLECTOR,
			gettext_noop("Collects function-level statistics on database activity."),
			NULL
		},
		&pgstat_track_functions,
		TRACK_FUNC_OFF, track_function_options,
		NULL, NULL, NULL
	},

	{
		{"wal_level", PGC_POSTMASTER, WAL_SETTINGS,
			gettext_noop("Set the level of information written to the WAL."),
			NULL
		},
		&wal_level,
		WAL_LEVEL_MINIMAL, wal_level_options,
		NULL, NULL, NULL
	},

	{
		{"dynamic_shared_memory_type", PGC_POSTMASTER, RESOURCES_MEM,
			gettext_noop("Selects the dynamic shared memory implementation used."),
			NULL
		},
		&dynamic_shared_memory_type,
		DEFAULT_DYNAMIC_SHARED_MEMORY_TYPE, dynamic_shared_memory_options,
		NULL, NULL, NULL
	},

	{
		{"wal_sync_method", PGC_SIGHUP, WAL_SETTINGS,
			gettext_noop("Selects the method used for forcing WAL updates to disk."),
			NULL
		},
		&sync_method,
		DEFAULT_SYNC_METHOD, sync_method_options,
		NULL, assign_xlog_sync_method, NULL
	},

	{
		{"xmlbinary", PGC_USERSET, CLIENT_CONN_STATEMENT,
			gettext_noop("Sets how binary values are to be encoded in XML."),
			NULL
		},
		&xmlbinary,
		XMLBINARY_BASE64, xmlbinary_options,
		NULL, NULL, NULL
	},

	{
		{"xmloption", PGC_USERSET, CLIENT_CONN_STATEMENT,
			gettext_noop("Sets whether XML data in implicit parsing and serialization "
						 "operations is to be considered as documents or content fragments."),
			NULL
		},
		&xmloption,
		XMLOPTION_CONTENT, xmloption_options,
		NULL, NULL, NULL
	},

	{
		{"huge_pages", PGC_POSTMASTER, RESOURCES_MEM,
			gettext_noop("Use of huge pages on Linux."),
			NULL
		},
		&huge_pages,
		HUGE_PAGES_TRY, huge_pages_options,
		NULL, NULL, NULL
	},

	{
		{"continuous_query_combiner_synchronous_commit", PGC_POSTMASTER, WAL_SETTINGS,
		 gettext_noop("Sets the transaction synchronization level for continuous query combiner commits."),
		 NULL
		},
		&continuous_query_combiner_synchronous_commit,
		SYNCHRONOUS_COMMIT_OFF, synchronous_commit_options,
		NULL, assign_synchronous_commit, NULL
	},

	/* End-of-list marker */
	{
		{NULL, 0, 0, NULL, NULL}, NULL, 0, NULL, NULL, NULL, NULL
	}
};
