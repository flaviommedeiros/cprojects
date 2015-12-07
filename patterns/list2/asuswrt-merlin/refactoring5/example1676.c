#ifdef VT_OPENQRY
if (ioctl(STDIN_FILENO, VT_OPENQRY, &vtno) != 0) {
		/* Not a linux terminal, probably serial console.
		 * Force the TERM setting to vt102
		 * if TERM is set to linux (the default) */
		if (!s || strcmp(s, "linux") == 0)
			putenv((char*)"TERM=vt102");
		if (!ENABLE_FEATURE_INIT_SYSLOG)
			log_console = NULL;
	} else
#endif
	if (!s)
		putenv((char*)"TERM=" CONFIG_INIT_TERMINAL_TYPE);
