static const char * callsystem_default_envvars[]={
		"USER", "LOGNAME", "HOME", "LANG", "LC_ALL", "LC_COLLATE", "LC_CTYPE",
		"LC_MESSAGES", "LC_MONETARY", "LC_NUMERIC", "LC_TIME", "PATH", "MANPATH",
		"INFOPATH", "CDPATH", "DISPLAY", "PWD", "SHELL", "TERM", "PAGER", "EDITOR",
		"VISUAL", "BROWSER", "NLSPATH", "LOCPATH", "TMPDIR",
		"HOSTALIASES", "TZ", "TZDIR", "TERMCAP",
		"COLUMNS", "LINES",
#ifdef unix
		"LD_LIBRARY_PATH", "LD_PRELOAD", "POSIXLY_CORRECT",
		/* please review this list, I just added anything I found, naturally
		 * here shall only be the names which are expected for sane operation */
#elif defined(WIN32)
		/* */
#endif
		0,
	};
