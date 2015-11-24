static fr_command_table_t command_table_debug[] = {
	{ "condition", FR_WRITE,
	  "debug condition [condition] - Enable debugging for requests matching [condition]",
	  command_debug_condition, NULL },

	{ "level", FR_WRITE,
	  "debug level <number> - Set debug level to <number>.  Higher is more debugging.",
	  command_debug_level, NULL },

	{ "file", FR_WRITE,
	  "debug file [filename] - Send all debugging output to [filename]",
	  command_debug_file, NULL },

#if defined(HAVE_FOPENCOOKIE) || defined (HAVE_FUNOPEN)
	{ "socket", FR_WRITE,
	  "debug socket [on|off] - Send all debugging output to radmin socket.",
	  command_debug_socket, NULL },
#endif

	{ NULL, 0, NULL, NULL, NULL }
};
