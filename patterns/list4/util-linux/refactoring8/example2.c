static const struct option longopts[] = {
		{ "acc-expiration", no_argument,	0, 'a' },
		{ "colon-separate", no_argument,	0, 'c' },
		{ "export",         no_argument,	0, 'e' },
		{ "failed",         no_argument,	0, 'f' },
		{ "groups",         required_argument,	0, 'g' },
		{ "help",           no_argument,	0, 'h' },
		{ "logins",         required_argument,	0, 'l' },
		{ "supp-groups",    no_argument,	0, 'G' },
		{ "newline",        no_argument,	0, 'n' },
		{ "notruncate",     no_argument,	0, OPT_NOTRUNC },
		{ "noheadings",     no_argument,	0, OPT_NOHEAD },
		{ "output",         required_argument,	0, 'o' },
		{ "last",           no_argument,	0, 'L', },
		{ "raw",            no_argument,	0, 'r' },
		{ "system-accs",    no_argument,	0, 's' },
		{ "time-format",    required_argument,	0, OPT_TIME_FMT },
		{ "user-accs",      no_argument,	0, 'u' },
		{ "version",        no_argument,	0, 'V' },
		{ "pwd",            no_argument,	0, 'p' },
		{ "print0",         no_argument,	0, 'z' },
		{ "wtmp-file",      required_argument,	0, OPT_WTMP },
		{ "btmp-file",      required_argument,	0, OPT_BTMP },
#ifdef HAVE_LIBSELINUX
		{ "context",        no_argument,	0, 'Z' },
#endif
		{ NULL,             0, 			0,  0  }
	};
