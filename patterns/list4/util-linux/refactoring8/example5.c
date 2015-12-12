static const struct option longopts[] = {
		{ "help", no_argument, NULL, 'h' },
		{ "version", no_argument, NULL, 'V'},
		{ "target", required_argument, NULL, 't' },
		{ "mount", optional_argument, NULL, 'm' },
		{ "uts", optional_argument, NULL, 'u' },
		{ "ipc", optional_argument, NULL, 'i' },
		{ "net", optional_argument, NULL, 'n' },
		{ "pid", optional_argument, NULL, 'p' },
		{ "user", optional_argument, NULL, 'U' },
		{ "setuid", required_argument, NULL, 'S' },
		{ "setgid", required_argument, NULL, 'G' },
		{ "root", optional_argument, NULL, 'r' },
		{ "wd", optional_argument, NULL, 'w' },
		{ "no-fork", no_argument, NULL, 'F' },
		{ "preserve-credentials", no_argument, NULL, OPT_PRESERVE_CRED },
#ifdef HAVE_LIBSELINUX
		{ "follow-context", no_argument, NULL, 'Z' },
#endif
		{ NULL, 0, NULL, 0 }
	};
