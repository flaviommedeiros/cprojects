static fr_command_table_t command_table_set[] = {
	{ "module", FR_WRITE,
	  "set module <command> - set module commands",
	  NULL, command_table_set_module },
#ifdef WITH_PROXY
	{ "home_server", FR_WRITE,
	  "set home_server <command> - set home server commands",
	  NULL, command_table_set_home },
#endif

	{ NULL, 0, NULL, NULL, NULL }
};
