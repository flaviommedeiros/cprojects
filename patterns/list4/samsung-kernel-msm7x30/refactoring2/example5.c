#ifdef CONFIG_CMDLINE
if (!((char *)data)[0])
#endif
		strlcpy(data, CONFIG_CMDLINE, COMMAND_LINE_SIZE);
