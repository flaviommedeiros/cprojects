#ifdef CONFIG_CMDLINE
if (p == NULL || l == 0 || (l == 1 && (*p) == 0))
#endif
		strlcpy(cmd_line, CONFIG_CMDLINE, COMMAND_LINE_SIZE);
